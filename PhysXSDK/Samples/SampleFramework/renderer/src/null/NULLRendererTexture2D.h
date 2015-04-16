/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef NULL_RENDERER_TEXTURE_2D_H
#define NULL_RENDERER_TEXTURE_2D_H

#include <RendererConfig.h>

#include <RendererTexture2D.h>

namespace SampleRenderer
{

	class NullRendererTexture2D : public RendererTexture2D
	{
	public:
		NullRendererTexture2D(const RendererTexture2DDesc &desc);
		virtual ~NullRendererTexture2D(void);

	public:
		virtual void *lockLevel(PxU32 level, PxU32 &pitch);
		virtual void  unlockLevel(PxU32 level);

		void bind(PxU32 textureUnit);

		virtual	void	select(PxU32 stageIndex)
		{
			bind(stageIndex);
		}

	private:
		PxU8**				m_data;
		PxU32				m_numLevels;
		PxU32*				m_width;

	};

} // namespace SampleRenderer

#endif
