/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef D3D11_RENDERER_INDEXBUFFER_H
#define D3D11_RENDERER_INDEXBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererIndexBuffer.h>
#include "D3D11Renderer.h"

namespace SampleRenderer
{

class D3D11RendererIndexBuffer : public RendererIndexBuffer, public D3D11RendererResource
{
	friend class D3D11Renderer;
public:
	D3D11RendererIndexBuffer(ID3D11Device& d3dDevice, ID3D11DeviceContext& d3dDeviceContext, const RendererIndexBufferDesc& desc, bool bUseMapForLocking = TRUE);
	virtual ~D3D11RendererIndexBuffer(void);

public:
	virtual void* lock(void);
	virtual void  unlock(void);

private:
	virtual void bind(void) const;
	virtual void unbind(void) const;

	virtual void onDeviceLost(void);
	virtual void onDeviceReset(void);

	void* internalLock(D3D11_MAP MapType);

private:
	ID3D11Device&                 m_d3dDevice;
	ID3D11DeviceContext&          m_d3dDeviceContext;
	ID3D11Buffer*                 m_d3dIndexBuffer;
	D3D11_BUFFER_DESC             m_d3dBufferDesc;
	DXGI_FORMAT                   m_d3dBufferFormat;

	bool                          m_bUseMapForLocking;
	PxU8*                         m_buffer;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
