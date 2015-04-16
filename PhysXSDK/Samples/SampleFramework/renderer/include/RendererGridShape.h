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
// RendererGridShape : convenience class for generating a grid mesh.
//
#ifndef RENDERER_GRID_SHAPE_H
#define RENDERER_GRID_SHAPE_H

#include <RendererShape.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
#ifdef RENDERER_PSP2
	class RendererIndexBuffer;
#endif

	class RendererGridShape : public RendererShape
	{
	public:
		enum UpAxis
		{
			UP_X,
			UP_Y,
			UP_Z,
		};

		RendererGridShape(Renderer &renderer, PxU32 size, float cellSize, bool showAxis = false, UpAxis = UP_Y);
		virtual ~RendererGridShape(void);

		UpAxis getUpAxis() { return m_UpAxis; }

	private:
		RendererVertexBuffer *m_vertexBuffer;
#ifdef RENDERER_PSP2
		RendererIndexBuffer  *m_indexBuffer;
#endif
		UpAxis                m_UpAxis;
	};

} // namespace SampleRenderer

#endif
