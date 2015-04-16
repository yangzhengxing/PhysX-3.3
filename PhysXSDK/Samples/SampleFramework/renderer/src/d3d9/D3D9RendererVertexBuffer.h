/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_VERTEXBUFFER_H
#define D3D9_RENDERER_VERTEXBUFFER_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererVertexBuffer.h>
#include "D3D9Renderer.h"

namespace SampleRenderer
{

	class D3D9RendererVertexBuffer : public RendererVertexBuffer, public D3D9RendererResource
	{
	public:
		D3D9RendererVertexBuffer(IDirect3DDevice9 &d3dDevice, D3D9Renderer& renderer, const RendererVertexBufferDesc &desc);
		virtual ~D3D9RendererVertexBuffer(void);

		void addVertexElements(PxU32 streamIndex, std::vector<D3DVERTEXELEMENT9> &vertexElements) const;

		virtual bool checkBufferWritten(void);

	protected:
		virtual void  swizzleColor(void *colors, PxU32 stride, PxU32 numColors, RendererVertexBuffer::Format inFormat);

		virtual void *lock(void);
		virtual void  unlock(void);

		virtual void  bind(PxU32 streamID, PxU32 firstVertex);
		virtual void  unbind(PxU32 streamID);

	private:
		virtual void onDeviceLost(void);
		virtual void onDeviceReset(void);

	private:
		IDirect3DDevice9             &m_d3dDevice;
		IDirect3DVertexBuffer9       *m_d3dVertexBuffer;

		DWORD                         m_usage;
		DWORD                         m_lockFlags;
		D3DPOOL                       m_pool;
		UINT                          m_bufferSize;

		bool                          m_bufferWritten;
		void*						  m_savedData;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
