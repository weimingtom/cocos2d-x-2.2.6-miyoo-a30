#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
printf("enter linux main\n");
    // create the application instance
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
#if defined(USE_APP_WIDTH) && defined(USE_APP_HEIGHT)
    eglView->setFrameSize(USE_APP_WIDTH, USE_APP_HEIGHT);
#else    
    eglView->setFrameSize(640, 480);
#endif

    return CCApplication::sharedApplication()->run();
}
