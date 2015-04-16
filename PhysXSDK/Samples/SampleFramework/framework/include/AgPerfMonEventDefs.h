/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


// This file is used to define a list of AgPerfMon events.
//
// This file is included exclusively by AgPerfMonEventSrcAPI.h
// and by AgPerfMonEventSrcAPI.cpp, for the purpose of building
// an enumeration (enum xx) and an array of strings ()
// that contain the list of events.
//
// This file should only contain event definitions, using the
// DEFINE_EVENT macro.  E.g.:
//
//     DEFINE_EVENT(sample_name_1)
//     DEFINE_EVENT(sample_name_2)
//     DEFINE_EVENT(sample_name_3)


// Statistics from the fluid mesh packet cooker
DEFINE_EVENT(renderFunction)
DEFINE_EVENT(SampleRendererVBwriteBuffer)
DEFINE_EVENT(SampleOnTickPreRender)
DEFINE_EVENT(SampleOnTickPostRender)
DEFINE_EVENT(SampleOnRender)
DEFINE_EVENT(SampleOnDraw)
DEFINE_EVENT(D3D9Renderer_createVertexBuffer)
DEFINE_EVENT(Renderer_render)
DEFINE_EVENT(Renderer_render_depthOnly)
DEFINE_EVENT(Renderer_render_deferred)
DEFINE_EVENT(Renderer_render_lit)
DEFINE_EVENT(Renderer_render_unlit)
DEFINE_EVENT(Renderer_renderMeshes)
DEFINE_EVENT(Renderer_renderDeferredLights)
DEFINE_EVENT(D3D9RendererMesh_renderIndices)
DEFINE_EVENT(D3D9RendererMesh_renderVertices)
DEFINE_EVENT(D3D9Renderer_createIndexBuffer)
DEFINE_EVENT(D3D9RendererMesh_renderVerticesInstanced)
DEFINE_EVENT(D3D9Renderer_createInstanceBuffer)
DEFINE_EVENT(D3D9Renderer_createTexture2D)
DEFINE_EVENT(D3D9Renderer_createTarget)
DEFINE_EVENT(D3D9Renderer_createMaterial)
DEFINE_EVENT(D3D9Renderer_createMesh)
DEFINE_EVENT(D3D9Renderer_createLight)
DEFINE_EVENT(D3D9RendererMesh_renderIndicesInstanced)
DEFINE_EVENT(OGLRenderer_createVertexBuffer)
DEFINE_EVENT(OGLRenderer_createIndexBuffer)
DEFINE_EVENT(OGLRenderer_createInstanceBuffer)
DEFINE_EVENT(OGLRenderer_createTexture2D)
DEFINE_EVENT(OGLRenderer_createTarget)
DEFINE_EVENT(OGLRenderer_createMaterial)
DEFINE_EVENT(OGLRenderer_createMesh)
DEFINE_EVENT(OGLRenderer_createLight)
DEFINE_EVENT(OGLRendererMaterial_compile_vertexProgram)
DEFINE_EVENT(OGLRendererMaterial_load_vertexProgram)
DEFINE_EVENT(OGLRendererMaterial_compile_fragmentProgram)
DEFINE_EVENT(OGLRendererMaterial_load_fragmentProgram)
DEFINE_EVENT(OGLRendererVertexBufferBind)
DEFINE_EVENT(OGLRendererSwapBuffers)
DEFINE_EVENT(writeBufferSemanticStride)
DEFINE_EVENT(writeBufferfixUV)
DEFINE_EVENT(writeBufferConvertFromApex)
DEFINE_EVENT(writeBufferGetFormatSemantic)
DEFINE_EVENT(writeBufferlockSemantic)
DEFINE_EVENT(OGLRendererVertexBufferLock)
DEFINE_EVENT(Renderer_meshRenderLast)
DEFINE_EVENT(Renderer_atEnd)
DEFINE_EVENT(renderMeshesBindMeshContext)
DEFINE_EVENT(renderMeshesFirstIf)
DEFINE_EVENT(renderMeshesSecondIf)
DEFINE_EVENT(renderMeshesThirdIf)
DEFINE_EVENT(renderMeshesForthIf)
DEFINE_EVENT(OGLRendererBindMeshContext)
DEFINE_EVENT(OGLRendererBindMeshcg)
DEFINE_EVENT(cgGLSetMatrixParameter)
DEFINE_EVENT(D3D9RenderVBlock)
DEFINE_EVENT(D3D9RenderVBunlock)
DEFINE_EVENT(D3D9RenderIBlock)
DEFINE_EVENT(D3D9RenderIBunlock)
