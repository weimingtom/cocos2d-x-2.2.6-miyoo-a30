/*
 * CCEGLView.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef CCEGLVIEW_H_
#define CCEGLVIEW_H_

#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"

#ifdef USE_NO_GLFW
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#else
#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>
#endif

bool initExtensions();

NS_CC_BEGIN

class CCEGLView : public CCEGLViewProtocol{
public:
	CCEGLView();
	virtual ~CCEGLView();

#if USE_NO_GLFW
#else	
	friend void keyEventHandle(GLFWwindow*,int,int,int,int);
	friend void mouseButtonEventHandle(GLFWwindow*,int,int,int);
	friend void mousePosEventHandle(GLFWwindow*,double,double);
	friend void charEventHandle(GLFWwindow*,unsigned int);
#endif

	/**
	 * iPixelWidth, height: the window's size
	 * iWidth ,height: the point size, which may scale.
	 * iDepth is not the buffer depth of opengl, it indicate how may bits for a pixel
	 */
	virtual void setFrameSize(float width, float height);
	virtual void setViewPortInPoints(float x , float y , float w , float h);
	virtual void setScissorInPoints(float x , float y , float w , float h);

	/*
	 * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
	 */
	void setFrameZoomFactor(float fZoomFactor);
	float getFrameZoomFactor();
	virtual bool isOpenGLReady();
	virtual void end();
	virtual void swapBuffers();
	virtual void setIMEKeyboardState(bool bOpen);

	/**
	 @brief	get the shared main open gl window
	 */
	static CCEGLView* sharedOpenGLView();
private:
	bool initGL();
	void destroyGL();
private:
	//store current mouse point for moving, valid if and only if the mouse pressed
	CCPoint m_mousePoint;
	bool bIsInit;
	float m_fFrameZoomFactor;
#if USE_NO_GLFW
#else		
	GLFWwindow* m_window;
#endif
};

NS_CC_END

#endif /* CCEGLVIEW_H_ */
