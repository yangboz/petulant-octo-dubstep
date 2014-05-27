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

//PageView name constants
#define PAGE_VIEW_INTRO 0
#define PAGE_VIEW_UPLOAD 1
#define PAGE_VIEW_EDITOR 2
#define PAGE_VIEW_VERIFY 3
#define PAGE_VIEW_TYPESET 4


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//Buttons EventHandlers
	void onUploadButtonTouch(Object *pSender, ui::TouchEventType type);
	void onResetButtonTouch(Object *pSender, ui::TouchEventType type);
	void onVerifyButtonTouch(Object *pSender, ui::TouchEventType type);
	void onTypesetButtonTouch(Object *pSender, ui::TouchEventType type);
	void onPrintButtonTouch(Object *pSender, ui::TouchEventType type);
	//Navigation buttons related
	void onEditorNaviButtonTouch(Object *pSender, ui::TouchEventType type);
	void onUploadNaviButtonTouch(Object *pSender, ui::TouchEventType type);
	void onVerifyNaviButtonTouch(Object *pSender, ui::TouchEventType type);
	void onTypesetNaviButtonTouch(Object *pSender, ui::TouchEventType type);
	//Window button related
	void onWindowCloseButtonTouch(Object *pSender, ui::TouchEventType type);
	void onWindowMinButtonTouch(Object *pSender, ui::TouchEventType type);
	//Editor view related
	///Slider related
	void onScaleSliderValueChanged(Object *pSender, ui::SliderEventType type);
	void onMoveSliderValueChanged(Object *pSender, ui::SliderEventType type);
	///
	void onZoomInButtonTouch(Object *pSender, ui::TouchEventType type);
	void onZoomOutButtonTouch(Object *pSender, ui::TouchEventType type);
	void onRotateButtonTouch(Object *pSender, ui::TouchEventType type);
	///ListView related
	void onCertListViewItemButtonTouch(Object *pSender, ui::TouchEventType type);
	void onCertListViewItemButtonSelected(Object *pSender, ui::TouchEventType type);
	void onCertListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onUploadListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onEditorListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onPrintListViewItemSelected(Object *pSender, ui::ListViewEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//OpenFilePickerTask
	void onOpenFilePicker();
	//Popup layer related
	void centerPopupLayer(const char *bgFilePath);
	void removePopupLayer();
	//Set up list views with size values
	void setupListViews();

private:
	ui::Widget *uiLayout;//MainLayout
	//Window buttons
	ui::Button *btn_window_min;
	ui::Button *btn_window_close;
	ui::Button *btn_zoom_in;
	ui::Button *btn_zoom_out;
	ui::Button *btn_rotate;
	ui::Button *btn_upload;
	ui::Button *btn_backto_upload;
	ui::Button *btn_reset;
	ui::Button *btn_backto_editor;
	ui::Button *btn_goto_verify;
	ui::Button *btn_backto_verify;
	ui::Button *btn_cancel_verify;
	ui::Button *btn_goto_typeset;
	ui::Button *btn_print;
	ui::Button *btn_save;
	//PageViews
	ui::PageView *pageView_main;
	//UILayouts
	ui::Layout *panel_intro;
	ui::Layout *panel_upload;
	ui::Layout *panel_editor;
	ui::Layout *panel_verify;
	ui::Layout *panel_typeset;
	//Upload view related
	ui::ImageView *imageView_frame;
	ui::ImageView *imageView_back_ground;
	ui::ImageView *imageView_fore_ground;
	//Editor view related
	ui::ScrollView *scrollView_editor;
	ui::ImageView *imageView_editor;
	ui::ImageView *imageView_guide;
	//ListViews
	ui::ListView *listView_intro_size;
	ui::ListView *listView_upload_size;
	ui::ListView *listView_editor_size;
	ui::ListView *listView_verify_size;
	ui::ListView *listView_typeset_size;
	//Sliders
	ui::Slider *slider_photo_move;
	ui::Slider *slider_photo_scale;
	//ProgressBar
	ui::LoadingBar *progressBar_upload;
	//Popups
	PopupLayer *popup_upload_photo_invalid;
	PopupLayer *popup_save_photo_success;
	//Site variables
	int slider_scale_changed_value;
	int slider_move_changed_value;
	float cur_roated_value;
	float cur_moved_value;
	float cur_scaled_value;
	std::string cur_photo_file_path;
	cocos2d::CCSize cur_defined_size;

	//Popup related
	PopupLayer* createPopupLayer(const char *bgFilePath);
	void popupButtonCallback(cocos2d::CCNode *pNode);
};

#endif // __HELLOWORLD_SCENE_H__
