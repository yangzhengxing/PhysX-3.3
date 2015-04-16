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
#ifndef RENDERER_SHAPE_H
#define RENDERER_SHAPE_H

#include <RendererConfig.h>

namespace SampleRenderer
{

	class Renderer;
	class RendererMesh;

	class RendererShape
	{
	protected:
		RendererShape(Renderer &renderer);

	public:
		virtual ~RendererShape(void);
		
		RendererMesh *getMesh(void);
		Renderer& getRenderer() const { return m_renderer; }

	private:
		RendererShape &operator=(const RendererShape &) { return *this; }

	protected:
		Renderer&		m_renderer;
		RendererMesh*	m_mesh;
	public:
		void*			m_userData;
	};

} //  namespace SampleRenderer

#endif
