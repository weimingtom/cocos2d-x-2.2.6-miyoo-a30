cocos2dx/platform/linux/CCFileUtilsLinux.cpp

m_strDefaultResRootPath += "/../../../Resources/";

->

#if 0
    m_strDefaultResRootPath += "/../../../Resources/";
#else
    m_strDefaultResRootPath += "/";
#endif


cocos2dx/platform/linux/CCEGLView.cpp

USE_NO_GLFW

gedit cocos2dx/platform/linux/CCEGLView.cpp

--
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
 
 
--

#if USE_NO_GLFW
//skip
#else
#include <X11/Xlib.h>
#endif
#include <stdio.h>

NS_CC_BEGIN

int CCDevice::getDPI()
{
	static int dpi = -1;
	if (dpi == -1)
	{
#if USE_NO_GLFW
	    dpi = 160;
#else

--
cocos2d-x-2.2.6\cocos2dx\misc_nodes\CCClippingNode.cpp

|| CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
->
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS)

    // enable alpha test only if the alpha threshold < 1,
    // indeed if alpha threshold == 1, every pixel will be drawn anyways
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    GLboolean currentAlphaTestEnabled = GL_FALSE;
    GLenum currentAlphaTestFunc = GL_ALWAYS;
    GLclampf currentAlphaTestRef = 1;
	
	
--


