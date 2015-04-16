/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef RENDERER_TARGET_H
#define RENDERER_TARGET_H

namespace SampleRenderer
{

	class RendererTarget
	{
		friend class Renderer;
	public:
		RendererTarget(void);
		virtual ~RendererTarget(void);

		void release(void) { delete this; }

	private:
		virtual void bind(void)=0;
		virtual void unbind(void)=0;
	};

} // namespace SampleRenderer

#endif
