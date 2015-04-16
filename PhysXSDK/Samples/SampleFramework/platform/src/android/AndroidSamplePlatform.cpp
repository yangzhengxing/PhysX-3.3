/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMemoryMacros.h>
#include <android/AndroidSamplePlatform.h>
#include <SampleApplication.h>
#include <RendererWindow.h>

#include <PsString.h>
#include <PsFile.h>
#include <PsUtilities.h>

#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>

#include <android/native_window.h>

#include "AppGlue.h"
#include "mojoshader.h"

#include <algorithm>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define RENDERER_ENABLE_GL_NV_DEPTH_NONLINEAR
 
using namespace SampleFramework;
using SampleRenderer::RendererWindow;


PxReal g_screenWidth = 1.0f,
			g_screenHeight = 1.0f,
			g_screenAspect = 1.0f;


const std::string esslVertexDefinitions("precision highp float;\n\
varying vec4 texCoord[8];\n\
varying vec4 frontColor;\n\
varying vec4 frontSecondaryColor;\n");

const std::string esslFragmentDefinitions("precision highp float;\n\
varying vec4 texCoord[8];\n\
varying vec4 frontColor;\n\
varying vec4 frontSecondaryColor;\n");

static bool isPointInRect(PxI32 x, PxI32 y, PxI32 leftTopX, PxI32 leftTopY, PxI32 rightBottomX, PxI32 rightBottomY)
{
	if(x > leftTopX && x < rightBottomX && y > leftTopY && y < rightBottomY) return true;
	return false;
}

static bool isPointInCircle(PxI32 x, PxI32 y, PxI32 cx, PxI32 cy, PxI32 radius)
{
	if(PxVec2(x - cx, y - cy).magnitude() <= radius) return true;
	return false;
}


/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
			/* TODO */
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL)
			{
				AndroidPlatform* platform = static_cast<AndroidPlatform*>(SamplePlatform::platform());
				platform->setAndroidWindow(engine->app->window);
				platform->setWindowShown(true);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            break;
        case APP_CMD_GAINED_FOCUS:
			/* TODO */
            break;
        case APP_CMD_LOST_FOCUS:
			/* TODO */
            break;
        case APP_CMD_PAUSE:
            if (engine->app->window != NULL)
			{
				AndroidPlatform* platform = static_cast<AndroidPlatform*>(SamplePlatform::platform());
				platform->setWindowShown(false);
            }
            break;
    }
}

/* This function generates GLSL source from compiled D3D bytecode */
static mojoResult::parseResultType do_parse(const char *buf, const int len)
{
	mojoResult::parseResultType pr;

	const MOJOSHADER_parseData *pd;
	pd = MOJOSHADER_parse(MOJOSHADER_PROFILE_GLSL, reinterpret_cast<const unsigned char*>(buf), len, NULL, 0, NULL, NULL, NULL);
	if(pd->error_count == 0)
	{
		pr.source = pd->output;
		for(int i = 0; i < pd->attribute_count; ++i)
			pr.attributes[pd->attributes[i].usage].push_back(pd->attributes[i].name);
	}
	else
	{
		for(int i = 0; i < pd->error_count; ++i)
			LOGI("MojoShader ERROR: %s (%s at %d)", pd->errors[i].error, pd->errors[i].filename, pd->errors[i].error_position);
	}
	MOJOSHADER_freeParseData(pd);
	return pr;
} // do_parse


/* This function assembles D3D assembly into D3D binary intermediate bytecode */
static const MOJOSHADER_parseData* assemble(const char *buf, int len, const mojoResult* result)
{
    const MOJOSHADER_parseData *pd;
    int retval = 0;

	const MOJOSHADER_symbol* psym = NULL;
	unsigned int sym_count = 0;
	
	/* TODO: find start register, find boneMatrices boolean */
	/* --- bone matrices specifics --- */
	bool boneMatrices = false;
	unsigned int startIndex = 0;
	mojoResult::relocationType::const_iterator it = result->relocation.find("g_boneMatrices");
	if(it != result->relocation.end()) 
	{
		startIndex = (*it).second.index / (sizeof(float) * 4);
		boneMatrices = true;
	}
	
	const MOJOSHADER_symbol sym = {
		"g_boneMatrices",  /* symbol name */
		MOJOSHADER_SYMREGSET_FLOAT4,  /* uses the float4 registers. */
		startIndex, /* starts at register startIndex */
		4 * 60, /* uses 4 * <num of elements> float4 registers */
		/* that was low level stuff. The rest is HLSL information. */
		{
			MOJOSHADER_SYMCLASS_MATRIX_ROWS,  /* row-major matrix */
			MOJOSHADER_SYMTYPE_FLOAT,   /* matrix of floats */
			4, /* 4 rows */
			4, /* 4 columns */
			8,  /* 8 element (array of 8 matrices, assuming that there will be no more than 8 bones maximum ever) */
			0,  /* not a struct, so no members to report. */
			NULL,  /* not a struct, so no members to report. */
		}
	};

	if(boneMatrices) {
		sym_count = 1;
		psym = &sym;
	}	
	
	/* --- bone matrices specifics --- */
    pd = MOJOSHADER_assemble(NULL, buf, len, NULL, 0, psym /* symbols */ , sym_count /* symbols count */,
                             NULL, 0, NULL, NULL,
                             NULL, NULL, NULL);

	return pd;
} // assemble

struct sizeType {
	int size;
	sizeType() : size(0) {}
	sizeType(const int x) : size(x) {}
};

static unsigned int sizeOfD3DShaderType(const std::string& type)
{
	std::map<std::string, sizeType> types;
	types["float"] = sizeof(float);
	types["float2"] = sizeof(float);
	types["float3"] = sizeof(float) * 3;
	types["float4"] = sizeof(float) * 4;
	types["float4x4"] = sizeof(float) * 4 * 4;
	return types[type].size;
}

static GLuint cgTypeToGLType(const std::string& type)
{
	std::map<std::string, GLuint> types;
	types["float"] = GL_FLOAT;
	types["float2"] = GL_FLOAT_VEC2;
	types["float3"] = GL_FLOAT_VEC3;
	types["float4"] = GL_FLOAT_VEC4;
	types["float4x4"] = GL_FLOAT_MAT4;
	return types[type];
}

static void addRelocation(const std::string& line, mojoResult::relocationType& relocation, bool vertex)
{
	const std::string vertexUniformArrayName 	= "vs_uniforms_vec4";
	const std::string pixelUniformArrayName 	= "ps_uniforms_vec4";
	const std::string vertexSamplerName			= "vs_s";
	const std::string pixelSamplerName			= "ps_s";
	std::istringstream in(line);
	std::string token;
	std::vector<std::string> tokens;
	while(in.good())
	{
		std::getline(in, token, ' ');
		tokens.push_back(token);
	}
	int varSize = sizeOfD3DShaderType(tokens[1]);
	/* Find non-sampler2D variable */
	if(varSize)
	{
		for(int i = 3; i < tokens.size(); ++i)
		{
			std::string relocationIndexPrefix("c[");
			if(!tokens[i].compare(0, relocationIndexPrefix.size(), relocationIndexPrefix))
			{
				size_t closingBrackedPos = tokens[i].find(']');
				std::string indexSubstr = tokens[i].substr(2, closingBrackedPos - 2);
				std::istringstream convertingStream(indexSubstr);
				int index = 0;
				convertingStream >> index;
				mojoResult::shaderUniformRelocation loc;
				loc.name = vertex ? vertexUniformArrayName : pixelUniformArrayName;
				/* cgc indexes vectors */
				loc.index = index * (sizeof(float) * 4);
				loc.size = varSize;
				loc.type = cgTypeToGLType(tokens[1]);
				size_t varNameOpeningBracketPos = tokens[2].find('[');
				if(varNameOpeningBracketPos != std::string::npos) 
				{
					tokens[2] = tokens[2].substr(0, varNameOpeningBracketPos);
				}
				if(relocation.count(tokens[2]) == 0)
				{
					relocation[tokens[2]] = loc;
					LOGI("\t%s(%d): %s => %s[%d]", tokens[1].c_str(), varSize, tokens[2].c_str(), loc.name.c_str(), loc.index);
				}
			}
		}
	}
	/* Find sampler2D variable */
	else if(tokens[1] == "sampler2D")
	{
		for(int i = 3; i < tokens.size(); ++i)
		{
			if(tokens[i] == "texunit")
			{
				mojoResult::shaderUniformRelocation loc;
				loc.name = (vertex ? vertexSamplerName : pixelSamplerName) + tokens[i + 1];
				loc.index = 0;
				loc.size = sizeof(void*);
				loc.type = GL_SAMPLER_2D;
				relocation[tokens[2]] = loc;
				LOGI("\tSAMPLER2D: %s => %s", tokens[2].c_str(), loc.name.c_str());
				break;
			}
		}
	}
}

static mojoResult::relocationType findInitialRelocation(const char *buf, int len, bool vertex)
{
	mojoResult::relocationType result;
	std::istringstream in(buf);
	int counter = 0;
	while(in.good())
	{
		std::string line;
		std::getline(in, line);
		std::string relocationPrefix("//var");
		if(!line.compare(0, relocationPrefix.size(), relocationPrefix))
			addRelocation(line, result, vertex);
	}
	return result;
}

static std::string replace(std::string text, std::string s, std::string d)
{
  for(unsigned index=0; index=text.find(s, index), index!=std::string::npos;)
  {
    text.replace(index, s.length(), d);
    index+=d.length();
  }
  return text;
}

static std::string trimNonNumericChars(const std::string& in)
{
	std::string result;
	for(size_t i = 0; i < in.size(); ++i)
		if(in[i] >= '0' && in[i] <= '9')
			result.append(1, in[i]);
	return result;
}

static mojoResult::relocationType findFinalRelocation(const std::string& source, const mojoResult::relocationType& relocation)
{
	mojoResult::relocationType result = relocation;
	std::string relocationLineStart1("#define vs_c");
	std::string relocationLineStart2("#define ps_c");
	std::string relocationEndStart("void main");
	std::istringstream ss(source);
	bool previous_it_valid = false;
	std::string line;
	std::map<int, int> relocations;
	while(ss.good())
	{
		std::getline(ss, line);
		if(!line.compare(0, relocationEndStart.size(), relocationEndStart)) break;
		if(!line.compare(0, relocationLineStart1.size(), relocationLineStart1) || !line.compare(0, relocationLineStart2.size(), relocationLineStart2))
		{
			std::istringstream ssl(line);
			std::string dummy, shortName, uniformName;
			getline(ssl, dummy, ' ');
			getline(ssl, shortName, ' ');
			getline(ssl, uniformName);
			uniformName = replace(uniformName, "vs_uniforms_vec4", "");
			uniformName = replace(uniformName, "ps_uniforms_vec4", "");

			shortName = trimNonNumericChars(shortName);
			uniformName = trimNonNumericChars(uniformName);
			
			/* if this was not line like
			 "#define vs_c0 vs_uniforms_vec4[0]", 			 
			 then move to the next line, otherwise shortName and uniformName should contain
			 "0" and "0" respectively, for this particular example. */
			if(!shortName.size() || !uniformName.size()) continue;
			
			std::istringstream convertingStream1(shortName);
			std::istringstream convertingStream2(uniformName);
			int uniformInitialLocation = -1, uniformFinalLocation = -1;
			convertingStream1 >> uniformInitialLocation;
			convertingStream2 >> uniformFinalLocation;
			relocations[uniformInitialLocation * sizeof(float) * 4] = uniformFinalLocation * sizeof(float) * 4;
		}
	}
	
	/* Here, we prepare three structures to be used when fixing relocation input parameter,
	One of them, the std::map<int, int> relocations, contains new indexes for each uniform in the array, including parts of uniforms, for example:
	0 -> 0
	1 -> 1
	...
	6 -> 6
	8 -> 7
	12 -> 8
	In this example there were three matrices and one scalar value. Shader didn't used fourth row of the second matrix, hence there is 8 after 6, not 7.
	Then because shader used only first row of the third matrix, the difference becomes even bigger, hence next index is 12, instead of 9. 
	Next one, initialUniformRelocations contains initial indexes for the uniforms, found in the D3D assembly comments:
	0
	4
	8
	12
	The result of the following code is the vector of the same size, which contains corrected sizes of the uniforms in the array:
	64
	48
	16
	16
	That is, first matrix is fully used, three of four rows of second matrix used and only first row of the third matrix and scalar value in the last vec4 element of the array.
	Given relocations map and sizes vector, we could fix relocation input parameter.
	*/
	
	if(!relocations.size()) return result;
	
	std::vector<int> initialUniformRelocations;
	for(mojoResult::relocationType::iterator it = result.begin(); it != result.end(); ++it)
	{
		if((*it).second.type == GL_SAMPLER_2D) continue;
		initialUniformRelocations.push_back((*it).second.index);
	}

	if(!initialUniformRelocations.size()) return result;

	std::sort(initialUniformRelocations.begin(), initialUniformRelocations.end());
	std::vector<int> uniformRelocationsFinalSizes(initialUniformRelocations.size(), 0);
	std::map<int, int> uniformIndexToSize;

	int currentUniform = 0;
	int currentUniformIndex = initialUniformRelocations[currentUniform];
	for(std::map<int, int>::iterator it = relocations.begin(); it != relocations.end(); ++it)
	{
		if((*it).first == currentUniformIndex)
		{
			currentUniform++;
			currentUniformIndex = initialUniformRelocations[currentUniform];
		}
		uniformRelocationsFinalSizes[currentUniform - 1] += sizeof(float) * 4;
	}
	
	for(int i = 0; i < initialUniformRelocations.size(); ++i)
		uniformIndexToSize[initialUniformRelocations[i]] = uniformRelocationsFinalSizes[i];
	
	/* Fixing is here */
	for(mojoResult::relocationType::iterator it = result.begin(); it != result.end(); ++it)
	{
		LOGI("Fixing: %s", (*it).first.c_str());
		if((*it).second.type == GL_SAMPLER_2D) continue;
		/* We won't fix size of just one float */
		/* Set g_boneMatrices size to 60 matrices */
		if((*it).first == "g_boneMatrices") 
		{
			(*it).second.size = sizeof(float) * 16 * 60;
			LOGI("Special case for bones: set size to %d", (*it).second.size);
		}
		else if((*it).second.size != sizeof(float))
		{
			(*it).second.size = uniformIndexToSize[(*it).second.index];
			LOGI("Set size to %d", (*it).second.size);
		}

		(*it).second.index = relocations[(*it).second.index];
	}

	return result;
}

void* AndroidPlatform::compileProgram(void * context,
										const char* assetDir,
										const char *programPath,
										physx::PxU64 profile,
										const char* passString,
										const char *entry,
										const char **args)
{
	/* Open file and read it into the buffer */
	if (programPath == NULL)
        LOGI("no input file specified");

	std::string strProgramPath(programPath);
	std::string shaderProgramName = strProgramPath.substr(0, strProgramPath.find_last_of("."));
	std::string shaderProgramPath = std::string("/sdcard/media/SampleRenderer/4/shaders/") + shaderProgramName + std::string(passString) + ".cg";
	shaderProgramPath = replace(shaderProgramPath, "vertex/", "../compiledshaders/android/vertex/");
	shaderProgramPath = replace(shaderProgramPath, "fragment/", "../compiledshaders/android/fragment/");
    FILE *io = fopen(shaderProgramPath.c_str(), "rb");
    if (io == NULL)
        LOGI("failed to open input file '%s'", shaderProgramPath.c_str());

    fseek(io, 0, SEEK_END);
    long fsize = ftell(io);
    fseek(io, 0, SEEK_SET);
    if (fsize == -1)
        fsize = 1000000;
    char *buf = new char[fsize+1];
    const int rc = fread(buf, 1, fsize, io);
    fclose(io);

	//needed for iOS & Android, since resulting buffer doesn't seem to be null terminated. 
	buf[fsize] = '\0';
	
    if (rc == EOF)
	{
        LOGI("failed to read input file");
	}
	/* Since we must return a pointer, we couldn't return object itself.
	This is why we use heap allocation here. Receiving side should free this memory.
	*/
	mojoResult* result = new mojoResult;

	/* Start two-step relocation parsing.
	First step is to find initial relocation info.
	That is, parse D3D assembly comments to find original uniform names
	mapping onto D3D assembly's variables names. Second step will fire after GLSL source
	generation complete. */
	result->relocation = findInitialRelocation(buf, rc, (std::string(entry) == "vmain"));
	/* Assemble D3D assembly into D3D bytecode */
	const MOJOSHADER_parseData *pd = assemble(buf, rc, result);
	delete[] buf;
	if(!pd)
	{
		LOGI("Failed to assemble shader!");
		return NULL;
	}
	/* Parse D3D bytecode into GLSL source */
	mojoResult::parseResultType pr = do_parse(pd->output, pd->output_len);
	pr.source = replace(pr.source, "gl_TexCoord", "texCoord");
	pr.source = replace(pr.source, "gl_FrontColor", "frontColor");
	pr.source = replace(pr.source, "gl_Color", "frontColor");
	pr.source = replace(pr.source, "gl_FrontSecondaryColor", "frontSecondaryColor");

	/* Alright, this is a bit hacky */
	if(shaderProgramName.find("pointsprite") != std::string::npos) {
		pr.source = replace(pr.source, "ps_v0.xy)", "gl_PointCoord)");
		pr.source = replace(pr.source, "ps_v1.xy)", "gl_PointCoord)");
	}
	pr.source = replace(pr.source, "#version 110", "");

	/* Second-step is to find final relocation.
	Because MojoShader generates one uniform array for all non-sampler
	uniforms and it doesn't include unused parts of original uniforms (i.e. it will
	not include other 3 rows of matrix if only first is used), we should fix relocation sizes
	to prevent overwriting of the data after the boundaries of the current uniform. */

	result->relocation = findFinalRelocation(pr.source, result->relocation);

	if(std::string(entry) == "vmain")
		pr.source = esslVertexDefinitions + pr.source;
	else
		pr.source = esslFragmentDefinitions + pr.source;

	result->parseResult = pr;
	MOJOSHADER_freeParseData(pd);
	LOGI("PLATFORM: Translated %s/%s into GLSL", programPath, passString);
	return result;
}


bool AndroidPlatform::isOpen()
{
	return m_windowShown;
}

void AndroidPlatform::setAndroidWindow(void * ptr)
{
	m_androidWindow = ptr;
}


void AndroidPlatform::setWindowShown(bool s)
{
	m_windowShown = s;
}


bool AndroidPlatform::preOpenWindow(void * ptr)
{
	bool ok = true;

	m_androidApp = static_cast<android_app*>(ptr);
	if(!m_androidApp)
	{
		LOGI("AndroidPlatform::openWindow: android_app state is NULL, couldn't register cmd/input handlers");
		ok = false;
	}
	else
	{
		memset(&m_engine, 0, sizeof(m_engine));
		m_androidApp->userData = &m_engine;
		m_androidApp->onAppCmd = engine_handle_cmd;
		m_androidApp->onInputEvent = AndroidSampleUserInput::engine_handle_input;
		m_engine.app = m_androidApp;
	}

	return ok;
}

void AndroidPlatform::update()
{
	// Read all pending events.
	int ident;
	int events;
	struct android_poll_source* source;

	while ((ident=ALooper_pollAll(0, NULL, &events,(void**)&source)) >= 0)
	{
		// Process this event.
		if (source != NULL)
		{
			source->process(m_androidApp, source);
		}
		if(m_androidApp->destroyRequested)
		{
			LOGI("PLATFORM: Destroy requested.");
			setWindowShown(false);
		}
	}
}

void AndroidPlatform::doInput()
{
	m_androidSampleUserInput.updateInput();
}

SamplePlatform* SampleFramework::createPlatform(SampleRenderer::RendererWindow* _app)
{
	LOGI("Creating Android platform abstraction.\n");
	SamplePlatform::setPlatform(new AndroidPlatform(_app));
	return SamplePlatform::platform();
}

AndroidPlatform::AndroidPlatform(SampleRenderer::RendererWindow* _app) : SamplePlatform(_app), m_windowShown(false), m_androidApp(NULL)	
{
	/* Call dummy function from the AppGlue to ensure that it isn't stripped out */
	app_dummy();	
	memcpy(m_platformName,"android",7*sizeof(char));
}


void AndroidPlatform::swapBuffers()
{
    if(m_windowShown)
        eglSwapBuffers(m_eglDisplay, m_eglSurface);
}


void AndroidPlatform::setupRendererDescription(SampleRenderer::RendererDesc& renDesc)
{
	/* Suppose that all Android devices support only GLES2 */
	renDesc.driver = SampleRenderer::Renderer::DRIVER_GLES2;
}

void AndroidPlatform::initializeOGLDisplay(const SampleRenderer::RendererDesc& desc,
											physx::PxU32& width,
											physx::PxU32& height)
{
	m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    int numConfigs;
	EGLint format;
	EGLint major, minor;

	eglInitialize(m_eglDisplay, &major, &minor);
	LOGI("Using EGL v%d.%d", major, minor);

    const EGLint config16bpp[] = {
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
#if defined(RENDERER_ENABLE_GL_NV_DEPTH_NONLINEAR)
			/* Next two magic numbers enables GL_NV_depth_nonlinear extensions to improve z-fighting problems */
			/* EGL_DEPTH_ENCODING_NV, EGL_DEPTH_ENCODING_NONLINEAR_NV */
			0x30E2, 0x30E3,
#endif
			EGL_DEPTH_SIZE, 16,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    if(!eglChooseConfig(m_eglDisplay, config16bpp, &m_eglConfig, 1, &numConfigs))
    {
		LOGI("Error: eglChooseConfig returns: %x\n", eglGetError());
    }

	EGLint configAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, EGL_NO_CONTEXT, configAttrs);
	if(!m_eglContext)
	{
		LOGI("Error: eglCreateContext returns: %x\n", eglGetError());
	}

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(m_eglDisplay, m_eglConfig, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(reinterpret_cast<EGLNativeWindowType>(m_androidWindow), 0, 0, format);

    m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, reinterpret_cast<EGLNativeWindowType>(m_androidWindow), NULL);
    if(!m_eglSurface)
	{
		LOGI("Error: eglCreateWindowSurface returns: %x\n", eglGetError());
	}

    eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
	/* Disable vsync */
	eglSwapInterval(m_eglDisplay, 0);
	width = ANativeWindow_getWidth(reinterpret_cast<EGLNativeWindowType>(m_androidWindow));
	height = ANativeWindow_getHeight(reinterpret_cast<EGLNativeWindowType>(m_androidWindow));
	g_screenWidth = width;
	m_androidSampleUserInput.setWidth(width);
	g_screenHeight = height;
	m_androidSampleUserInput.setHeight(height);
	g_screenAspect = g_screenWidth / g_screenHeight;
	LOGI("Screen size is %dx%d", width, height);

	LOGI("Vendor        = %s", glGetString(GL_VENDOR));
	LOGI("Renderer      = %s", glGetString(GL_RENDERER));
	LOGI("Version       = %s", glGetString(GL_VERSION));
	LOGI("SL Version    = %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLint numFormats;
	glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &numFormats);
	LOGI("GL Shader Binary Formats: %d formats supported", numFormats);
	LOGI("GL Extensions: %s", glGetString(GL_EXTENSIONS));
}

void AndroidPlatform::freeDisplay()
{
	eglDestroySurface(m_eglDisplay, m_eglSurface);
	eglDestroyContext(m_eglDisplay, m_eglContext);
	eglTerminate(m_eglDisplay);
	LOGI("EGL terminated after surface & context has been destroyed.");
}

const char* AndroidPlatform::getPathSeparator()
{
	return "/";
}

static bool doesDirectoryExist(const char* path)
{
	bool exists = false;
	DIR* dir = NULL;
	dir = opendir(path);
	if(dir)
	{
		closedir(dir);
		exists = true;
	}
	return exists;
}

bool AndroidPlatform::makeSureDirectoryPathExists(const char* dirPath)
{
	bool ok = doesDirectoryExist(dirPath);
	if (!ok)
	{
		ok = mkdir(dirPath, S_IRWXU|S_IRWXG|S_IRWXO) == 0;
	}
	return ok;
}
void AndroidPlatform::showMessage(const char* title, const char* message)
{
	LOGI("%s: %s\n", title, message);
}
