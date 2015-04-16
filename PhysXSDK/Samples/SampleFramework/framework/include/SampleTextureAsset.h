/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_TEXTURE_ASSET_H
#define SAMPLE_TEXTURE_ASSET_H

#include <stdio.h>

#include <SampleAsset.h>

namespace SampleRenderer
{
	class Renderer;
	class RendererTexture;
}

namespace SampleFramework
{

	class SampleTextureAsset : public SampleAsset
	{
		friend class SampleAssetManager;

	public:
		enum Type
		{
			DDS,
			TGA,
			BMP,
			PSP2,
			PVR,
			TEXTURE_FILE_TYPE_COUNT,
		};

	public:
		SampleTextureAsset(SampleRenderer::Renderer &renderer, File &file, const char *path, Type texType);
		virtual ~SampleTextureAsset(void);

	public:
		SampleRenderer::RendererTexture *getTexture(void);
		const SampleRenderer::RendererTexture *getTexture(void) const;

	public:
		virtual bool isOk(void) const;

	private:
		void loadDDS(SampleRenderer::Renderer &renderer, File &file);
		void loadTGA(SampleRenderer::Renderer &renderer, File &file);
		void loadPSP2Texture(SampleRenderer::Renderer &renderer, File &file);
		void loadPVR(SampleRenderer::Renderer &renderer, File &file);
		void loadBMP(SampleRenderer::Renderer &renderer, File &file);

		SampleRenderer::RendererTexture *m_texture;
	};

} // namespace SampleFramework

#endif
