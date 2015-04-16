/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D9_RENDERER_TEXTURE_2D_H
#define D3D9_RENDERER_TEXTURE_2D_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include <RendererTexture2D.h>
#include "D3D9Renderer.h"

namespace SampleRenderer
{
	class D3D9Renderer;
	class D3D9RendererTexture2D : public RendererTexture2D, public D3D9RendererResource
	{
		friend class D3D9RendererTarget;
		friend class D3D9RendererSpotLight;
	public:
		D3D9RendererTexture2D(IDirect3DDevice9 &d3dDevice, D3D9Renderer& renderer, const RendererTexture2DDesc &desc);
		virtual ~D3D9RendererTexture2D(void);

	public:
		virtual void *lockLevel(PxU32 level, PxU32 &pitch);
		virtual void  unlockLevel(PxU32 level);

		void bind(PxU32 samplerIndex);

		virtual	void	select(PxU32 stageIndex)
		{
			bind(stageIndex);
		}

	private:

		virtual void onDeviceLost(void);
		virtual void onDeviceReset(void);

	private:
		IDirect3DDevice9          &m_d3dDevice;
		IDirect3DTexture9         *m_d3dTexture;

		DWORD                      m_usage;
		D3DPOOL                    m_pool;
		D3DFORMAT                  m_format;

		D3DTEXTUREFILTERTYPE       m_d3dMinFilter;
		D3DTEXTUREFILTERTYPE       m_d3dMagFilter;
		D3DTEXTUREFILTERTYPE       m_d3dMipFilter;
		D3DTEXTUREADDRESS          m_d3dAddressingU;
		D3DTEXTUREADDRESS          m_d3dAddressingV;
	};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
#endif
