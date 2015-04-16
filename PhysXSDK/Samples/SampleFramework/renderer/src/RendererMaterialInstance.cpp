/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererMaterialInstance.h>
#include <RendererMaterial.h>

using namespace SampleRenderer;

RendererMaterialInstance::RendererMaterialInstance(RendererMaterial &material) :
m_material(material)
{
	m_data = 0;
	PxU32 dataSize = m_material.getMaterialInstanceDataSize();
	if(dataSize > 0)
	{
		m_data = new PxU8[dataSize];
		memset(m_data, 0, dataSize);
	}
}

RendererMaterialInstance::RendererMaterialInstance(const RendererMaterialInstance& other) :
m_material(other.m_material)
{
	PxU32 dataSize = m_material.getMaterialInstanceDataSize();
	if (dataSize > 0)
	{
		m_data = new PxU8[dataSize];
		memcpy(m_data, other.m_data, dataSize);
	}
}

RendererMaterialInstance::~RendererMaterialInstance(void)
{
	if(m_data) delete [] m_data;
}

void RendererMaterialInstance::writeData(const RendererMaterial::Variable &var, const void *data)
{
	if(m_data && data)
	{
		memcpy(m_data+var.getDataOffset(), data, var.getDataSize());
	}
}

RendererMaterialInstance &RendererMaterialInstance::operator=(const RendererMaterialInstance &b)
{
	PX_ASSERT(&m_material == &b.m_material);
	if(&m_material == &b.m_material)
	{
		memcpy(m_data, b.m_data, m_material.getMaterialInstanceDataSize());
	}
	return *this;
}
