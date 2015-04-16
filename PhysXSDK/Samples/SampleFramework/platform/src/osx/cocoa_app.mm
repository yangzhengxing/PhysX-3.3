
#include "cocoa_app.h"
#include "cocoa_window.h"

@implementation CocoaApp
  
- (id)init
{
	_running = 1;
	return [super init];
}


  
- (void)runOnce: (BOOL) blockTillEvent
{
	if([self isRunning])
	{
		NSAutoreleasePool *pool    = [[NSAutoreleasePool alloc] init];
		NSRunLoop         *runLoop = [[NSRunLoop currentRunLoop] retain];
		
		NSDate  *limitDate = [runLoop limitDateForMode: NSDefaultRunLoopMode];
		NSEvent *event = [self  nextEventMatchingMask: NSAnyEventMask
                              untilDate: blockTillEvent ? limitDate : nil
                              inMode: NSDefaultRunLoopMode
                              dequeue: YES];
      	
		if(event)
		{
			[self sendEvent: event];
		}
		
		[runLoop release];
		[pool    drain];
	}
}

@end
