/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
//
// RendererShape : base class for convenience classes for generating meshes based on shapes.
//
#include <RendererShape.h>

using namespace SampleRenderer;

RendererShape::RendererShape(Renderer& renderer) :
	m_renderer	(renderer),
	m_mesh		(NULL),
	m_userData	(NULL)
{
}

RendererShape::~RendererShape(void)
{
	RENDERER_ASSERT(m_mesh==0, "Mesh was not properly released before Shape destruction.");
}

RendererMesh* RendererShape::getMesh(void)
{
	return m_mesh;
}
