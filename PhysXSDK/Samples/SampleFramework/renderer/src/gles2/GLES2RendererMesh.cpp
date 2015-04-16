/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#include "GLES2RendererMesh.h"

#if defined(RENDERER_ENABLE_GLES2)
namespace SampleRenderer
{

static GLenum getGLPrimitive(RendererMesh::Primitive primitive)
{
	GLenum glprim = ~(GLenum)0;
	switch(primitive)
	{
		case RendererMesh::PRIMITIVE_POINTS:         glprim = GL_POINTS;         break;
		case RendererMesh::PRIMITIVE_LINES:          glprim = GL_LINES;          break;
		case RendererMesh::PRIMITIVE_LINE_STRIP:     glprim = GL_LINE_STRIP;     break;
		case RendererMesh::PRIMITIVE_TRIANGLES:      glprim = GL_TRIANGLES;      break;
		case RendererMesh::PRIMITIVE_TRIANGLE_STRIP: glprim = GL_TRIANGLE_STRIP; break;
		case RendererMesh::PRIMITIVE_POINT_SPRITES:  glprim = GL_POINTS;         break;
		default: break;
	}
	RENDERER_ASSERT(glprim != ~(GLenum)0, "Unable to find GL Primitive type.");
	return glprim;
}

static GLenum getGLIndexType(RendererIndexBuffer::Format format)
{
	GLenum gltype = 0;
	switch(format)
	{
		case RendererIndexBuffer::FORMAT_UINT16: gltype = GL_UNSIGNED_SHORT; break;
		case RendererIndexBuffer::FORMAT_UINT32: gltype = GL_UNSIGNED_INT;   break;
		default: break;
	}
	RENDERER_ASSERT(gltype, "Unable to convert to GL Index Type.");
	return gltype;
}

GLES2RendererMesh::GLES2RendererMesh(GLES2Renderer& renderer, const RendererMeshDesc &desc) :
	RendererMesh(desc), m_renderer(renderer)
{
	
}

GLES2RendererMesh::~GLES2RendererMesh(void)
{
	
}

void GLES2RendererMesh::renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{
	const PxU32 indexSize = RendererIndexBuffer::getFormatByteSize(indexFormat);
	void *buffer = ((PxU8*) 0)+indexSize*firstIndex;
	glDrawElements(getGLPrimitive(getPrimitives()), numIndices, getGLIndexType(indexFormat), buffer);
}

void GLES2RendererMesh::renderVertices(PxU32 numVertices, RendererMaterial *material) const
{
	RendererMesh::Primitive primitive = getPrimitives();
	if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) glDepthMask(false);
	glDrawArrays(getGLPrimitive(primitive), 0, numVertices);
	if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) glDepthMask(true);
	}

void GLES2RendererMesh::renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{
	RENDERER_ASSERT(0, "TODO")
}

void GLES2RendererMesh::renderVerticesInstanced(PxU32 numVertices, RendererMaterial *material) const
{
	RENDERER_ASSERT(0, "TODO")
}

}
#endif // #if defined(RENDERER_ENABLE_GLES2)
		
