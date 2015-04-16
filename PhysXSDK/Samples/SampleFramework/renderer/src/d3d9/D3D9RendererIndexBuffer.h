/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_INDEXBUFFER_H
#define D3D9_RENDERER_INDEXBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererIndexBuffer.h>
#include "D3D9Renderer.h"

namespace SampleRenderer
{

	class D3D9RendererIndexBuffer : public RendererIndexBuffer, public D3D9RendererResource
	{
	public:
		D3D9RendererIndexBuffer(IDirect3DDevice9 &d3dDevice, D3D9Renderer& renderer, const RendererIndexBufferDesc &desc);
		virtual ~D3D9RendererIndexBuffer(void);

	public:
		virtual void *lock(void);
		virtual void  unlock(void);

	private:
		virtual void bind(void) const;
		virtual void unbind(void) const;

		virtual void onDeviceLost(void);
		virtual void onDeviceReset(void);

	private:
		IDirect3DDevice9      &m_d3dDevice;
		IDirect3DIndexBuffer9 *m_d3dIndexBuffer;

		DWORD                         m_usage;
		D3DPOOL                       m_pool;
		UINT                          m_bufferSize;
		D3DFORMAT					  m_format;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
