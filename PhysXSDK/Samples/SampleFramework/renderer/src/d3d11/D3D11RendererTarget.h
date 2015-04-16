/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D11_RENDERER_TARGET_H
#define D3D11_RENDERER_TARGET_H

#include <RendererConfig.h>

#if defined(RENDERER_WINDOWS)
#define RENDERER_ENABLE_DIRECT3D11_TARGET
#endif

#if defined(RENDERER_ENABLE_DIRECT3D11) && defined(RENDERER_ENABLE_DIRECT3D11_TARGET)

#include <RendererTarget.h>
#include "D3D11Renderer.h"

namespace SampleRenderer
{
class D3D11RendererTexture2D;

class D3D11RendererTarget : public RendererTarget, public D3D11RendererResource
{
public:
	D3D11RendererTarget(ID3D11Device& d3dDevice, ID3D11DeviceContext& d3dDeviceContext, const RendererTargetDesc& desc);
	virtual ~D3D11RendererTarget(void);

private:
	D3D11RendererTarget& operator=(const D3D11RendererTarget&) {}
	virtual void bind(void);
	virtual void unbind(void);

private:
	virtual void onDeviceLost(void);
	virtual void onDeviceReset(void);

private:
	ID3D11Device&                        m_d3dDevice;
	ID3D11DeviceContext&                 m_d3dDeviceContext;

	std::vector<D3D11RendererTexture2D*> m_textures;
	D3D11RendererTexture2D*              m_depthStencilSurface;

	std::vector<ID3D11RenderTargetView*> m_d3dRTVs;
	std::vector<ID3D11RenderTargetView*> m_d3dLastRTVs;

	ID3D11DepthStencilView*              m_d3dDSV;
	ID3D11DepthStencilView*              m_d3dLastDSV;

	ID3D11RasterizerState*               m_d3dRS;
	ID3D11RasterizerState*               m_d3dLastRS;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11) && defined(RENDERER_ENABLE_DIRECT3D11_TARGET)
#endif
