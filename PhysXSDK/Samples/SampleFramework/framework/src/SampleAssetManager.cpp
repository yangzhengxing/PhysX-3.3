/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <SampleAssetManager.h>
#include <SampleAsset.h>
#include <SampleMaterialAsset.h>
#include <SampleTextureAsset.h>
#include <SampleInputAsset.h>

#include <Renderer.h>

#include <stdio.h>
#include "SamplePlatform.h"
#include "ODBlock.h"

// for PsString.h
namespace physx
{
	namespace string
	{}
}
#include <PsString.h>
#include <PsFile.h>

#include "SampleXml.h"
#include "extensions/PxDefaultStreams.h"

using namespace SampleFramework;

///////////////////////////////////////////////////////////////////////////////

static std::vector<char*>* gSearchPaths = NULL;

void SampleFramework::addSearchPath(const char* path)
{
	if(!path)
		return;

	const PxU32 len = *path ? (PxU32)strlen(path) : 0;
	if(!len)
		return;

	const PxU32 len2 = len+2;
	char* searchPath = new char[len2];
	physx::string::strcpy_s(searchPath, len2, path);
	if(path[len-1] != '/' && path[len-1] != '\\')
	{
		physx::string::strcat_s(searchPath, len2, "/");
	}
	if(!gSearchPaths)
		gSearchPaths = new std::vector<char*>;
	gSearchPaths->push_back(searchPath);
}

void SampleFramework::clearSearchPaths()
{
	if(!gSearchPaths)
		return;
	const PxU32 numSearchPaths = (PxU32)gSearchPaths->size();
	for(PxU32 i=0; i<numSearchPaths; i++)
	{
		delete [] (*gSearchPaths)[i];
	}
	delete gSearchPaths;
	gSearchPaths = NULL;
}

static void FixSeparators(char* path)
{
	for (unsigned i = 0; i < strlen(path); ++i)
		if (path[i] == '\\' || path[i] == '/')
			path[i] = SampleFramework::SamplePlatform::platform()->getPathSeparator()[0];
}

File* SampleFramework::findFile(const char* path, bool binary)
{
	if(!gSearchPaths)
		return NULL;

	File* file = NULL;
	const PxU32 numSearchPaths = (PxU32)gSearchPaths->size();
	for(PxU32 i=0; i<numSearchPaths; i++)
	{
		const char* prefix = (*gSearchPaths)[i];

		char fullPath[512];
		physx::string::strcpy_s(fullPath, 512, prefix);
		physx::string::strcat_s(fullPath, 512, path);
		FixSeparators(fullPath);
		if(binary)
			Fnd::fopen_s(&file, fullPath, "rb");
		else
		{
			// text files open also for write
			Fnd::fopen_s(&file, fullPath, "r+");
		}
		if(file) break;
	}
	return file;
}

const char* SampleFramework::findPath(const char* path)
{
	if(!gSearchPaths)
		return path;

	static char fullPath[512];

	File* file = NULL;
	const PxU32 numSearchPaths = (PxU32)gSearchPaths->size();
	for(PxU32 i=0; i<numSearchPaths; i++)
	{
		const char* prefix = (*gSearchPaths)[i];
		physx::string::strcpy_s(fullPath, 512, prefix);
		physx::string::strcat_s(fullPath, 512, path);
		FixSeparators(fullPath);
		Fnd::fopen_s(&file, fullPath, "rb");
		if(file) break;
	}
	if(file)
	{
		fclose(file);
		return fullPath;
	}
	else
		return path;
}


///////////////////////////////////////////////////////////////////////////////

SampleAssetManager::SampleAssetManager(SampleRenderer::Renderer& renderer,
									   SampleAssetCreator* fallbackAssetCreator) :
	m_renderer(renderer), 
	m_fallbackAssetCreator(fallbackAssetCreator)
{
}

SampleAssetManager::~SampleAssetManager(void)
{
	PX_ASSERT(m_assets.size() == 0);
}

SampleAsset* SampleAssetManager::getAsset(const char* path, SampleAsset::Type type)
{	
	SampleAsset* asset = findAsset(path);
	if(!asset)
	{
		asset = loadAsset(path, type);
	}
	if(asset && asset->getType() != type)
	{
		releaseAsset(*asset);
		asset = 0;
	}
	if(asset)
	{
		addAssetUser(*asset);
	}
	return asset;
}

void SampleAssetManager::returnAsset(SampleAsset& asset)
{
	PX_ASSERT(asset.m_numUsers > 0);
	if(asset.m_numUsers > 0)
	{
		asset.m_numUsers--;
	}
	if(asset.m_numUsers == 0)
	{
		releaseAsset(asset);
	}
}

SampleAsset* SampleAssetManager::findAsset(const char* path)
{
	SampleAsset* asset = NULL;
	PxU32 numAssets = (PxU32)m_assets.size();
	for(PxU32 i=0; i<numAssets; i++)
	{
		if(!strcmp(m_assets[i]->getPath(), path))
		{
			asset = m_assets[i];
			break;
		}
	}
	return asset;
}

static const char* strext(const char* str)
{
	const char* ext = str;
	while(str)
	{
		str = strchr(str, '.');
		if(str)
		{
			str++;
			ext = str;
		}
	}
	return ext;
}

class FileExtensions
{
public:
	explicit FileExtensions(const char** extensions, PxU32 numExtensions)
		: mExtensions(extensions), mNumExtensions(numExtensions) { }

	template<typename EnumType>
	EnumType typeOf(const char* extension)
	{
		PxU32 type = 0;
		while (type < mNumExtensions && (physx::string::stricmp(extension, mExtensions[type]) != 0)) ++type;
		return static_cast<EnumType>(type);
	}
	
protected:
	const char** mExtensions;
	PxU32  mNumExtensions;
};

enum FileType { TYPE_XML = 0, TYPE_DDS, TYPE_TGA, TYPE_ODS, TYPE_PVR, TYPE_BMP, NUM_TYPES, TYPE_NOT_SUPPORTED = NUM_TYPES };
static const char* sSupportedExtensions[NUM_TYPES] = {"xml", "dds", "tga", "ods", "pvr", "bmp"};
static FileExtensions sFileExtensions(sSupportedExtensions, NUM_TYPES);

#if defined(RENDERER_ENABLE_PVR_SUPPORT)
static FILE* findFileExchangeExtension(const char* path, bool binary, const char* origEnding, const char* newEnding)
{
	char pathPVR[512];
	strcpy(pathPVR, path);
	char* endStr = strstr(pathPVR, origEnding);	
	strcpy(endStr, newEnding);
	return findFile(pathPVR, binary);
}
#endif

SampleAsset* SampleAssetManager::loadAsset(const char* path, SampleAsset::Type type)
{
	SampleAsset* asset = NULL;
	const char* extension = strext(path);
	if(extension && *extension)
	{
		FileType fileType = sFileExtensions.typeOf<FileType>(extension);
		if (TYPE_NOT_SUPPORTED != fileType )
		{
			File* file = NULL;
#if defined(RENDERER_ENABLE_PVR_SUPPORT)
			if(fileType == TYPE_DDS)
			{
				file = findFileExchangeExtension(path, true, ".dds", ".pvr");
				fileType = TYPE_PVR;
			}
#endif
			if(!file)
				file = findFile(path, fileType != TYPE_ODS);

			if(!file)
				Fnd::fopen_s(&file, path, fileType != TYPE_ODS ? "rb" : "r+");

			if(file)
			{
				switch(fileType)
				{
				case TYPE_XML:
					 asset = loadXMLAsset(*file, path);
					 break;
				case TYPE_DDS:
#if defined(RENDERER_PSP2)
					asset = loadTextureAsset(*file, path, SampleTextureAsset::PSP2);
#else
					asset = loadTextureAsset(*file, path, SampleTextureAsset::DDS);
#endif
					break;
				case TYPE_PVR:
					asset = loadTextureAsset(*file, path, SampleTextureAsset::PVR);
					break;
				case TYPE_BMP:
					asset = loadTextureAsset(*file, path, SampleTextureAsset::BMP);
					break;
				case TYPE_TGA:
					asset = loadTextureAsset(*file, path, SampleTextureAsset::TGA);
					break;
				case TYPE_ODS:
					asset = loadODSAsset(*file, path);
					break;
				case TYPE_NOT_SUPPORTED:
				default:
					PX_ALWAYS_ASSERT();
				};
				fclose(file);
			}
		}

		if (NULL == asset)
		{
			if (m_fallbackAssetCreator)
			{
				asset = m_fallbackAssetCreator->create(path, type);
			}
			if (NULL == asset)
			{

#define SAM_DEFAULT_MATERIAL "materials/simple_lit.xml"

#if defined(RENDERER_ENABLE_PVR_SUPPORT)
#	define SAM_DEFAULT_TEXTURE "textures/test.pvr"
#else
#	define SAM_DEFAULT_TEXTURE "textures/test.dds"
#endif

				// report the missing asset
				char msg[1024];

				if (type == SampleAsset::ASSET_MATERIAL && strcmp(path, SAM_DEFAULT_MATERIAL) )  // Avoid infinite recursion
				{
					physx::string::sprintf_s(msg, sizeof(msg), "Could not find material: %s, loading default material: %s", 
						path, SAM_DEFAULT_MATERIAL);
					RENDERER_OUTPUT_MESSAGE(&m_renderer, msg);

					return loadAsset(SAM_DEFAULT_MATERIAL, type);  // Try to use the default asset
				}
				else if (type == SampleAsset::ASSET_TEXTURE)
				{
					physx::string::sprintf_s(msg, sizeof(msg), "Could not find texture: %s, loading default texture: %s", 
						path, SAM_DEFAULT_TEXTURE);
					RENDERER_OUTPUT_MESSAGE(&m_renderer, msg);

					return loadAsset(SAM_DEFAULT_TEXTURE, type);  // Try to use the default asset
				}
				else if (fileType == TYPE_ODS)
				{
					physx::string::sprintf_s(msg, sizeof(msg), "Could not find input definition: %s", path);
					RENDERER_OUTPUT_MESSAGE(&m_renderer, msg);
				}
			}
		}
	}
	//PX_ASSERT(asset && asset->isOk());
	if(asset && !asset->isOk())
	{
		deleteAsset(asset);
		asset = 0;
	}
	if(asset)
	{
		addAsset(asset);
	}
	return asset;
}

void SampleAssetManager::releaseAsset(SampleAsset& asset)
{
	PxU32 numAssets = (PxU32)m_assets.size();
	PxU32 found     = numAssets;
	for(PxU32 i=0; i<numAssets; i++)
	{
		if(&asset == m_assets[i])
		{
			found = i;
			break;
		}
	}
	PX_ASSERT(found < numAssets);
	if(found < numAssets)
	{
		m_assets[found] = m_assets.back();
		m_assets.pop_back();
		deleteAsset(&asset);
	}
}

void SampleAssetManager::addAssetUser(SampleAsset& asset)
{
	asset.m_numUsers++;
}

void SampleAssetManager::addAsset(SampleAsset* asset)
{
	if (asset)
		m_assets.push_back(asset);
}

void SampleAssetManager::deleteAsset(SampleAsset* asset)
{
	if (asset)
		asset->release();
}

SampleAsset* SampleAssetManager::loadXMLAsset(File& file, const char* path)
{
	SampleAsset* asset = NULL;

	PxDefaultFileInputData theBuffer(findPath(path));	
	FAST_XML::XmlBuilder builder;
	physx::shdfnd::FastXml *xml = createFastXml(&builder);
	xml->processXml(theBuffer, false);
	FAST_XML::xml_node* rootnode = builder.rootnode();
	if(!strcmp(rootnode->name(), "material"))
	{
		asset = new SampleMaterialAsset(*this, *rootnode, path);
	}
	xml->release();

	return asset;
}

SampleAsset* SampleAssetManager::loadTextureAsset(File& file, const char* path, SampleTextureAsset::Type texType)
{
	SampleTextureAsset* asset = new SampleTextureAsset(getRenderer(), file, path, texType);
	return asset;
}

SampleAsset* SampleAssetManager::loadODSAsset(File& file, const char* path)
{
	SampleAsset* asset = new SampleInputAsset(&file, path);
	return asset;
}
