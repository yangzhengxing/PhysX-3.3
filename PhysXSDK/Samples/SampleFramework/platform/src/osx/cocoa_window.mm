
#include "cocoa_window.h"
#include "cocoa_app.h"
#include "cocoa_glview.h"
#include "RendererWindow.h"
#include <Carbon/Carbon.h>
#include "osx/OSXSamplePlatform.h"
#include "osx/OSXSampleUserInput.h"

using namespace SampleFramework;

@implementation CocoaWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (void)close
{
    [super close];
    [NSApp terminate:nil];
}

- (BOOL)acceptsMouseMovedEvents
{
	return YES;
}

- (void)mouseDown:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)mouseUp:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)otherMouseDown:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)mouseDragged:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)mouseMoved:(NSEvent *)theEvent
{
	[self handleMouse: theEvent];
}

- (void)keyDown:(NSEvent *)theEvent
{
	[self handleKeyboard: theEvent];
}

- (void)keyUp:(NSEvent *)theEvent
{
	[self handleKeyboard: theEvent];
}

- (void)flagsChanged:(NSEvent *)theEvent
{
	OSXSampleUserInput&	userInput = ((OSXPlatform*)m_rendererWindow->getPlatform())->getOSXSampleUserInput();
	
	int flags = [theEvent modifierFlags];
	int change = flags ^ m_modifyerState;
	
	if (change & NSAlternateKeyMask)
	{
		(flags & NSAlternateKeyMask) ? userInput.doOnKeyDown(kVK_Option, 0) : userInput.doOnKeyUp(kVK_Option, 0);
	}
	
	if (change & NSControlKeyMask)
	{
		(flags & NSControlKeyMask) ? userInput.doOnKeyDown(kVK_Control, 0) : userInput.doOnKeyUp(kVK_Control, 0);
	}
	
	if (change & NSCommandKeyMask)
	{
		(flags & NSCommandKeyMask) ? userInput.doOnKeyDown(kVK_Command, 0) : userInput.doOnKeyUp(kVK_Command, 0);
	}
	
	if (change & NSShiftKeyMask)
	{
		(flags & NSShiftKeyMask) ? userInput.doOnKeyDown(kVK_Shift, 0) : userInput.doOnKeyUp(kVK_Shift, 0);
	}
	
	m_modifyerState = flags; 
	
}


- (void)handleMouse:(NSEvent *)theEvent
{
	OSXPlatform* platform = (OSXPlatform*)m_rendererWindow->getPlatform();
	OSXSampleUserInput&	userInput = platform->getOSXSampleUserInput();
	
	NSPoint event_location = [theEvent locationInWindow];
	
	switch ([theEvent type]) 
	{
		case NSLeftMouseUp:
			userInput.doOnMouseUp(event_location.x, event_location.y, MOUSE_BUTTON_LEFT);
			break;
		case NSRightMouseUp:
			userInput.doOnMouseUp(event_location.x, event_location.y, MOUSE_BUTTON_RIGHT);
			break;
		case NSOtherMouseUp:
			userInput.doOnMouseUp(event_location.x, event_location.y, MOUSE_BUTTON_CENTER);
			break;
		case NSLeftMouseDown:
			{
				if (!platform->hasContentFocus())
				{
					platform->enableContentFocus(true);
				}
				else
				{
					userInput.doOnMouseDown(event_location.x, event_location.y, MOUSE_BUTTON_LEFT);
				}
			}
			break;
		case NSRightMouseDown:
			userInput.doOnMouseDown(event_location.x, event_location.y, MOUSE_BUTTON_RIGHT);
			break;
		case NSOtherMouseDown:
			userInput.doOnMouseDown(event_location.x, event_location.y, MOUSE_BUTTON_CENTER);
			break;
		case NSLeftMouseDragged:
		case NSRightMouseDragged:
		case NSOtherMouseDragged:
		case NSMouseMoved:
			if (platform->getMouseCursorRecentering())
			{
				platform->recenterMouseCursor(true);				
			}
			else
			{
				physx::PxU32 width, height;
				platform->getWindowSize(width, height);
				physx::PxVec2 currentPos(event_location.x, static_cast<physx::PxReal>(height) - event_location.y);
				physx::PxVec2 diff = currentPos - platform->getMouseCursorPos();
				userInput.doOnMouseMove(currentPos.x, static_cast<physx::PxReal>(height)-currentPos.y, diff.x, -diff.y, MOUSE_MOVE);
				platform->setMouseCursorPos(currentPos);
			}
			break;
	}
}

- (void)handleKeyboard:(NSEvent *)theEvent
{
	OSXSampleUserInput&	userInput = ((OSXPlatform*)m_rendererWindow->getPlatform())->getOSXSampleUserInput();
	
	unsigned short osxCode = [theEvent keyCode];
	NSString* charString = [theEvent characters];
	char charBuffer[16];
	[charString getCString:charBuffer maxLength:16 encoding:[NSString defaultCStringEncoding]];
	bool isDown = [theEvent type] == NSKeyDown;
	
	if (isDown)
	{
		userInput.doOnKeyDown(osxCode, charBuffer[0]);
	}
	else 
	{
		userInput.doOnKeyUp(osxCode, charBuffer[0]);
	}
}

- (void)windowResignKey:(NSNotification *)notification
{
	((OSXPlatform*)m_rendererWindow->getPlatform())->enableContentFocus(false);
}



@end 


namespace SampleRenderer
{
	
	CocoaGLView *glview = 0;
	CocoaWindow *window = 0;
	
	void createWindow(PxU32 width, PxU32 height) // called from OGLRenderer::OGLRenderer(..)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NSApp = [CocoaApp sharedApplication];
		
		NSUInteger syleMask = NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask;
		
		window = [[CocoaWindow alloc]             initWithContentRect:NSMakeRect(0,0,width,height)
															styleMask:syleMask
															  backing:NSBackingStoreBuffered
																defer:TRUE];
		
		[window setTitle:@"SampleFramework"];
		[window setAcceptsMouseMovedEvents:TRUE];
		//sschirm: unfortunately this doesn't seem to prevent the gl view to clear the bottom bar we could use for resizing
		[window setAutorecalculatesContentBorderThickness:NO forEdge:NSMinYEdge];
		[window setContentBorderThickness:24.0 forEdge:NSMinYEdge];
        [window center];
		
		[[NSNotificationCenter defaultCenter] addObserver: window selector: @selector(windowResignKey:) name:NSWindowDidResignKeyNotification object:nil];
		
		[pool release];
	}
    
    void createGLView(SampleRenderer::RendererWindow *w) // called from OGLRenderer::OGLRenderer(..)
	{
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		window->m_rendererWindow = w;
		
		glview = [[CocoaGLView alloc] initWithRenderWindow:w];
		
		window->m_glview = glview;
		window->m_modifyerState = 0;
		
		[window setContentView: glview];
		//[glview setFrame: NSMakeRect(0,24,400,400)];
		//[glview setBounds: NSMakeRect(0,200,400,400)];
		
        [window orderFrontRegardless];
        [window makeKeyAndOrderFront: nil];       // triggers a callback to drawRect
		
        [pool release];
	}
	
	void releaseWindow(void)
	{
		
	}
	
	bool updateWindow(void)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
		[glview setNeedsDisplay:YES];

		[pool release];
		
		return [NSApp isRunning];
	}
	
	void emitEvents()
	{
		[NSApp runOnce: FALSE];
	}
	
	void getWindowSize(physx::PxU32& width, physx::PxU32& height)
	{
		NSRect bounds = [glview bounds];
		width = NSWidth(bounds);
		height = NSHeight(bounds);
	}
	
	void swapBuffers(void)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		
		[glview flushBuffer];
		
		[pool release];
	}
	
	bool isKeyWindow()
	{
		return [window isKeyWindow];
	}
	
	CGPoint getMousePosition()
	{
		CGEventRef event = CGEventCreate(nil);
		CGPoint loc = CGEventGetLocation(event);
		CFRelease(event);
		return loc;
	}
	
	CGPoint getViewCenter()
	{
		//compute view center
		NSRect viewBounds = [glview bounds];
		NSPoint viewBoundsCenter = NSMakePoint(viewBounds.origin.x + viewBounds.size.width/2, viewBounds.origin.y + viewBounds.size.height/2);
	
		//transform to window coordinates
		NSPoint windowPoint = [glview convertPoint:viewBoundsCenter toView:nil];
		
		//transform to flipped global display coords (we need to flip the result to get coords 
		//compatible with CGEventGetLocation and CGWarpMouseCursorPosition)
		//use screen 0 for global display coords
		NSPoint screenPoint = [window convertBaseToScreen:windowPoint];
		NSScreen* screen0 = [[NSScreen screens] objectAtIndex:0];
		NSPoint globalDisplayCenter = NSMakePoint(screenPoint.x, screen0.frame.size.height - screenPoint.y);
		
		return CGPointMake(globalDisplayCenter.x, globalDisplayCenter.y);
	}
	
	void setTitle(const char* title)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		NSString* nsTitle = [[NSString alloc] initWithUTF8String:title];
		[window setTitle: nsTitle];
		[pool release];
	}
	
	void getTitle(char* title, PxU32 maxLen)
	{
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
		const char* windowTitle = [window.title UTF8String];
		strlcpy(title, windowTitle, maxLen);
		[pool release];
	}
	
} // namespace SampleRenderer
