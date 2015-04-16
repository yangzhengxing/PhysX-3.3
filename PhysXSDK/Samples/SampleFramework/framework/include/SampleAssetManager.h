/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_ASSET_MANAGER_H
#define SAMPLE_ASSET_MANAGER_H

#include <stdio.h>
#include <vector>

#include <SampleAsset.h>
#include <SampleTextureAsset.h>

#include <RendererConfig.h>



namespace SampleRenderer
{
	class Renderer;
}

namespace SampleFramework
{
	class SampleAsset;

	class SampleAssetManager
	{
	public:

		class SampleAssetCreator {
		public:
            virtual ~SampleAssetCreator() {}
			virtual SampleAsset* create(const char*, SampleAsset::Type) = 0;
		};

	public:
									SampleAssetManager(SampleRenderer::Renderer &renderer,
													   SampleAssetCreator* fallbackAssetCreator = NULL);
									~SampleAssetManager();

		SampleRenderer::Renderer&	getRenderer() { return m_renderer; }

		SampleAsset*				getAsset(const char* path, SampleAsset::Type type);
		void						returnAsset(SampleAsset& asset);

	protected:
		SampleAsset*				findAsset(const char* path);
		SampleAsset*				loadAsset(const char* path, SampleAsset::Type type);
		void						releaseAsset(SampleAsset& asset);

		void						addAssetUser(SampleAsset& asset);
		void						addAsset(SampleAsset* asset);
		void						deleteAsset(SampleAsset* asset);

		SampleAsset*				loadXMLAsset(File& file, const char* path);
		SampleAsset*				loadTextureAsset(File& file, const char* path, SampleTextureAsset::Type texType);
		SampleAsset*				loadODSAsset(File& file, const char* path);

	private:
		SampleAssetManager&	operator=(const SampleAssetManager&) { return *this; }

	protected:
		SampleRenderer::Renderer&	m_renderer;
		SampleAssetCreator*			m_fallbackAssetCreator;
		std::vector<SampleAsset*>	m_assets;
	};

	void		addSearchPath(const char* path);
	void		clearSearchPaths();
	File*		findFile(const char* path, bool binary = true);
	const char*	findPath(const char* path);

	/**
	Search for the speficied path in the current directory. If not found, move up in the folder hierarchy
	until the path can be found or until the specified maximum number of steps is reached.

	\note On consoles no recursive search will be done

	\param	[in] path The path to look for
	\param	[out] buffer Buffer to store the (potentially) adjusted path
	\param	[in] bufferSize Size of buffer
	\param	[in] maxRecursion Maximum number steps to move up in the folder hierarchy
	return	true if path was found
	*/
	bool		searchForPath(const char* path, char* buffer, int bufferSize, bool isReadOnly, int maxRecursion);

} // namespace SampleFramework

#endif
