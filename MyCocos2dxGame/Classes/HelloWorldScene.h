#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define COCOS2D_DEBUG 1

//#include "cocos-ext.h" 
#include "CocosGUI.h"
#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"

//
#include "FileOperation.h"
#include "HW_DataModel.h"
#include "OpenCvOpeartion.h"

#include "PopupLayer\PopupLayer.h"

#include "HW_UserDataModel.h"

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
	void onResetButtonTouch(Object *pSender, ui::TouchEventType type);
	void onVerifyButtonTouch(Object *pSender, ui::TouchEventType type);
	void onTypesetButtonTouch(Object *pSender, ui::TouchEventType type);
	void onPrintButtonTouch(Object *pSender, ui::TouchEventType type);
	void onCertListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onPrintListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onSliderValueChanged(Object *pSender, ui::SliderEventType type);
	void onWindowCloseButtonTouch(Object *pSender, ui::TouchEventType type);
	void onWindowMinButtonTouch(Object *pSender, ui::TouchEventType type);
	void onCertListViewItemButtonTouch(Object *pSender, ui::TouchEventType type);
	void onZoomInButtonTouch(Object *pSender, ui::TouchEventType type);
	void onZoomOutButtonTouch(Object *pSender, ui::TouchEventType type);
	void onRotateButtonTouch(Object *pSender, ui::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//OpenFilePickerTask
	void onOpenFilePicker();
	//Popup layer testing
	void popupLayerTesting();
	//Assemble list view of photo size
	void assembleListViewOfPhotoSize();

private:
	ui::Widget *uiLayout;//MainLayout
	//Window buttons
	ui::Button *btn_window_min;
	ui::Button *btn_window_close;
	ui::Button *btn_zoom_in;
	ui::Button *btn_zoom_out;
	ui::Button *btn_rotate;
	ui::Button *btn_open;
	ui::Button *btn_reset;
	ui::Button *btn_verify;
	ui::Button *btn_typeset;
	ui::Button *btn_print;
	//PageViews
	ui::PageView *pageView_main;
	//Editor view related
	ui::ScrollView *scrollView_editor;
	ui::ImageView *imageView_cert_origin;
	//ListViews
	ui::ListView *listView_index_size;
	ui::ListView *listView_index_validate;
	ui::ListView *listView_index_print;
	//Sliders
	ui::Slider *slider_photo_size;
	//Site variables
	int slider_changed_value;
	float cur_roate_value;

	//Popup related
	void popupButtonCallback(cocos2d::CCNode *pNode);
};

#endif // __HELLOWORLD_SCENE_H__
