/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D11_RENDERER_MESH_H
#define D3D11_RENDERER_MESH_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererMesh.h>
#include "D3D11Renderer.h"

namespace SampleRenderer
{
class D3D11RendererMaterial;

class D3D11RendererMesh : public RendererMesh
{
	friend class D3D11Renderer;
	
public:
	D3D11RendererMesh(D3D11Renderer& renderer, const RendererMeshDesc& desc);
	virtual ~D3D11RendererMesh(void);

protected:
	virtual void renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial* material) const;
	virtual void renderVertices(PxU32 numVertices, RendererMaterial* material) const;

	virtual void renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial* material) const;
	virtual void renderVerticesInstanced(PxU32 numVertices, RendererMaterial* material) const;

	D3D11RendererMesh& operator=(const D3D11RendererMesh&) { return *this; }

	Renderer& renderer() { return m_renderer; }

private:
	void         bind(void) const;
	void         render(RendererMaterial* material) const;

	void setTopology(const Primitive& primitive, bool bTessellationEnabled) const;
	void setLayout(const RendererMaterial*, bool bInstanced) const;
	void setSprites(bool bEnabled) const;
	void setNumVerticesAndIndices(PxU32 numIndices, PxU32 numVertices);

	ID3D11InputLayout* getInputLayoutForMaterial(const D3D11RendererMaterial*, bool bInstanced) const;

private:
	class ScopedMeshRender;
	friend class ScopedMeshRender;

	typedef std::vector<D3D11_INPUT_ELEMENT_DESC> LayoutVector;

	D3D11Renderer&           m_renderer;

	LayoutVector             m_inputDescriptions;
	LayoutVector             m_instancedInputDescriptions;
	PxU64                    m_inputHash;
	PxU64                    m_instancedInputHash;

	// This is merely for cleanup, and has no effect on externally visible state
	mutable bool             m_bPopStates;

	std::string              m_spriteShaderPath;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
