# cocos2d-x-2.2.6-miyoo-a30
[WIP] Cocos2d-x-2.2.6 MIYOO A30, TRIMUI SMART PRO, TRIMUI BRICK port, now only support video output with GLES2, no input and audio

## About OpenGL ES 2.0 initialization code  
* Inspired by and thanks to Steward.    
* see also https://steward-fu.github.io/website/handheld/miyoo_a30_cpp_es_triangle.htm   
```
參考資訊：
https://www.khronos.org/assets/uploads/books/openglr_es_20_programming_guide_sample.pdf
```

## Original Cocos2d-x Repo    
* https://github.com/cocos2d/cocos2d-x/tree/cocos2d-x-2.2.6  

## About GCC toolchain and development environment  
* see also https://github.com/weimingtom/onscripter-libretro_fork  
```
(for miyoo a30)
https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024
see https://github.com/weimingtom/miyoo_a30_playground
see https://github.com/weimingtom/onscripter-jh-miyoo-a30

(for Trimui Smart Pro and Trimui Brick, aarch64)
https://github.com/trimui/toolchain_sdk_smartpro/releases/tag/20231018

(for PC)
xubuntu 20.04 64bit  
```


## About screen rotation 90 degrees problem  
* see also https://github.com/weimingtom/cocos2dx226_vc6  
```
see cocos2dx/CCDirector.cpp, void CCDirector::setProjection(ccDirectorProjection kProjection), see

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
            //if needed, we need to add a rotation for Landscape orientations on Windows Phone 8 since it is always in Portrait Mode
            kmGLMultMatrix(CCEGLView::sharedOpenGLView()->getOrientationMatrix());
#endif
```

## Key and important codes  
* CCEGLView.cpp
* CCDirector.cpp
* CCNode.cpp
* CCSprite.cpp
* HelloWorldScene.cpp
* main.cpp
