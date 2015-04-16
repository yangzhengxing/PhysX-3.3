/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <osx/OSXSamplePlatform.h>
#include <SampleApplication.h>

#include <Carbon/Carbon.h>

#include <ApplicationServices/ApplicationServices.h>

#include <GL/glew.h>
#include <cg/cg.h>
#include <PsString.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

namespace SampleRenderer
{
    void createWindow(PxU32 width, PxU32 height);
	void createGLView(SampleRenderer::RendererWindow *w);
	void releaseWindow();
	bool updateWindow();
    void emitEvents();
	void getWindowSize(PxU32& width, PxU32& height);
	bool isKeyWindow();
	void swapBuffers();
	CGPoint getViewCenter();
	CGPoint getMousePosition();
	void setTitle(const char* title);
	void getTitle(char* title, PxU32 maxLen);
}

using namespace SampleFramework;

SamplePlatform*		SampleFramework::createPlatform(SampleRenderer::RendererWindow* _app)
{
	printf("Creating OSX platform abstraction.\n");
	SamplePlatform::setPlatform(new OSXPlatform(_app));
	return SamplePlatform::platform();
}

void* OSXPlatform::compileProgram(void * context,
									  const char* assetDir,
									  const char *programPath,
									  physx::PxU64 profile,
									  const char* passString,
									  const char *entry,
									  const char **args)

{
	char fullpath[1024];
	physx::string::strcpy_s(fullpath, 1024, assetDir);
	physx::string::strcat_s(fullpath, 1024, "shaders/");
	physx::string::strcat_s(fullpath, 1024, programPath);
	CGprogram program = cgCreateProgramFromFile(static_cast<CGcontext>(context), CG_SOURCE, fullpath, static_cast<CGprofile>(profile), entry, args);

	return program;
}


OSXPlatform::OSXPlatform(SampleRenderer::RendererWindow* _app) : 
	SamplePlatform(_app),
	mHasContentFocus(false),
	mHideMouseCursor(false),
	mMouseCursorPos(0),
	mRecenterMouseCursor(false)
{
}

void OSXPlatform::setCWDToEXE(void)
{
	char exepath[1024] = {0};
	ProcessSerialNumber proc;
	GetCurrentProcess(&proc);
	FSRef location;
	GetProcessBundleLocation(&proc, &location);
	FSRefMakePath(&location, (UInt8*)exepath, 1024);

	if(exepath[0])
	{
		popPathSpec(exepath);
		chdir(exepath);
	}
}

void OSXPlatform::setupRendererDescription(SampleRenderer::RendererDesc& renDesc)
{
	renDesc.driver = SampleRenderer::Renderer::DRIVER_OPENGL;
	renDesc.windowHandle = reinterpret_cast<physx::PxU64>(static_cast<SampleApplication*>(m_app));
}

void OSXPlatform::update()
{
	SampleRenderer::emitEvents();
    SampleRenderer::updateWindow();
}

void OSXPlatform::postRendererSetup(SampleRenderer::Renderer* renderer)
{
	PX_ASSERT(m_app);
	PX_UNUSED(renderer);
	SampleApplication& app = static_cast<SampleApplication&>(*m_app);
	// TODO - APPLE MAC OSX
	if(!app.getRenderer())
	{
		// quit if no renderer was created.  Nothing else to do.
		// error was output in createRenderer.
		exit(1);
	}
	char windowTitle[1024] = {0};
	app.getTitle(windowTitle, 1024);
	strlcat(windowTitle, " : ", 1024);
	strlcat(windowTitle, SampleRenderer::Renderer::getDriverTypeName(app.getRenderer()->getDriverType()), 1024);
	app.setTitle(windowTitle);
}

void OSXPlatform::showCursor(bool isVisible)
{
	if (isVisible == mHideMouseCursor)
	{
		(isVisible) ? CGDisplayShowCursor(kCGDirectMainDisplay) : CGDisplayHideCursor(kCGDirectMainDisplay);
		mHideMouseCursor = !isVisible;
	}
}

void OSXPlatform::setMouseCursorRecentering(bool val)
{
	if (mRecenterMouseCursor != val)
	{
		mRecenterMouseCursor = val;
		if (mRecenterMouseCursor)
			recenterMouseCursor(false);
	}
}

bool OSXPlatform::getMouseCursorRecentering() const
{
	return mRecenterMouseCursor;
}

void OSXPlatform::recenterMouseCursor(bool generateEvent)
{
	if (mRecenterMouseCursor && m_app->hasFocus())
	{
		CGPoint osxCurrentPos = SampleRenderer::getMousePosition();
		CGPoint osxCenterPos = SampleRenderer::getViewCenter();	

		PxU32 width, height;
		getWindowSize(width, height);
		mMouseCursorPos = PxVec2(osxCurrentPos.x, static_cast<PxReal>(height) - osxCurrentPos.y);
		
		CGAssociateMouseAndMouseCursorPosition(0);
		CGWarpMouseCursorPosition(osxCenterPos);
		CGAssociateMouseAndMouseCursorPosition(1);
		
		if (generateEvent)
		{
			PxVec2 centerPos(osxCenterPos.x, static_cast<PxReal>(height) - osxCenterPos.y); 
			PxVec2 diff = mMouseCursorPos - centerPos;
			getOSXSampleUserInput().doOnMouseMove(mMouseCursorPos.x, mMouseCursorPos.y, diff.x, diff.y, MOUSE_MOVE);
		}
	}
}

void OSXPlatform::doInput()
{
	/* do nothing */
}

void OSXPlatform::enableContentFocus(bool val)
{
	if (val != mHasContentFocus)
	{
		mHasContentFocus = val;
		if (mHasContentFocus)
		{
			if (mHideMouseCursor)
			{
				CGDisplayHideCursor(kCGDirectMainDisplay);
			}
			recenterMouseCursor(false);
		}
		else
		{
			CGDisplayShowCursor(kCGDirectMainDisplay);			
		}
	}
}

void OSXPlatform::initializeOGLDisplay(const SampleRenderer::RendererDesc& desc,
									physx::PxU32& width,
									physx::PxU32& height)
{
	createGLView(reinterpret_cast<SampleRenderer::RendererWindow*>(desc.windowHandle));
    SampleRenderer::getWindowSize(width, height);
}

bool OSXPlatform::openWindow(PxU32& width,
                             PxU32& height,
                             const char* title,
                             bool fullscreen)
{
    SampleRenderer::createWindow(width, height);
    enableContentFocus(true);
    return true;
}

void OSXPlatform::postInitializeOGLDisplay()
{
	glewInit();
}

void OSXPlatform::freeDisplay()
{
	SampleRenderer::releaseWindow();
}

void OSXPlatform::swapBuffers()
{
	SampleRenderer::swapBuffers();
}

bool OSXPlatform::hasFocus() const
{
	return mHasContentFocus;
}

void OSXPlatform::getTitle(char *title, physx::PxU32 maxLength) const
{
	SampleRenderer::getTitle(title, maxLength);
}

void OSXPlatform::setTitle(const char *title)
{
	SampleRenderer::setTitle(title);
}

bool OSXPlatform::updateWindow()
{
	return SampleRenderer::updateWindow();
}

void OSXPlatform::getWindowSize(PxU32& width, PxU32& height)
{
	SampleRenderer::getWindowSize(width, height);
}

const char*	OSXPlatform::getPathSeparator()
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

bool OSXPlatform::makeSureDirectoryPathExists(const char* dirPath)
{
	bool ok = doesDirectoryExist(dirPath);
	if (!ok)
		ok = mkdir(dirPath, S_IRWXU|S_IRWXG|S_IRWXO) == 0;
	return ok;
}

void OSXPlatform::showMessage(const char* title, const char* message)
{
	printf("%s: %s\n", title, message);
}
