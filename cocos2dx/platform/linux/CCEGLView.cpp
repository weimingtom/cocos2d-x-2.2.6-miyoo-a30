/*
 * CCEGLViewlinux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#include <stdlib.h>
#include <unistd.h>
#include "CCEGLView.h"
#include "CCGL.h"
//#include "GLFW/glfw3.h"
#include "cocoa/CCSet.h"
#include "CCDirector.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"


bool initExtensions() {
	return true;
}

NS_CC_BEGIN

CCEGLView::CCEGLView()
: bIsInit(false)
, m_fFrameZoomFactor(1.0f)
{
    initExtensions();
}

CCEGLView::~CCEGLView()
{
}

#if USE_NO_GLFW
//skip
#else
void keyEventHandle(GLFWwindow* window, int iKeyID/*key*/, int scancode, int iKeyState/*action*/, int mods) { //int iKeyID,int iKeyState
	if (iKeyState ==GLFW_RELEASE) {
		return;
	}
/*
    if (action != GLFW_PRESS)
        return;
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_KP_ADD:
        case GLFW_KEY_Q:
        case GLFW_KEY_KP_SUBTRACT:
        case GLFW_KEY_W:
    }
*/
	if (iKeyID == GLFW_KEY_DELETE) {
		CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	} else if (iKeyID == GLFW_KEY_ENTER) {
		CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
	} else if (iKeyID == GLFW_KEY_TAB) {

	}
}

void charEventHandle(GLFWwindow* window, unsigned int codepoint) { //int iCharID,int iCharState
	// ascii char
	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char*)(&codepoint), 1);
}

void mouseButtonEventHandle(GLFWwindow* window, int iMouseID/*button*/, int iMouseState/*action*/, int mods) { //int iMouseID,int iMouseState
	if (iMouseID == GLFW_MOUSE_BUTTON_LEFT) {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
		//get current mouse pos
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		CCPoint oPoint((float)x,(float)y);
		/*
		if (!CCRect::CCRectContainsPoint(s_pMainWindow->m_rcViewPort,oPoint))
		{
			CCLOG("not in the viewport");
			return;
		}
		*/
         oPoint.x /= pEGLView->m_fFrameZoomFactor;
         oPoint.y /= pEGLView->m_fFrameZoomFactor;
		int id = 0;
		if (iMouseState == GLFW_PRESS) {
			pEGLView->handleTouchesBegin(1, &id, &oPoint.x, &oPoint.y);

		} else if (iMouseState == GLFW_RELEASE) {
			pEGLView->handleTouchesEnd(1, &id, &oPoint.x, &oPoint.y);
		}
	}
}

void mousePosEventHandle(GLFWwindow* window, double iPosX/*x*/, double iPosY/*y*/) { //int iPosX,int iPosY
	int iButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	//to test move
	if (iButtonState == GLFW_PRESS) {
            CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
            int id = 0;
            float x = (float)iPosX;
            float y = (float)iPosY;
            x /= pEGLView->m_fFrameZoomFactor;
            y /= pEGLView->m_fFrameZoomFactor;
            pEGLView->handleTouchesMove(1, &id, &x, &y);
	}
}

void closeEventHandle(GLFWwindow* window) {
	CCDirector::sharedDirector()->end();

CCLOG("closeEventHandle");
glfwSetWindowShouldClose(window, GL_TRUE);
}
#endif

#if USE_NO_GLFW
EGLDisplay display = EGL_NO_DISPLAY;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;


GLfloat vVertices[] = {
 0.0f,  0.5f, 0.0f,
-0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f
};
    GLuint pObject = 0;
#endif
	
void CCEGLView::setFrameSize(float width, float height)
{	
	bool eResult = false;
	//create the window by glfw.

	//check
	CCAssert(width!=0&&height!=0, "invalid window's size equal 0");

#if USE_NO_GLFW
	EGLint egl_major = 0;
    EGLint egl_minor = 0;
    EGLint num_configs = 0;
    EGLConfig configs = {0};
    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE,   8,//5,  
        EGL_GREEN_SIZE, 8,//6,
        EGL_BLUE_SIZE,  8,//5,  
        EGL_ALPHA_SIZE, 8,//0,
        EGL_NONE
    };
    EGLint window_attributes[] = { 
        EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
        EGL_NONE
    };
    EGLint const context_attributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE,
    };
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, &egl_major, &egl_minor);
    eglChooseConfig(display, config_attribs, &configs, 1, &num_configs);
    surface = eglCreateWindowSurface(display, configs, 0, window_attributes);
    context = eglCreateContext(display, configs, EGL_NO_CONTEXT, context_attributes);
    eglMakeCurrent(display, surface, surface, context);
	
//======================	
//FIXME:don't forget bIsInit and CCEGLViewProtocol::setFrameSize, otherwise screen will be black
//======================
		CCEGLViewProtocol::setFrameSize(width, height);		

		/* Updates its title */
		//glfwSetWindowTitle(m_window, "Cocos2dx-Linux");

		//set the init flag
		bIsInit = true;

		//register the glfw key event
		//glfwSetKeyCallback(m_window, keyEventHandle);
		//register the glfw char event
		//glfwSetCharCallback(m_window, charEventHandle);
		//register the glfw mouse event
		//glfwSetMouseButtonCallback(m_window, mouseButtonEventHandle);
		//register the glfw mouse pos event
		//glfwSetCursorPosCallback(m_window, mousePosEventHandle);

		//glfwSetWindowCloseCallback(m_window, closeEventHandle);

		//Inits extensions
		//eResult = initExtensions();

		//if (!eResult) {
		//	CCAssert(0, "fail to init the extensions of opengl");
		//}
		//initGL();	
	
		//Inits extensions
		eResult = initExtensions();

		if (!eResult) {
			CCAssert(0, "fail to init the extensions of opengl");
		}
		initGL();

const char *vShaderSrc =
    "attribute vec4 vPosition;  \n"
    "void main()                \n"
    "{                          \n"
    "  gl_Position = vPosition; \n"
    "}                          \n";
 
const char *fShaderSrc =
    "precision mediump float;                       \n"
    "void main()                                    \n"
    "{                                              \n"
    "   gl_FragColor = vec4(0.7, 0.85, 0.97, 1.0);    \n"
    "}                                              \n"; 

    GLuint vShader = 0;
    GLuint fShader = 0;
    GLint compiled = 0;
    
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSrc, NULL);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &compiled);
 
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSrc, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &compiled);
  
    pObject = glCreateProgram();
    glAttachShader(pObject, vShader);
    glAttachShader(pObject, fShader);
    glLinkProgram(pObject);
    glUseProgram(pObject);

#if 0
#define LCD_W   USE_APP_HEIGHT
#define LCD_H   USE_APP_WIDTH
//    glViewport(0, 0, LCD_W, LCD_H);
#else
#define LCD_W   USE_APP_WIDTH
#define LCD_H   USE_APP_HEIGHT
//    glViewport(0, 0, LCD_W, LCD_H);
#endif    
    
    
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(display, surface);
CCLog("setFrameSize %f, %f", width, height);

//while(1) {
#if 0
    glViewport(0, 0, LCD_W, LCD_H);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    eglSwapBuffers(display, surface);
    sleep(3);
#endif    
//}









	
#else	
	
	//Inits GLFW
	eResult = glfwInit() != GL_FALSE;

	if (!eResult) {
		CCAssert(0, "fail to init the glfw");
	}

	/* Updates window hint */
	
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int iDepth = 16; // set default value
	/* Depending on video depth */
	switch(iDepth)
	{
		/* 16-bit */
		case 16:
		{		
			/* Updates video mode */
glfwWindowHint(GLFW_RED_BITS, 5);
glfwWindowHint(GLFW_GREEN_BITS, 6);
glfwWindowHint(GLFW_BLUE_BITS, 5);
glfwWindowHint(GLFW_ALPHA_BITS, 0);		
			eResult = ((m_window = glfwCreateWindow(width, height, "", NULL, NULL)) != NULL) ? true : false;

			break;
		}

		/* 24-bit */
		case 24:
		{
			/* Updates video mode */
glfwWindowHint(GLFW_RED_BITS, 8);
glfwWindowHint(GLFW_GREEN_BITS, 8);
glfwWindowHint(GLFW_BLUE_BITS, 8);
glfwWindowHint(GLFW_ALPHA_BITS, 0);				
			eResult = ((m_window = glfwCreateWindow(width, height, "", NULL, NULL)) != NULL) ? true : false;

			break;
		}

		/* 32-bit */
		default:
		case 32:
		{
			/* Updates video mode */
glfwWindowHint(GLFW_RED_BITS, 8);
glfwWindowHint(GLFW_GREEN_BITS, 8);
glfwWindowHint(GLFW_BLUE_BITS, 8);
glfwWindowHint(GLFW_ALPHA_BITS, 8);				
			eResult = ((m_window = glfwCreateWindow(width, height, "", NULL, NULL)) != NULL) ? true :false;
			break;
		}
	}

	/* Success? */
	if(eResult)
	{
glfwMakeContextCurrent(m_window);

//printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
//printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );
	
		/* Updates actual size */
	  //		glfwGetWindowSize(&width, &height);

		CCEGLViewProtocol::setFrameSize(width, height);		

		/* Updates its title */
		glfwSetWindowTitle(m_window, "Cocos2dx-Linux");

		//set the init flag
		bIsInit = true;

		//register the glfw key event
		glfwSetKeyCallback(m_window, keyEventHandle);
		//register the glfw char event
		glfwSetCharCallback(m_window, charEventHandle);
		//register the glfw mouse event
		glfwSetMouseButtonCallback(m_window, mouseButtonEventHandle);
		//register the glfw mouse pos event
		glfwSetCursorPosCallback(m_window, mousePosEventHandle);

		glfwSetWindowCloseCallback(m_window, closeEventHandle);

		//Inits extensions
		eResult = initExtensions();

		if (!eResult) {
			CCAssert(0, "fail to init the extensions of opengl");
		}
		initGL();
		
    		
	}
#endif	
}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
#if USE_NO_GLFW	
//skip
#else
    glfwSetWindowSize(m_window, m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
#endif	
    CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}

float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
#if !USE_ROTATE90
    glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor+ m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));   
#else
    glViewport(
    	(GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor)
        ); 
#endif
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
#if !USE_ROTATE90
    glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
              (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
              (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
              (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
#else
    glScissor(
    	(GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor)
   	);
#endif
}


bool CCEGLView::isOpenGLReady()
{
	return bIsInit;
}

void CCEGLView::end()
{
	/* Exits from GLFW */
#if USE_NO_GLFW
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
#else		
	glfwTerminate();
#endif	
	delete this;
	exit(0);
}

long ntime = 0;
void CCEGLView::swapBuffers() {

	if (bIsInit) { //FIXME: NOTICE, if bIsInit==false, it shows nothing
//CCLog("swapBuffers %d", ntime++);
		/* Swap buffers */
#if USE_NO_GLFW	
if (false) {
    //glUseProgram(pObject);
    glViewport(0, 0, LCD_W, LCD_H);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}    
		eglSwapBuffers(display, surface);
#else	
		glfwSwapBuffers(m_window);
glfwPollEvents();
#endif
	}
}

void CCEGLView::setIMEKeyboardState(bool bOpen) {

}

bool CCEGLView::initGL()
{
#ifndef GL_VERTEX_PROGRAM_POINT_SIZE
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642 
#endif

    // Enable point size by default on linux.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void CCEGLView::destroyGL()
{
#if USE_NO_GLFW
    //eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    //eglDestroyContext(display, context);
    //eglDestroySurface(display, surface);
    //eglTerminate(display);
#else		
	//glfwTerminate();
#endif
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new CCEGLView();
    }
    return s_pEglView;
}

NS_CC_END
