/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef OSX_SAMPLE_PLATFORM_H
#define OSX_SAMPLE_PLATFORM_H

#include <SamplePlatform.h>
#include <osx/OSXSampleUserInput.h>

namespace SampleFramework
{
	class OSXPlatform : public SamplePlatform
	{
	public:
		explicit							OSXPlatform(SampleRenderer::RendererWindow* _app);
		// System
		virtual void						setCWDToEXE(void);
		virtual bool						makeSureDirectoryPathExists(const char* dirPath);
		
		// Rendering
		virtual void						initializeOGLDisplay(const SampleRenderer::RendererDesc& desc,
															physx::PxU32& width,
															physx::PxU32& height);
		virtual void						postInitializeOGLDisplay();
		virtual void						postRendererSetup(SampleRenderer::Renderer* renderer);
		virtual void						setupRendererDescription(SampleRenderer::RendererDesc& renDesc);
		virtual	bool						hasFocus() const;
		virtual	void						getTitle(char *title, physx::PxU32 maxLength) const;
		virtual	void						setTitle(const char *title);
		virtual const char*					getPlatformName() const { return "osx"; }
		virtual	bool						updateWindow();
        virtual void						update();
        virtual bool						openWindow(physx::PxU32& width, 
                                                       physx::PxU32& height,
                                                       const char* title,
                                                       bool fullscreen);
		virtual void						getWindowSize(physx::PxU32& width, physx::PxU32& height);
		virtual const char*					getPathSeparator();
		virtual	void						freeDisplay();
		virtual void						swapBuffers();
		
		virtual void						showCursor(bool);
		
		virtual void						showMessage(const char* title, const char* message);


		virtual	void*						compileProgram(void * context,
														  const char* assetDir,
														  const char *programPath,
														  physx::PxU64 profile,
														  const char* passString,
														  const char *entry,
														   const char **args);

		// Input
		virtual void						doInput();
		
		virtual const SampleUserInput*		getSampleUserInput() const { return &mOSXSampleUserInput; }
		virtual SampleUserInput*			getSampleUserInput() { return &mOSXSampleUserInput; }
	
		virtual void						setMouseCursorRecentering(bool val);
		virtual bool						getMouseCursorRecentering() const;
		
		physx::PxVec2						getMouseCursorPos() const { return mMouseCursorPos; }
		void								setMouseCursorPos(const physx::PxVec2& pos) { mMouseCursorPos = pos; }
		void								recenterMouseCursor(bool generateEvent);

		OSXSampleUserInput&					getOSXSampleUserInput() { return mOSXSampleUserInput; }
		const OSXSampleUserInput&			getOSXSampleUserInput() const { return mOSXSampleUserInput; }
		
		void								enableContentFocus(bool val);
		bool								hasContentFocus() { return mHasContentFocus; }	
		
	protected:
		OSXSampleUserInput					mOSXSampleUserInput;
		bool								mHasContentFocus;
		bool								mHideMouseCursor;
		physx::PxVec2						mMouseCursorPos;
		bool								mRecenterMouseCursor;
	};
}

#endif
