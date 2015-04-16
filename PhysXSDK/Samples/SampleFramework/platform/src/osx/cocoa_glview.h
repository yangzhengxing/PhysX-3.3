/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef COCOA_GLVIEW_H
#define COCOA_GLVIEW_H

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#include <RendererWindow.h>

@interface CocoaGLView : NSOpenGLView
{
	@private
		SampleRenderer::RendererWindow* m_rendererWindow;
}

- (id)initWithRenderWindow:(SampleRenderer::RendererWindow*)renderWindow;

- (void)dealloc;
- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)flushBuffer;
- (void)reshape;

@end 

#endif 
