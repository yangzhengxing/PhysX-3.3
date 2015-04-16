
#include "cocoa_glview.h"

@implementation CocoaGLView
  
- (id)initWithRenderWindow:(SampleRenderer::RendererWindow*)renderWindow
{
	const NSOpenGLPixelFormatAttribute attrs[] =
    {
      NSOpenGLPFAAccelerated,
      NSOpenGLPFADoubleBuffer,
      NSOpenGLPFADepthSize,   24,
      NSOpenGLPFAStencilSize, 8,
      NSOpenGLPFAColorSize,   24,
      0
    };

    NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	self = [super initWithFrame:NSMakeRect(0,0,1,1) pixelFormat:format];
	m_rendererWindow = renderWindow;
    
    [[self openGLContext] makeCurrentContext];
	
	//turning off vsync doesn't seem to work like this
	//GLint vsync = 0;
	//[[self openGLContext] setValues:&vsync forParameter:NSOpenGLCPSwapInterval];
	
    return self;
}
  
- (void)dealloc
{
	[super dealloc];
}
  
- (void)drawRect:(NSRect)rect
{
	[super drawRect:rect];
}

- (void)flushBuffer
{
	[[self openGLContext] flushBuffer];
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
	[super.window rightMouseDown: theEvent];
}
  
- (void)reshape
{
	NSRect bounds = [self bounds];
	m_rendererWindow->onResize(NSWidth(bounds), NSHeight(bounds));
}



@end
 
