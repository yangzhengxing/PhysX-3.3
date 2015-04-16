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
// RendererBoxShape : convenience class for generating a box mesh.
//
#ifndef RENDERER_BOX_SHAPE_H
#define RENDERER_BOX_SHAPE_H

#include <RendererShape.h>

namespace SampleRenderer
{

	class RendererVertexBuffer;
	class RendererIndexBuffer;

	class RendererBoxShape : public RendererShape
	{
	public:
		RendererBoxShape(Renderer &renderer, const PxVec3 &extents, const PxReal* uvs=NULL);
		virtual ~RendererBoxShape(void);

	private:
		RendererVertexBuffer *m_vertexBuffer;
		RendererIndexBuffer  *m_indexBuffer;
	};

} // namespace SampleRenderer

#endif
