#0: pc
#1: miyoo a30 and rg28xx
#2: trimui smart pro
#3: trimui brick
MIYOO := 1

ifeq ($(MIYOO),3)
CC = /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-gcc
CPP := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-g++
AR := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-ar cru
RANLIB := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-ranlib 
else ifeq ($(MIYOO),2)
CC = /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-gcc
CPP := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-g++
AR := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-ar cru
RANLIB := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-ranlib 
else ifeq ($(MIYOO),1)
CC = /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CPP := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
AR := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ar cru
RANLIB := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ranlib 
else
CC  := gcc
CPP := g++
AR  := ar cru
RANLIB := ranlib
endif
RM := rm -rf

CPPFLAGS := 
CPPFLAGS += -I.   
#CPPFLAGS += -g -O2
CPPFLAGS += -g3 -O0
#CPPFLAGS += -DWIN32
#CPPFLAGS += -D_DEBUG
#CPPFLAGS += -D_WINDOWS
#CPPFLAGS += -D_USRDLL
#CPPFLAGS += -DCOCOS2DXWIN32_EXPORTS
#CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#CPPFLAGS += -DCOCOS2D_DEBUG=1
#CPPFLAGS += -D_CRT_SECURE_NO_WARNINGS
#CPPFLAGS += -D_SCL_SECURE_NO_WARNINGS
#CPPFLAGS += -DPTW32_STATIC_LIB
CPPFLAGS += -DLINUX 
CPPFLAGS += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 
CPPFLAGS += -D_DEBUG 
CPPFLAGS += -DCOCOS2D_DEBUG=1




ifeq ($(MIYOO),3)
#trimui brick
CPPFLAGS += -DUSE_APP_WIDTH=1024
CPPFLAGS += -DUSE_APP_HEIGHT=768
CPPFLAGS += -DUSE_NO_GLFW=1
CPPFLAGS += -DUSE_ROTATE90=0
else ifeq ($(MIYOO),2)
#trimui smart pro
CPPFLAGS += -DUSE_APP_WIDTH=1280
CPPFLAGS += -DUSE_APP_HEIGHT=720
CPPFLAGS += -DUSE_NO_GLFW=1
CPPFLAGS += -DUSE_ROTATE90=0
else ifeq ($(MIYOO),1)
#miyoo a30 and rg28xx
CPPFLAGS += -DUSE_APP_WIDTH=640
CPPFLAGS += -DUSE_APP_HEIGHT=480
CPPFLAGS += -DUSE_NO_GLFW=1
CPPFLAGS += -DUSE_ROTATE90=1
else
#pc
CPPFLAGS += -DUSE_APP_WIDTH=640
CPPFLAGS += -DUSE_APP_HEIGHT=480
CPPFLAGS += -DUSE_NO_GLFW=0 -DUSE_SHADER_PRECISION=1
#if PC use OpenGLES to replace OpenGL, need USE_SHADER_PRECISION
#cocos2d-x debug info [cocos2d: 0:1(1): error: No precision specified in this scope for type `mat4'
CPPFLAGS += -DUSE_ROTATE90=0
endif




#CPPFLAGS += -D_WIN32_WINNT=0x0500
#CPPFLAGS += -DGLEW_STATIC

CPPFLAGS += -Icocos2dx
CPPFLAGS += -Icocos2dx/include
CPPFLAGS += -Icocos2dx/kazmath/include
CPPFLAGS += -Icocos2dx/platform/linux
ifeq ($(MIYOO),3)
CPPFLAGS += -I/home/wmt/work_trimui/usr/include
CPPFLAGS += -I/home/wmt/work_trimui/usr/include/webp
CPPFLAGS += -I/home/wmt/work_trimui/usr/include/freetype2
else ifeq ($(MIYOO),2)
CPPFLAGS += -I/home/wmt/work_trimui/usr/include
CPPFLAGS += -I/home/wmt/work_trimui/usr/include/webp
CPPFLAGS += -I/home/wmt/work_trimui/usr/include/freetype2
else ifeq ($(MIYOO),1)
CPPFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include
CPPFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include/webp
CPPFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include/freetype2
else
#xubuntu 16
#sudo apt install libglfw3-dev libpng-dev zlib1g-dev libjpeg-dev libfreetype-dev libbz2-dev
CPPFLAGS += -I/usr/include
CPPFLAGS += -I/usr/include/webp
CPPFLAGS += -I/usr/include/freetype2
endif











LDFLAGS := 
LDFLAGS += -lfreetype -lbz2 #CCImage.o
LDFLAGS += -lz #ZipUtils.o
LDFLAGS += -lpng #CCImage.o
LDFLAGS += -lpthread #CCTextureCache.o
LDFLAGS += -ljpeg #CCImage.o
LDFLAGS += -lGLESv2 -lEGL


ifeq ($(MIYOO),3)
#trimui brick replace glfw3 with EGL
LDFLAGS += -lIMGegl -lsrv_um -lusc -lglslcompiler -L/home/wmt/work_trimui/usr/lib
else ifeq ($(MIYOO),2)
#trimui smart pro replace glfw3 with EGL
LDFLAGS += -lIMGegl -lsrv_um -lusc -lglslcompiler -L/home/wmt/work_trimui/usr/lib
else ifeq ($(MIYOO),1)
#miyoo a30 replace glfw3 with EGL
LDFLAGS += -L/home/wmt/work_a30/staging_dir/target/usr/lib
else
#xubuntu 16, need glfw3 and EGL
#sudo apt install libglfw3-dev libpng-dev zlib1g-dev libjpeg-dev libfreetype-dev libbz2-dev
LDFLAGS += -lglfw #cocos2dx/platform/linux/CCEGLView.cpp
endif


#LDFLAGS += -lwebp #CCImageCommonWebp.o
#LDFLAGS += -lfontconfig #cocos2dx/platform/linux/CCImage.cpp
#LDFLAGS += -ltiff #CCImage.o, cocos2d::CCImage::_initWithTiffData, cocos2dx/platform/CCImageCommon_cpp.h

#LDFLAGS += -lGL #CCDirector.o
#LDFLAGS += -lGLEW #cocos2dx/misc_nodes/CCRenderTexture.cpp

###LDFLAGS += -lXrandr 
###LDFLAGS += -lrt -lX11
###LDFLAGS += -lstdc++

OBJS := 

#actions
OBJS += cocos2dx/actions/CCAction.o
OBJS += cocos2dx/actions/CCActionCamera.o
OBJS += cocos2dx/actions/CCActionCatmullRom.o
OBJS += cocos2dx/actions/CCActionEase.o
OBJS += cocos2dx/actions/CCActionGrid.o
OBJS += cocos2dx/actions/CCActionGrid3D.o
OBJS += cocos2dx/actions/CCActionInstant.o
OBJS += cocos2dx/actions/CCActionInterval.o
OBJS += cocos2dx/actions/CCActionManager.o
OBJS += cocos2dx/actions/CCActionPageTurn3D.o
OBJS += cocos2dx/actions/CCActionProgressTimer.o
OBJS += cocos2dx/actions/CCActionTiledGrid.o
OBJS += cocos2dx/actions/CCActionTween.o

#base_nodes
OBJS += cocos2dx/base_nodes/CCAtlasNode.o
OBJS += cocos2dx/base_nodes/CCNode.o

#cocoa
OBJS += cocos2dx/cocoa/CCAffineTransform.o
OBJS += cocos2dx/cocoa/CCArray.o
OBJS += cocos2dx/cocoa/CCAutoreleasePool.o
OBJS += cocos2dx/cocoa/CCDataVisitor.o
OBJS += cocos2dx/cocoa/CCDictionary.o
OBJS += cocos2dx/cocoa/CCGeometry.o
OBJS += cocos2dx/cocoa/CCNS.o
OBJS += cocos2dx/cocoa/CCObject.o
OBJS += cocos2dx/cocoa/CCSet.o
OBJS += cocos2dx/cocoa/CCString.o
OBJS += cocos2dx/cocoa/CCZone.o

#draw_nodes
OBJS += cocos2dx/draw_nodes/CCDrawingPrimitives.o
OBJS += cocos2dx/draw_nodes/CCDrawNode.o

#effects
OBJS += cocos2dx/effects/CCGrabber.o
OBJS += cocos2dx/effects/CCGrid.o

#kazmath
OBJS += cocos2dx/kazmath/src/GL/mat4stack.o
OBJS += cocos2dx/kazmath/src/GL/matrix.o
OBJS += cocos2dx/kazmath/src/aabb.o
OBJS += cocos2dx/kazmath/src/mat3.o
OBJS += cocos2dx/kazmath/src/mat4.o
OBJS += cocos2dx/kazmath/src/neon_matrix_impl.o
OBJS += cocos2dx/kazmath/src/plane.o
OBJS += cocos2dx/kazmath/src/quaternion.o
OBJS += cocos2dx/kazmath/src/ray2.o
OBJS += cocos2dx/kazmath/src/utility.o
OBJS += cocos2dx/kazmath/src/vec2.o
OBJS += cocos2dx/kazmath/src/vec3.o
OBJS += cocos2dx/kazmath/src/vec4.o

#keypad_dispatcher
OBJS += cocos2dx/keypad_dispatcher/CCKeypadDelegate.o
OBJS += cocos2dx/keypad_dispatcher/CCKeypadDispatcher.o

#label_nodes
OBJS += cocos2dx/label_nodes/CCLabelAtlas.o
OBJS += cocos2dx/label_nodes/CCLabelBMFont.o
OBJS += cocos2dx/label_nodes/CCLabelTTF.o

#layers_scenes_transitions_nodes
OBJS += cocos2dx/layers_scenes_transitions_nodes/CCLayer.o
OBJS += cocos2dx/layers_scenes_transitions_nodes/CCScene.o
OBJS += cocos2dx/layers_scenes_transitions_nodes/CCTransition.o
OBJS += cocos2dx/layers_scenes_transitions_nodes/CCTransitionPageTurn.o
OBJS += cocos2dx/layers_scenes_transitions_nodes/CCTransitionProgress.o

#menu_nodes
OBJS += cocos2dx/menu_nodes/CCMenu.o
OBJS += cocos2dx/menu_nodes/CCMenuItem.o

#misc_nodes
OBJS += cocos2dx/misc_nodes/CCClippingNode.o
OBJS += cocos2dx/misc_nodes/CCMotionStreak.o
OBJS += cocos2dx/misc_nodes/CCProgressTimer.o
OBJS += cocos2dx/misc_nodes/CCRenderTexture.o

#particle_nodes
OBJS += cocos2dx/particle_nodes/CCParticleBatchNode.o
OBJS += cocos2dx/particle_nodes/CCParticleExamples.o
OBJS += cocos2dx/particle_nodes/CCParticleSystem.o
OBJS += cocos2dx/particle_nodes/CCParticleSystemQuad.o

#platform
#OBJS += cocos2dx/platform/win32/CCAccelerometer.o
OBJS += cocos2dx/platform/linux/CCApplication.o
OBJS += cocos2dx/platform/linux/CCCommon.o
OBJS += cocos2dx/platform/linux/CCDevice.o
OBJS += cocos2dx/platform/linux/CCEGLView.o
OBJS += cocos2dx/platform/linux/CCFileUtilsLinux.o
OBJS += cocos2dx/platform/linux/CCImage.o
OBJS += cocos2dx/platform/linux/CCStdC.o
OBJS += cocos2dx/platform/CCEGLViewProtocol.o
OBJS += cocos2dx/platform/CCFileUtils.o
OBJS += cocos2dx/platform/CCImageCommonWebp.o
OBJS += cocos2dx/platform/CCSAXParser.o
OBJS += cocos2dx/platform/CCThread.o
OBJS += cocos2dx/platform/platform.o

#script_support
OBJS += cocos2dx/script_support/CCScriptSupport.o

#shaders
OBJS += cocos2dx/shaders/CCGLProgram.o
OBJS += cocos2dx/shaders/ccGLStateCache.o
OBJS += cocos2dx/shaders/CCShaderCache.o
OBJS += cocos2dx/shaders/ccShaders.o

#sprite_nodes
OBJS += cocos2dx/sprite_nodes/CCAnimation.o
OBJS += cocos2dx/sprite_nodes/CCAnimationCache.o
OBJS += cocos2dx/sprite_nodes/CCSprite.o
OBJS += cocos2dx/sprite_nodes/CCSpriteBatchNode.o
OBJS += cocos2dx/sprite_nodes/CCSpriteFrame.o
OBJS += cocos2dx/sprite_nodes/CCSpriteFrameCache.o

#text_input_node
OBJS += cocos2dx/text_input_node/CCIMEDispatcher.o
OBJS += cocos2dx/text_input_node/CCTextFieldTTF.o

#textures
OBJS += cocos2dx/textures/CCTexture2D.o
OBJS += cocos2dx/textures/CCTextureAtlas.o
OBJS += cocos2dx/textures/CCTextureCache.o
OBJS += cocos2dx/textures/CCTextureETC.o
OBJS += cocos2dx/textures/CCTexturePVR.o

#tilemap_parallax_nodes
OBJS += cocos2dx/tilemap_parallax_nodes/CCParallaxNode.o
OBJS += cocos2dx/tilemap_parallax_nodes/CCTileMapAtlas.o
OBJS += cocos2dx/tilemap_parallax_nodes/CCTMXLayer.o
OBJS += cocos2dx/tilemap_parallax_nodes/CCTMXObjectGroup.o
OBJS += cocos2dx/tilemap_parallax_nodes/CCTMXTiledMap.o
OBJS += cocos2dx/tilemap_parallax_nodes/CCTMXXMLParser.o

#touch_dispatcher
OBJS += cocos2dx/touch_dispatcher/CCTouch.o
OBJS += cocos2dx/touch_dispatcher/CCTouchDispatcher.o
OBJS += cocos2dx/touch_dispatcher/CCTouchHandler.o

#(top)
OBJS += cocos2dx/CCCamera.o
OBJS += cocos2dx/CCConfiguration.o
OBJS += cocos2dx/CCDirector.o
OBJS += cocos2dx/ccFPSImages.o
OBJS += cocos2dx/CCScheduler.o
OBJS += cocos2dx/cocos2d.o
#OBJS += cocos2dx/proj.win32/pch.o

#support
OBJS += cocos2dx/support/component/CCComponent.o
OBJS += cocos2dx/support/component/CCComponentContainer.o
OBJS += cocos2dx/support/data_support/ccCArray.o
OBJS += cocos2dx/support/image_support/TGAlib.o
OBJS += cocos2dx/support/tinyxml2/tinyxml2.o
OBJS += cocos2dx/support/user_default/CCUserDefault.o
OBJS += cocos2dx/support/zip_support/ioapi.o
OBJS += cocos2dx/support/zip_support/unzip.o
OBJS += cocos2dx/support/zip_support/ZipUtils.o
OBJS += cocos2dx/support/base64.o
OBJS += cocos2dx/support/CCNotificationCenter.o
OBJS += cocos2dx/support/CCPointExtension.o
OBJS += cocos2dx/support/CCProfiling.o
OBJS += cocos2dx/support/ccUTF8.o
OBJS += cocos2dx/support/ccUtils.o
OBJS += cocos2dx/support/CCVertex.o
OBJS += cocos2dx/support/TransformUtils.o

HELLOCPP_OBJS :=
HELLOCPP_OBJS += samples/Cpp/HelloCpp/Classes/AppDelegate.o
HELLOCPP_OBJS += samples/Cpp/HelloCpp/Classes/HelloWorldScene.o

all : samples/Cpp/HelloCpp/HelloCpp

cocos2dx.a : $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

samples/Cpp/HelloCpp/HelloCpp: cocos2dx.a $(HELLOCPP_OBJS)
	$(CPP) samples/Cpp/HelloCpp/proj.linux/main.cpp $(HELLOCPP_OBJS) cocos2dx.a -o $@ -Isamples/Cpp/HelloCpp/Classes $(CPPFLAGS) $(LDFLAGS)

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

%.o : %.c
	$(CC) $(CPPFLAGS) -o $@ -c $<
	
test:
	./samples/Cpp/HelloCpp/HelloCpp

clean :
	$(RM) $(OBJS) $(HELLOCPP_OBJS) cocos2dx.a samples/Cpp/HelloCpp/HelloCpp
