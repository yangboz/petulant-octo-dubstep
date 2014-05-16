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

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace ui;
//OpenCV core
#include <opencv2\opencv.hpp>
using namespace cv;
//OpenCV face detection
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


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
	void onValidateButtonTouch(Object *pSender, ui::TouchEventType type);
	void onListViewItemSelected(Object *pSender, ui::ListViewEventType type);
	void onSliderValueChanged(Object *pSender, ui::SliderEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//OpenFilePickerTask
	void onOpenFilePicker();
	//OpenCV function header
	void faceDetectAndDisplay(cv::Mat frame);

private:
	ui::Widget *uiLayout;//MainLayout
	//PageViews
	ui::PageView *pageView_index;
	ui::PageView *pageView_editor;
	//Editor view related
	ui::ScrollView *scrollView_editor;
	ui::ImageView *imageView_cert_origin;
	//Labels
	ui::TextField *panel_index_lbl_size;
	ui::TextField *panel_index_lbl_validate;
	ui::TextField *panel_index_lbl_print;
	//ListViews
	ui::TextField *listView_index_lbl_size;
	ui::TextField *listView_index_lbl_validate;
	ui::TextField *listView_index_lbl_print;
	ui::ListView *listView_index_size;
	ui::ListView *listView_index_validate;
	ui::ListView *listView_index_print;
	//
	int listView_selected_index;
	int slider_changed_value;
	//OpenCV related variables
	//@see http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
	/** Global variables */
	std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
	std::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	std::string window_name = "Image_Face_detection";
	//cv::RNG rng(12345);
};

#endif // __HELLOWORLD_SCENE_H__
