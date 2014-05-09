#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define COCOS2D_DEBUG 1

//#include "cocos-ext.h" 
#include "CocosGUI.h"
#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	//EventHandlers
	void onOpenButtonTouch(Object *pSender, ui::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//ChineseCharacters Wrapper
	std::string WStrToUTF8(const std::wstring &str);
	void WStrToUTF8Convert(std::string& dest, const std::wstring& src);

	//OpenFilePickerTask
	void onOpenFilePicker();

private:
	ui::Widget *uiLayout;
};

#endif // __HELLOWORLD_SCENE_H__
