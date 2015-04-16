/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_OPENGL)

#include "OGLRendererMesh.h"

#include "OGLRendererInstanceBuffer.h"
#include "OGLRendererMaterial.h"

using namespace SampleRenderer;

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

OGLRendererMesh::OGLRendererMesh(OGLRenderer &renderer, const RendererMeshDesc &desc) 
:	RendererMesh(desc)
,	m_renderer(renderer)
{

}

OGLRendererMesh::~OGLRendererMesh(void)
{

}

void OGLRendererMesh::renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{
	const PxU32 indexSize = RendererIndexBuffer::getFormatByteSize(indexFormat);
	void *buffer = ((PxU8*)0)+indexSize*firstIndex;
	glDrawElements(getGLPrimitive(getPrimitives()), numIndices, getGLIndexType(indexFormat), buffer);
}

void OGLRendererMesh::renderVertices(PxU32 numVertices, RendererMaterial *material) const
{
	RendererMesh::Primitive primitive = getPrimitives();
	glDrawArrays(getGLPrimitive(primitive), 0, numVertices);
}

void OGLRendererMesh::renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{
	const OGLRendererInstanceBuffer *ib = static_cast<const OGLRendererInstanceBuffer*>(getInstanceBuffer());
	if(ib)
	{
		const PxU32 firstInstance = m_firstInstance;
		const PxU32 numInstances  = getNumInstances();

		const OGLRendererMaterial *currentMaterial = m_renderer.getCurrentMaterial();

		CGparameter modelMatrixParam     = m_renderer.getCGEnvironment().modelMatrix;
		CGparameter modelViewMatrixParam = m_renderer.getCGEnvironment().modelViewMatrix;

		if(currentMaterial && modelMatrixParam && modelViewMatrixParam)
		{
			for(PxU32 i=0; i<numInstances; i++)
			{
#if defined(RENDERER_ENABLE_CG)
				const physx::PxMat44 &model = ib->getModelMatrix(firstInstance+i);
				GLfloat glmodel[16];
				PxToGL(glmodel, model);

				physx::PxMat44 modelView = m_renderer.getViewMatrix() * model;
				GLfloat glmodelview[16];
				PxToGL(glmodelview, modelView);

				cgGLSetMatrixParameterfc(modelMatrixParam,     glmodel);
				cgGLSetMatrixParameterfc(modelViewMatrixParam, glmodelview);
#endif

				currentMaterial->bindMeshState(false);

				renderIndices(numVertices, firstIndex, numIndices, indexFormat, material);
			}
		}
	}
}

void OGLRendererMesh::renderVerticesInstanced(PxU32 numVertices, RendererMaterial *material) const
{
	const OGLRendererInstanceBuffer *ib = static_cast<const OGLRendererInstanceBuffer*>(getInstanceBuffer());
	if(ib)
	{
		const PxU32 firstInstance = m_firstInstance;
		const PxU32 numInstances  = getNumInstances();

		const OGLRendererMaterial *currentMaterial = m_renderer.getCurrentMaterial();

		CGparameter modelMatrixParam     = m_renderer.getCGEnvironment().modelMatrix;
		CGparameter modelViewMatrixParam = m_renderer.getCGEnvironment().modelViewMatrix;

		if(currentMaterial && modelMatrixParam && modelViewMatrixParam)
		{
			for(PxU32 i=0; i<numInstances; i++)
			{
#if defined(RENDERER_ENABLE_CG)
				const physx::PxMat44 &model = ib->getModelMatrix(firstInstance+i);
				GLfloat glmodel[16];
				PxToGL(glmodel, model);

				physx::PxMat44 modelView = m_renderer.getViewMatrix() * model;
				GLfloat glmodelview[16];
				PxToGL(glmodelview, modelView);

				cgGLSetMatrixParameterfc(modelMatrixParam,     glmodel);
				cgGLSetMatrixParameterfc(modelViewMatrixParam, glmodelview);
#endif

				currentMaterial->bindMeshState(false);

				renderVertices(numVertices, material);
			}
		}
	}
}

#endif // #if defined(RENDERER_ENABLE_OPENGL)
		
