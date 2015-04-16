/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D11_RENDERER_VERTEXBUFFER_H
#define D3D11_RENDERER_VERTEXBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererVertexBuffer.h>
#include "D3D11Renderer.h"

namespace SampleRenderer
{

class D3D11RendererVertexBuffer : public RendererVertexBuffer, public D3D11RendererResource
{
	friend class D3D11Renderer;
public:
	D3D11RendererVertexBuffer(ID3D11Device& d3dDevice, ID3D11DeviceContext& d3dDeviceContext, const RendererVertexBufferDesc& desc, bool bUseMapForLocking = TRUE);
	virtual ~D3D11RendererVertexBuffer(void);

	void addVertexElements(PxU32 streamIndex, std::vector<D3D11_INPUT_ELEMENT_DESC> &vertexElements) const;

	virtual bool checkBufferWritten(void);

protected:
	virtual void  swizzleColor(void* colors, PxU32 stride, PxU32 numColors, RendererVertexBuffer::Format inFormat);

	virtual void* lock(void);
	virtual void  unlock(void);

	virtual void  bind(PxU32 streamID, PxU32 firstVertex);
	virtual void  unbind(PxU32 streamID);

private:
	virtual void onDeviceLost(void);
	virtual void onDeviceReset(void);

	void* internalLock(D3D11_MAP MapType);

private:
	ID3D11Device&                 m_d3dDevice;
	ID3D11DeviceContext&          m_d3dDeviceContext;
	ID3D11Buffer*                 m_d3dVertexBuffer;
	D3D11_BUFFER_DESC             m_d3dBufferDesc;
	bool                          m_bUseMapForLocking;
	PxU8*                         m_buffer;
	bool                          m_bBufferWritten;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
