/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include "D3D11RendererIndexBuffer.h"
#include <RendererIndexBufferDesc.h>

#if defined(PX_WINDOWS)
#include <pxtask/PxCudaContextManager.h>
#endif

using namespace SampleRenderer;

static DXGI_FORMAT getD3D11Format(RendererIndexBuffer::Format format)
{
	DXGI_FORMAT dxgiFormat = DXGI_FORMAT_UNKNOWN;
	switch (format)
	{
	case RendererIndexBuffer::FORMAT_UINT16:
		dxgiFormat = DXGI_FORMAT_R16_UINT;
		break;
	case RendererIndexBuffer::FORMAT_UINT32:
		dxgiFormat = DXGI_FORMAT_R32_UINT;
		break;
	}
	RENDERER_ASSERT(dxgiFormat != DXGI_FORMAT_UNKNOWN, "Unable to convert to DXGI_FORMAT.");
	return dxgiFormat;
}

D3D11RendererIndexBuffer::D3D11RendererIndexBuffer(ID3D11Device& d3dDevice, ID3D11DeviceContext& d3dDeviceContext, const RendererIndexBufferDesc& desc, bool bUseMapForLocking) :
	RendererIndexBuffer(desc),
	m_d3dDevice(d3dDevice),
	m_d3dDeviceContext(d3dDeviceContext),
	m_d3dIndexBuffer(NULL),
	m_bUseMapForLocking(bUseMapForLocking && (!desc.registerInCUDA)),
	m_buffer(NULL)
{
	memset(&m_d3dBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	m_d3dBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_d3dBufferDesc.ByteWidth = (UINT)(getFormatByteSize(desc.format) * desc.maxIndices);
	m_d3dBufferFormat = getD3D11Format(desc.format);

	if (m_bUseMapForLocking)
	{
		m_d3dBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_d3dBufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		m_d3dBufferDesc.CPUAccessFlags = 0;
		m_d3dBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
		m_buffer = new PxU8[m_d3dBufferDesc.ByteWidth];
		memset(m_buffer, 0, sizeof(PxU8)*m_d3dBufferDesc.ByteWidth);
	}

	onDeviceReset();

	if (m_d3dIndexBuffer)
	{
		m_maxIndices = desc.maxIndices;
	}

}

D3D11RendererIndexBuffer::~D3D11RendererIndexBuffer(void)
{
	if (m_d3dIndexBuffer)
	{
#if defined(PX_WINDOWS) && PX_SUPPORT_GPU_PHYSX
		if (m_interopContext && m_registeredInCUDA)
		{
			m_registeredInCUDA = !m_interopContext->unregisterResourceInCuda(m_InteropHandle);
		}
#endif
		m_d3dIndexBuffer->Release();
		m_d3dIndexBuffer = NULL;
	}

	delete [] m_buffer;
}


void D3D11RendererIndexBuffer::onDeviceLost(void)
{
	m_registeredInCUDA = false;

	if (m_d3dIndexBuffer)
	{
#if defined(PX_WINDOWS) && PX_SUPPORT_GPU_PHYSX
		if (m_interopContext && m_registeredInCUDA)
		{
			m_registeredInCUDA = !m_interopContext->unregisterResourceInCuda(m_InteropHandle);
		}
#endif
		m_d3dIndexBuffer->Release();
		m_d3dIndexBuffer = 0;
	}
}

void D3D11RendererIndexBuffer::onDeviceReset(void)
{
	if (!m_d3dIndexBuffer)
	{
		m_d3dDevice.CreateBuffer(&m_d3dBufferDesc, NULL, &m_d3dIndexBuffer);
		RENDERER_ASSERT(m_d3dIndexBuffer, "Failed to create DIRECT3D11 Index Buffer.");
#if defined(PX_WINDOWS) && PX_SUPPORT_GPU_PHYSX
		if (m_interopContext && m_d3dIndexBuffer && m_mustBeRegisteredInCUDA)
		{
			m_registeredInCUDA = m_interopContext->registerResourceInCudaD3D(m_InteropHandle, m_d3dIndexBuffer);
		}
#endif
	}
}

void* D3D11RendererIndexBuffer::lock(void)
{
	// For now NO_OVERWRITE is the only mapping that functions properly
	return internalLock(getHint() == HINT_STATIC ? /* D3D11_MAP_WRITE_DISCARD */ D3D11_MAP_WRITE_NO_OVERWRITE : D3D11_MAP_WRITE_NO_OVERWRITE);
}

void* D3D11RendererIndexBuffer::internalLock(D3D11_MAP MapType)
{
	void* buffer = 0;
	if (m_d3dIndexBuffer)
	{
		if (m_bUseMapForLocking)
		{
			D3D11_MAPPED_SUBRESOURCE mappedRead;
			m_d3dDeviceContext.Map(m_d3dIndexBuffer, 0, MapType, NULL, &mappedRead);
			RENDERER_ASSERT(mappedRead.pData, "Failed to lock DIRECT3D11 Index Buffer.");
			buffer = mappedRead.pData;	
		}
		else
		{
			buffer = m_buffer;
		}
	}
	return buffer;
}

void D3D11RendererIndexBuffer::unlock(void)
{
	if (m_d3dIndexBuffer)
	{
		if (m_bUseMapForLocking)
		{
			m_d3dDeviceContext.Unmap(m_d3dIndexBuffer, 0);
		}
		else
		{
			m_d3dDeviceContext.UpdateSubresource(m_d3dIndexBuffer, 0, NULL, m_buffer, m_d3dBufferDesc.ByteWidth, 0);
		}
	}
}

void D3D11RendererIndexBuffer::bind(void) const
{
	m_d3dDeviceContext.IASetIndexBuffer(m_d3dIndexBuffer, m_d3dBufferFormat, 0);
}

void D3D11RendererIndexBuffer::unbind(void) const
{
	m_d3dDeviceContext.IASetIndexBuffer(NULL, DXGI_FORMAT(), 0);
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
