/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_MATERIAL_ASSET_H
#define SAMPLE_MATERIAL_ASSET_H

#include <SampleAsset.h>
#include <vector>

namespace FAST_XML
{
	class xml_node;
}

namespace SampleRenderer
{
	class RendererMaterial;
	class RendererMaterialInstance;
}

namespace SampleFramework
{
	class SampleAssetManager;

	class SampleMaterialAsset : public SampleAsset
	{
		friend class SampleAssetManager;
	protected:
		SampleMaterialAsset(SampleAssetManager &assetManager, FAST_XML::xml_node &xmlroot, const char *path);
		SampleMaterialAsset(SampleAssetManager &assetManager, Type type, const char *path);
		virtual ~SampleMaterialAsset(void);

	public:
		size_t                                    getNumVertexShaders() const;
		SampleRenderer::RendererMaterial         *getMaterial(size_t vertexShaderIndex = 0);
		SampleRenderer::RendererMaterialInstance *getMaterialInstance(size_t vertexShaderIndex = 0);
		unsigned int                              getMaxBones(size_t vertexShaderIndex) const;

	public:
		virtual bool isOk(void) const;

	protected:
		SampleAssetManager       &m_assetManager;
		struct MaterialStruct
		{
			SampleRenderer::RendererMaterial         *m_material;
			SampleRenderer::RendererMaterialInstance *m_materialInstance;
			unsigned int                              m_maxBones;
		};
		std::vector<MaterialStruct> m_vertexShaders;
		std::vector<SampleAsset*> m_assets;
	};

} // namespace SampleFramework

#endif
