/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_INSTANCEBUFFER_H
#define D3D9_RENDERER_INSTANCEBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererInstanceBuffer.h>
#include "D3D9Renderer.h"

namespace SampleRenderer
{

	class D3D9RendererInstanceBuffer : public RendererInstanceBuffer, public D3D9RendererResource
	{
	public:
		D3D9RendererInstanceBuffer(IDirect3DDevice9 &d3dDevice, D3D9Renderer& renderer, const RendererInstanceBufferDesc &desc);
		virtual ~D3D9RendererInstanceBuffer(void);

		void addVertexElements(PxU32 streamIndex, std::vector<D3DVERTEXELEMENT9> &vertexElements) const;

	protected:
		virtual void *lock(void);
		virtual void  unlock(void);

		virtual void  bind(PxU32 streamID, PxU32 firstInstance) const;
		virtual void  unbind(PxU32 streamID) const;

	private:
		virtual void onDeviceLost(void);
		virtual void onDeviceReset(void);

	private:
#if RENDERER_INSTANCING
		IDirect3DDevice9       &m_d3dDevice;
		IDirect3DVertexBuffer9 *m_d3dVertexBuffer;
#else
		void					*mInstanceBuffer;
#endif
		DWORD                   m_usage;
		D3DPOOL                 m_pool;
		UINT                    m_bufferSize;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
