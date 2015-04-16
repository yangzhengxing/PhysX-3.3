/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H

#include <RendererConfig.h>

namespace SampleFramework {
	class SamplePlatform;
}

namespace SampleRenderer
{

	class RendererWindow
	{
	public:
		RendererWindow(void);
		virtual ~RendererWindow(void);

		bool open(PxU32 width, PxU32 height, const char *title, bool fullscreen=false);
		void close(void);

		bool isOpen(void) const;

		// update the window's state... handle messages, etc.
		void update(void);

		// resize the window...
		void setSize(PxU32 width, PxU32 height);

		// get/set the window's title...
		void getTitle(char *title, PxU32 maxLength) const;
		void setTitle(const char *title);

		bool	hasFocus() const;
		void	setFocus(bool b);

		SampleFramework::SamplePlatform* getPlatform() { return m_platform; }
	public:
		// called just AFTER the window opens.
		virtual void onOpen(void) {}

		// called just BEFORE the window closes. return 'true' to confirm the window closure.
		virtual bool onClose(void) { return true; }

		// called just AFTER the window is resized.
		virtual void onResize(PxU32 /*width*/, PxU32 /*height*/) {}

		// called when the window's contents needs to be redrawn.
		virtual void onDraw(void) = 0;

	protected:
		SampleFramework::SamplePlatform*				m_platform;

	private:
		bool											m_isOpen;
	};

} // namespace SampleRenderer

#endif
