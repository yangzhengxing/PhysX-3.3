/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef COCOA_WINDOW_H
#define COCOA_WINDOW_H

#include <Cocoa/Cocoa.h>
#include <RendererWindow.h>
#include "cocoa_glview.h"

@interface CocoaWindow : NSWindow
{
  @public
	SampleRenderer::RendererWindow *m_rendererWindow;
	CocoaGLView *m_glview;
	int m_modifyerState;
}

- (BOOL)canBecomeKeyWindow;
- (void)close;
- (BOOL)acceptsMouseMovedEvents;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)rightMouseUp:(NSEvent *)theEvent;
- (void)rightMouseDragged:(NSEvent *)theEvent;
- (void)otherMouseDown:(NSEvent *)theEvent;
- (void)otherMouseUp:(NSEvent *)theEvent;
- (void)otherMouseDragged:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)handleMouse:(NSEvent *)theEvent;

- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)flagsChanged:(NSEvent *)theEvent;
- (void)handleKeyboard:(NSEvent *)theEvent;

- (void)windowResignKey:(NSNotification *)notification;






@end 


#endif 
