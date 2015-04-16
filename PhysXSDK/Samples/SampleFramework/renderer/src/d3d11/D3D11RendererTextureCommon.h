/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef D3D11_RENDERER_TEXTURE_COMMON_H
#define D3D11_RENDERER_TEXTURE_COMMON_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererTexture.h>
#include <RendererTextureDesc.h>
#include <SamplePlatform.h>

#include "D3D11RendererTraits.h"


namespace SampleRenderer
{

enum TEXTURE_BIND_FLAGS
{
	BIND_NONE     =  0,
	BIND_VERTEX   =  1 << D3DTypes::SHADER_VERTEX,
	BIND_GEOMETRY =  1 << D3DTypes::SHADER_GEOMETRY,
	BIND_PIXEL    =  1 << D3DTypes::SHADER_PIXEL,
	BIND_HULL     =  1 << D3DTypes::SHADER_HULL,
	BIND_DOMAIN   =  1 << D3DTypes::SHADER_DOMAIN,
	BIND_ALL      = (1 << D3DTypes::NUM_SHADER_TYPES) - 1
};

PX_INLINE PxU32 getBindFlags(D3DType d3dType) { return 1 << d3dType; }

PX_INLINE DXGI_FORMAT getD3D11TextureFormat(RendererTexture::Format format)
{
	DXGI_FORMAT dxgiFormat = static_cast<DXGI_FORMAT>(SampleFramework::SamplePlatform::platform()->getD3D11TextureFormat(format));
	RENDERER_ASSERT(dxgiFormat != DXGI_FORMAT_UNKNOWN, "Unable to convert to D3D11 Texture Format.");
	return dxgiFormat;
}

PX_INLINE D3D11_FILTER getD3D11TextureFilter(RendererTexture::Filter filter)
{
	D3D11_FILTER d3dFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	switch (filter)
	{
	case RendererTexture2D::FILTER_NEAREST:
		d3dFilter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case RendererTexture2D::FILTER_LINEAR:
		d3dFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case RendererTexture2D::FILTER_ANISOTROPIC:
		d3dFilter = D3D11_FILTER_ANISOTROPIC;
		break;
	default:
		RENDERER_ASSERT(0, "Unable to convert to D3D11 Filter mode.");
	}
	return d3dFilter;
}

PX_INLINE D3D11_TEXTURE_ADDRESS_MODE getD3D11TextureAddressing(RendererTexture2D::Addressing addressing)
{
	D3D11_TEXTURE_ADDRESS_MODE d3dAddressing = (D3D11_TEXTURE_ADDRESS_MODE)0;
	switch (addressing)
	{
	case RendererTexture2D::ADDRESSING_WRAP:
		d3dAddressing = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case RendererTexture2D::ADDRESSING_CLAMP:
		d3dAddressing = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case RendererTexture2D::ADDRESSING_MIRROR:
		d3dAddressing = D3D11_TEXTURE_ADDRESS_MIRROR;
		break;
	}
	RENDERER_ASSERT(d3dAddressing != 0, "Unable to convert to D3D11 Addressing mode.");
	return d3dAddressing;
}

}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)

#endif
