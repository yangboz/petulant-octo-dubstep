#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include <glfw3\include\win32\glfw3native.h>


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::createWithRect("HP_ID_Print_App", CCRectMake(0, 0, 800, 600), 1.0f);
		//glview = GLView::createWithRect("HP Certificates Print",CCRectMake(0,0,800,600),1.0f);
        director->setOpenGLView(glview);
		//Window customize
		//glview->setFrameSize(800, 600);
		glview->setDesignResolutionSize(800, 600, ResolutionPolicy::EXACT_FIT);
		//
	}
	//Remove windows border.
	GLFWwindow* glWindow = glview->getWindow();
	HWND hWnd = glfwGetWin32Window(glWindow);
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
