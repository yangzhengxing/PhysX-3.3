/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef LINUX_SAMPLE_PLATFORM_H
#define LINUX_SAMPLE_PLATFORM_H

#include <SamplePlatform.h>
#include <linux/LinuxSampleUserInput.h>

#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h> 

#if defined(RENDERER_ENABLE_OPENGL)
	#define GLEW_STATIC
	#include <GL/glew.h>
#endif

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace SampleFramework
{
	class LinuxPlatform : public SamplePlatform 
	{
	public:
		explicit							LinuxPlatform(SampleRenderer::RendererWindow* _app);
		// System
		virtual void						showCursor(bool);
		virtual void						setCWDToEXE(void);
		const char*							getPathSeparator();
		bool								makeSureDirectoryPathExists(const char* dirPath);
		void								showMessage(const char* title, const char* message);
		// Rendering
		virtual void						initializeOGLDisplay(const SampleRenderer::RendererDesc& desc,
															physx::PxU32& width, 
															physx::PxU32& height);
		virtual void						postInitializeOGLDisplay();
		virtual void						postRendererSetup(SampleRenderer::Renderer* renderer);
		virtual void						setupRendererDescription(SampleRenderer::RendererDesc& renDesc);
		virtual	bool						hasFocus() const;
		virtual void						setFocus(bool b);
		virtual	void						getTitle(char *title, physx::PxU32 maxLength) const;
		virtual	void						setTitle(const char *title);
		virtual	bool						updateWindow();
		virtual bool						openWindow(physx::PxU32& width, 
														physx::PxU32& height,
														const char* title,
														bool fullscreen);
		virtual void						getWindowSize(physx::PxU32& width, physx::PxU32& height);
		virtual void						update();
		virtual bool						closeWindow();
		virtual	void						freeDisplay();
		virtual void						swapBuffers();
		
		virtual	void*						compileProgram(void * context, 
														  const char* assetDir, 
														  const char *programPath, 
														  physx::PxU64 profile, 
														  const char* passString, 
														  const char *entry, 
														   const char **args);
		
		// Input
		virtual void						doInput();
														   
		virtual const SampleUserInput*		getSampleUserInput() const 		{ return &m_linuxSampleUserInput; }
		virtual SampleUserInput*			getSampleUserInput()			{ return &m_linuxSampleUserInput; }

		virtual const char*					getPlatformName() const 		{ return "linux"; }
		
		virtual void						setMouseCursorRecentering(bool val);
		virtual bool						getMouseCursorRecentering() const;
		
		physx::PxVec2						getMouseCursorPos() const { return m_mouseCursorPos; }
		void								setMouseCursorPos(const physx::PxVec2& pos) { m_mouseCursorPos = pos; }
		void								recenterMouseCursor(bool generateEvent);

		LinuxSampleUserInput&				getLinuxSampleUserInput() 		{ return m_linuxSampleUserInput; }
		const LinuxSampleUserInput&			getLinuxSampleUserInput() const { return m_linuxSampleUserInput; }
		
	protected:
		bool								filterKeyRepeat(const XEvent& keyReleaseEvent);
		void								handleMouseEvent(const XEvent& event);
		void								showCursorInternal(bool show);
		
	protected:
		Display*							m_display;
		XVisualInfo*						m_visualInfo;
		Window                				m_window;
		Atom								m_wmDelete;
		GLXContext             				m_glxContext;
		XF86VidModeModeInfo					m_desktopMode;
		int 								m_screen;  
		bool								m_isFullScreen;
		bool								m_hasFocus;
		bool								m_hasContentFocus;
		physx::PxU32						m_windowWidth;
		physx::PxU32						m_windowHeight;
		LinuxSampleUserInput				m_linuxSampleUserInput;
		physx::PxVec2						m_mouseCursorPos;
		bool								m_recenterMouseCursor;
		bool								m_showCursor;
	};
}

#endif
