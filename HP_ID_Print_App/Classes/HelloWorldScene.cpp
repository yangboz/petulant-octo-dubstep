﻿#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(cocos2d::Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu, 1);
	*/
    /////////////////////////////
    // 3. add your codes below...
	//UIElements behaviour
	//Load Layout
	this->uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioUI/CocoStudioUI.json");
	addChild(uiLayout);
	//PageViews(index,editor)
	this->pageView_main = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_main"));
	this->pageView_main->addEventListenerPageView(this, pagevieweventselector(HelloWorld::onPageViewTurning));
	//Panels
	this->panel_intro = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_intro"));
	this->panel_upload = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_upload"));
	this->panel_upload->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onPanelsTouch);
	this->panel_editor = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor"));
	this->panel_verifing = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_verifing"));
	this->panel_verified = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_verified"));
	this->panel_verified->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onPanelsTouch);
	this->panel_typeset = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_typeset"));
	///Manually disable the panel.
	this->pageView_main->setTouchEnabled(false);
	this->panel_intro->setTouchEnabled(false);
	this->panel_upload->setTouchEnabled(false);
	this->panel_editor->setTouchEnabled(false);
	this->panel_verifing->setTouchEnabled(false);
	//this->panel_verified->setTouchEnabled(false);
	this->panel_typeset->setTouchEnabled(false);
	//Window buttons
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_intro->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_upload->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_verifing->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_min = dynamic_cast<ui::Button*>(this->panel_typeset->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	//
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_intro->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_upload->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_verifing->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->panel_typeset->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	//Buttons in PageViewMain->Panel_intro/Panel_editor/Panel_typeset
	this->btn_zoom_in = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_zoom_in"));
	this->btn_zoom_in->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onZoomInButtonTouch);
	this->btn_zoom_out = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_zoom_out"));
	this->btn_zoom_out->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onZoomOutButtonTouch);
	this->btn_rotate = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_rotate"));
	this->btn_rotate->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onRotateButtonTouch);
	this->btn_upload = dynamic_cast<ui::Button*>(this->panel_upload->getChildByName("Button_upload"));
	this->btn_upload->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onUploadButtonTouch);
	this->btn_backto_upload = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_backto_upload"));
	this->btn_backto_upload->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onUploadNaviButtonTouch);
	this->btn_backto_editor = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_backto_editor"));
	this->btn_backto_editor->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onEditorNaviButtonTouch);
	this->btn_goto_verifing = dynamic_cast<ui::Button*>(this->panel_editor->getChildByName("Button_goto_verifing"));
	this->btn_goto_verifing->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onVerifingNaviButtonTouch);
	this->btn_backto_verified = dynamic_cast<ui::Button*>(this->panel_typeset->getChildByName("Button_backto_verified"));
	this->btn_backto_verified->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onVerifiedNaviButtonTouch);
	this->btn_cancel_verifing = dynamic_cast<ui::Button*>(this->panel_verifing->getChildByName("Button_cancel_verifing"));
	this->btn_cancel_verifing->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onUploadNaviButtonTouch);
	this->btn_goto_typeset = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_goto_typeset"));
	this->btn_goto_typeset->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onTypesetNaviButtonTouch);
	this->btn_print = dynamic_cast<ui::Button*>(this->panel_typeset->getChildByName("Button_print"));
	this->btn_print->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onPrintButtonTouch);
	this->btn_save = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_save"));
	this->btn_save->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onSaveButtonTouch);
	this->btn_red = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_red"));
	this->btn_red->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onRedColouredButtonTouch);
	this->btn_blue = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_blue"));
	this->btn_blue->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onBlueColouredButtonTouch);
	this->btn_white = dynamic_cast<ui::Button*>(this->panel_verified->getChildByName("Button_white"));
	this->btn_white->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWhiteColouredButtonTouch);
	//ImageViews
	///Panel_upload
	this->imageView_frame = dynamic_cast<ui::ImageView*>(this->panel_upload->getChildByName("Image_frame"));
	this->imageView_back_ground = dynamic_cast<ui::ImageView*>(this->imageView_frame->getChildByName("Image_background"));
	this->imageView_fore_ground = dynamic_cast<ui::ImageView*>(this->imageView_back_ground->getChildByName("Image_foreground"));
	this->imageView_instruction_upload = dynamic_cast<ui::ImageView*>(this->panel_upload->getChildByName("Image_instruction"));
	///Panel_editor
	this->scrollView_editor = dynamic_cast<ui::ScrollView*>(this->panel_editor->getChildByName("ScrollView_editor"));
	this->imageView_guide = dynamic_cast<ui::ImageView*>(this->panel_editor->getChildByName("Image_guide"));
	this->imageView_editor = dynamic_cast<ui::ImageView*>(this->scrollView_editor->getChildByName("Image_editor"));
	this->imageView_instruction_editor = dynamic_cast<ui::ImageView*>(this->panel_editor->getChildByName("Image_instruction"));
	///Panel_verifing
	this->imageView_verifing = dynamic_cast<ui::ImageView*>(this->panel_verifing->getChildByName("Image_verifing"));
	///Panel_verified
	this->scrollView_verified = dynamic_cast<ui::ScrollView*>(this->panel_verified->getChildByName("ScrollView_verified"));
	this->imageView_verified = dynamic_cast<ui::ImageView*>(this->scrollView_verified->getChildByName("Image_verified"));
	this->imageView_verified_result_0 = dynamic_cast<ui::ImageView*>(this->panel_verified->getChildByName("Image_verified_result_0"));
	this->imageView_verified_result_1 = dynamic_cast<ui::ImageView*>(this->panel_verified->getChildByName("Image_verified_result_1"));
	this->imageView_verified_result_2 = dynamic_cast<ui::ImageView*>(this->panel_verified->getChildByName("Image_verified_result_2"));
	///Panel_typeset
	this->imageView_typeset_frame = dynamic_cast<ui::ImageView*>(this->panel_typeset->getChildByName("Image_typeset_frame"));
	//ListViews
	this->listView_intro_size = dynamic_cast<ui::ListView*>(this->panel_intro->getChildByName("ListView_size"));
	this->listView_upload_size = dynamic_cast<ui::ListView*>(this->panel_upload->getChildByName("ListView_size"));
	this->listView_editor_size = dynamic_cast<ui::ListView*>(this->panel_editor->getChildByName("ListView_size"));
	this->listView_verifing_size = dynamic_cast<ui::ListView*>(this->panel_verifing->getChildByName("ListView_size"));
	this->listView_verified_size = dynamic_cast<ui::ListView*>(this->panel_verified->getChildByName("ListView_size"));
	this->listView_typeset_size = dynamic_cast<ui::ListView*>(this->panel_typeset->getChildByName("ListView_size"));
	//Sliders
	this->slider_photo_scale = dynamic_cast<ui::Slider*>(this->panel_editor->getChildByName("Slider_scale"));
	this->slider_photo_scale->addEventListenerSlider(this, sliderpercentchangedselector(HelloWorld::onScaleSliderValueChanged));
	this->slider_photo_rotate = dynamic_cast<ui::Slider*>(this->panel_editor->getChildByName("Slider_rotate"));
	this->slider_photo_rotate->addEventListenerSlider(this, sliderpercentchangedselector(HelloWorld::onRotateSliderValueChanged));
	//ProgressBar
	this->progressBar_upload = dynamic_cast<ui::LoadingBar*>(this->panel_upload->getChildByName("ProgressBar_upload"));
	this->progressBar_upload->setPercent(0);
	this->progressBar_verifing = dynamic_cast<ui::LoadingBar*>(this->panel_verifing->getChildByName("ProgressBar_verifing"));
	this->progressBar_verifing->setPercent(0);
	//Popups
	this->popup_upload_photo_invalid_size = NULL;
	this->popup_save_photo_success = NULL;
	this->popup_upload_photo_invalid_face = NULL;
	//ListView set up.
	this->setupListViews();
	//ScrollView event handler.
	this->scrollView_editor->addEventListenerScrollView(this, (ui::SEL_ScrollViewEvent)&HelloWorld::onScrollViewEdtiorTouch);
	//Default variables initialization
	this->cur_roated_value = 0.0f;
	this->cur_scaled_value = 1.0f;
	this->cur_moved_value_x = 0.0f;
	this->cur_moved_value_y = 0.0f;
	this->cur_colored_value = BG_COLOR_WHITE;
	this->userDefinedFolderFilePath = "";
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//EventHandlers
void HelloWorld::onUploadButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onUploadButtonTouch,TOUCH_EVENT_ENDED!");
		//Turn to open file picker and verifing steps.
		this->onOpenFilePicker();
		break;
	default:
			break;
	}
}

void HelloWorld::popupButtonCallback(cocos2d::CCNode *pNode)
{
	CCLOG("popup button call back. tag: %d", pNode->getTag());
}

void HelloWorld::onVerifyButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onVerifyButtonTouch,TOUCH_EVENT_ENDED!");
		//Photo verify function call here:
		this->pageView_main->scrollToPage(PAGE_VIEW_VERIFING);
		//Kind of verify function call here:
		HelloWorld::onVerify_Background();
		HelloWorld::onVerify_Clothing();
		HelloWorld::onVerify_Resolutiony();
		break;
	default:
		break;
	}
}
void HelloWorld::onTypesetButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onTypesetButtonTouch,TOUCH_EVENT_ENDED!");
		//Photo typeset function call here:
		this->pageView_main->scrollToPage(PAGE_VIEW_TYPESET);
		break;
	default:
		break;
	}
}
void HelloWorld::onPrintButtonTouch(Object *pSender, ui::TouchEventType type)
{
	std::string localPrinterName;
	IplImage *image;//cvLoadImage(this->cur_output_file_path.c_str());
	int tiledRows;
	int tiledColumns;
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onPrintButtonTouch,TOUCH_EVENT_ENDED!");
		//Save the tiling image file at first.
		tiledRows = HelloWorld::getCalculatedTileRows();
		tiledColumns = HelloWorld::getCalculatedTileCols();
		CCLOG("tiledRows:%i,tiledColumns:%i", tiledRows, tiledColumns);
		if (!OpenCvOperation::tilingImages(tiledRows, tiledColumns, this->cur_output_file_path, this->cur_output_tiled_file_path, HW_OPENCV_DEBUG))
		{
			MessageBox("Save tiled images failure!", "ERROR");
			return;
		}
		//Photo system print function call here:
		localPrinterName = PrintOperation::printDialog();
		if ( "" != localPrinterName)
		{
			//image = cvLoadImage(this->cur_output_tiled_file_path.c_str());
			//PrintOperation::printJpegImage(image, localPrinterName);
			PrintOperation::printCommand(this->cur_output_tiled_file_path, localPrinterName);
		}
		else
		{
			//MessageBox("Local printer invalid!", "ERROR");
			return;
		}
		break;
	default:
		break;
	}
}
///Verify view related
void HelloWorld::onRedColouredButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onRedColouredButtonTouch,TOUCH_EVENT_ENDED!");
		//Photo editor with background color function here:
		this->scrollView_verified->setBackGroundColor(cocos2d::Color3B::RED);
		//this->scrollView_editor->setBackGroundColor(cocos2d::Color3B::RED);
		this->cur_colored_value = BG_COLOR_RED;//Store user defined value for background.
		break;
	default:
		break;
	}
}
void HelloWorld::onBlueColouredButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onBlueColouredButtonTouch,TOUCH_EVENT_ENDED!");
		//Photo editor with background color function here:
		this->scrollView_verified->setBackGroundColor(cocos2d::Color3B::BLUE);
		//this->scrollView_editor->setBackGroundColor(cocos2d::Color3B::BLUE);
		this->cur_colored_value = BG_COLOR_BLUE;//Store user defined value for background.
		break;
	default:
		break;
	}
}
void HelloWorld::onWhiteColouredButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onWhiteColouredButtonTouch,TOUCH_EVENT_ENDED!");
		//Photo editor with background color function here:
		this->scrollView_verified->setBackGroundColor(cocos2d::Color3B::WHITE);
		//this->scrollView_editor->setBackGroundColor(cocos2d::Color3B::WHITE);
		this->cur_colored_value = BG_COLOR_WHITE;//Store user defined value for background.
		break;
	default:
		break;
	}
}
void HelloWorld::onSaveButtonTouch(Object *pSender, ui::TouchEventType type)
{

	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onSaveButtonTouch,TOUCH_EVENT_ENDED!");
		if (!HelloWorld::onSaveSolidColorBgImage(true))
		{
			MessageBox("Save background image file failure!", "ERROR");
		}
		if (HelloWorld::onSaveTilingResultImage())
		{
			//Popup notification.
			this->centerPopupLayer(HW_DataModel::HW_DataModel::BG_FILE_OF_SAVE_PHOTO_SUCCESS);
		}
		break;
	default:
		break;
	}
}
///
void HelloWorld::onIntroListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//std::string localPrinterName;
	Mat img;
	//std::string filePath = "C:\\Users\\yangboz\\Desktop\\乔伊.jpg";
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		//Testing code here:
		/*
		HW_StringUtils::gBKToUTF8(filePath);
		img = imread(filePath, CV_LOAD_IMAGE_UNCHANGED);
		if (img.empty())
		{
			CCLOG("OpenCV ImageLoad Failure！");
		}
		namedWindow("OpenCVLoadImageWindow", CV_WINDOW_AUTOSIZE);
		imshow("OpenCVLoadImageWindow", img);
		*/
		//localPrinterName = PrintOperation::printDialog();
		//OpenCvOperation::addingTwoImages("C:\\HP_ID_Print_output_foreground_.jpg", "C:\\HP_ID_Print_output_background_.png", "C:\\HP_ID_Print_output_result_fin_.png",HW_OPENCV_DEBUG);
		//OpenCvOperation::tilingImages(2, 2, "C:\\lena.png", "C:\\lena_.png", HW_OPENCV_DEBUG);
		//PrintOperation::printCommand("C:\\lena.png", localPrinterName);
		//OpenCvOperation::edgeDetection("C:\\lena.png",true);
		//OpenCvOperation::maxContourDetection("C:\\Users\\yangboz\\Desktop\\Cert_photos\\Passport_photo_2x2_inch.jpg", true);
		//OpenCvOperation::contoursDetection("C:\\lena.png", true);
		//OpenCvOperation::shirtDetection("C:\\Users\\yangboz\\Desktop\\Cert_photos\\Passport_photo_2x2_inch.jpg", true);
		//
		HW_UserDataModel::Instance()->cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		this->cur_defined_size = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index];
		CCLOG("onIntroListViewItemSelected index: %d", HW_UserDataModel::Instance()->cur_listView_selected_index);
		this->pageView_main->scrollToPage(PAGE_VIEW_UPLOAD);
		//Adjust the settings change effects.
		this->applyUploadSettingChanges();
		this->applyEditorSettingChanges();
		//Dynamically change the instruction image view content.
		this->changeCurrentInstructionImage();
		//
		break;
	default:
		break;
	}
}

void HelloWorld::onTypesetListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	int cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
	std::string background_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_FRAME_LABELS[cur_listView_selected_index];
	//
	Image *_photo = new Image();		
	_photo->initWithImageFile(this->cur_output_file_path);
	Texture2D *_photoTexture = new Texture2D();
	_photoTexture->initWithImage(_photo);
	//
	TMXTiledMap *_typeset_tileMap = NULL;
	TMXLayer *_foreground_layer = NULL;
	std::string cur_tileLayer_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_TMX_LABELS[cur_listView_selected_index];
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		CCLOG("listView_print selected child index: %d", cur_listView_selected_index);
		//Change typeset (background) frame image view here:
		this->imageView_typeset_frame->loadTexture(background_file_path);
		//Change the typeset foreground image view here:
		_typeset_tileMap = TMXTiledMap::create(cur_tileLayer_file_path);
		this->imageView_typeset_frame->removeAllChildren();
		this->imageView_typeset_frame->addChild(_typeset_tileMap);
		_typeset_tileMap->setPosition(cocos2d::CCPointMake(70,150));
		_foreground_layer = _typeset_tileMap->layerNamed("background");
		_foreground_layer->setTexture(_photoTexture);
		break;
	default:
		break;
	}
}

void HelloWorld::onUploadListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		HW_UserDataModel::Instance()->cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		CCLOG("onUploadListViewItemSelected index: %d", HW_UserDataModel::Instance()->cur_listView_selected_index);
		//Adjust the settings chnange effects.
		this->applyUploadSettingChanges();
		this->applyEditorSettingChanges();
		//Dynamically change the instrcution image view content.
		this->changeCurrentInstructionImage();
		break;
	default:
		break;
	}
}

void HelloWorld::onEditorListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		HW_UserDataModel::Instance()->cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		CCLOG("onUploadListViewItemSelected index: %d", HW_UserDataModel::Instance()->cur_listView_selected_index);
		//Adjust the settings chnange effects.
		this->applyUploadSettingChanges();
		this->applyEditorSettingChanges();
		break;
	default:
		break;
	}
}

void HelloWorld::onScaleSliderValueChanged(Object *pSender, ui::SliderEventType type)
{
	ui::Slider *slider = static_cast<ui::Slider*>(pSender);
	//const cocos2d::Size size = this->imageView_cert_origin->getSize();
	float scaleStepper = 0.01f;
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		this->cur_scaled_value = 1.0f + (slider->getPercent() - 50)*scaleStepper;
		CCLOG("onScaleSliderChanged,TOUCH_EVENT_ENDED,cur_scaled_value: %f", this->cur_scaled_value);
		//this->imageView_cert_origin->setSize(cocos2d::CCSizeMake(size.width*slider_changed_value / 100, size.height*slider_changed_value / 100));
		if (this->imageView_editor)
		{
			this->imageView_editor->setScale(this->cur_scaled_value);
		}
		break;
	default:
		break;
	}
}
void HelloWorld::onRotateSliderValueChanged(Object *pSender, ui::SliderEventType type)
{
	ui::Slider *slider = static_cast<ui::Slider*>(pSender);
	//const cocos2d::Size size = this->imageView_cert_origin->getSize();
	float rotateStepper = 10.0f;
	const cocos2d::Point orignalImagePoint = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	//
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		this->cur_roated_value = (slider->getPercent() - 50)*rotateStepper;
		CCLOG("onMoveSliderValueChanged,TOUCH_EVENT_ENDED,rotated value: %f", this->cur_roated_value);
		//
		if (this->imageView_editor)
		{
			this->imageView_editor->setRotation(this->cur_roated_value);
		}
		break;
	default:
		break;
	}
}
///Panel related touch to dismiss popup layers
void HelloWorld::onPanelsTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onPanelsTouch,TOUCH_EVENT_ENDED!");
		break;
	default:
		break;
	}
}
void HelloWorld::onPageViewTurning(Object *pSender, ui::PageViewEventType type)
{
	switch (type)
	{
	case PAGEVIEW_EVENT_TURNING:
		CCLOG("onPageViewTurning,TOUCH_EVENT_ENDED!");
		//
		break;
	default:
		break;
	}
}
///Windows system buttons
void HelloWorld::onWindowMinButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onWindowMinButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Windows minimize function here:

		break;
	default:
		break;
	}
}
void HelloWorld::onWindowCloseButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onWindowCloseButtonTouch,TOUCH_EVENT_ENDED!");
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
///Panel_editor related
void HelloWorld::onZoomInButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onZoomInButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->slider_photo_scale->setPercent(this->cur_scaled_value++);
		if (this->imageView_editor)
		{
			this->imageView_editor->setScale(this->cur_scaled_value);
		}
		break;
	default:
		break;
	}
}

void HelloWorld::onZoomOutButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onZoomOutButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->slider_photo_scale->setPercent(this->cur_scaled_value--);
		//
		if (this->imageView_editor)
		{
			this->imageView_editor->setScale(this->cur_scaled_value);
		}
		break;
	default:
		break;
	}
}

void HelloWorld::onRotateButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onRotateButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->cur_roated_value += 90.0f;
		this->imageView_editor->setRotation(this->cur_roated_value);
		break;
	default:
		break;
	}
}
///Navigation button related
void HelloWorld::onUploadNaviButtonTouch(Object *pSender, ui::TouchEventType type)
{
	
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onUploadNaviButtonTouch,TOUCH_EVENT_ENDED!");
		//Back to Panel_upload
		this->pageView_main->scrollToPage(PAGE_VIEW_UPLOAD);
		break;
	default:
		break;
	}
}
void HelloWorld::onEditorNaviButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onEditorNaviButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->pageView_main->scrollToPage(PAGE_VIEW_EDITOR);
		break;
	default:
		break;
	}
}
void HelloWorld::onVerifingNaviButtonTouch(Object *pSender, ui::TouchEventType type)
{
	cocos2d::Size definedSize = HelloWorld::getUserDefinedSize();
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onVerifingNaviButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->pageView_main->scrollToPage(PAGE_VIEW_VERIFING);
		this->progressBar_verifing->setPercent(50);
		//Photo transform handlers here:
		this->cur_moved_value_x = this->imageView_editor->getTouchMovePos().x;
		this->cur_moved_value_y = this->scrollView_editor->getTouchMovePos().y;
		CCLOG("cur_moved_value_x:%f,cur_moved_value_y:%f",this->cur_moved_value_x,this->cur_moved_value_y);
		/*
		if (!OpenCvOperation::saveRotatedImgeFile(this->cur_roated_value, this->cur_photo_file_path, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_ROTATED_FILE_NAME))
		{
			return;
		}
		if (!OpenCvOperation::saveScaledImageFile(this->cur_scaled_value, this->cur_photo_file_path, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_SCALED_FILE_NAME))
		{
			return;
		}
		
		if (!OpenCvOperation::saveMovedImageFile(this->cur_moved_value_x, this->cur_moved_value_y, this->cur_photo_file_path, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_MOVED_FILE_NAME))
		{
			return;
		}
		*/
		//OpenCvOperation::edgeDetection(this->cur_photo_file_path, true);
		if (!OpenCvOperation::saveTransformedImageFile(this->cur_roated_value, this->cur_scaled_value, this->cur_moved_value_x, this->cur_moved_value_y, this->cur_photo_file_path, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_TRANSFORMED_FILE_NAME))
		{
			return;
		}
		//OpenCvOperation::backgroundSubstraction_MOG_1(this->cur_photo_file_path);
		//OpenCvOperation::backgroundSubstraction_MOG_1(this->cur_photo_file_path);
		//OpenCvOperation::backgroundSubstraction_(this->cur_photo_file_path);
		if (OpenCvOperation::foregroundGrabcut(this->cur_photo_file_path, (int)definedSize.width, (int)definedSize.height, true, true))
		{
			
			this->progressBar_verifing->setPercent(100);
			this->pageView_main->scrollToPage(PAGE_VIEW_VERIFIED);
			this->imageView_verified->loadTexture(HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME);
		}
		break;
	default:
		break;
	}
}
void HelloWorld::onVerifiedNaviButtonTouch(Object *pSender, ui::TouchEventType type)
{
	std::string definedFolderFilePath;
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onVerifiedNaviButtonTouch,TOUCH_EVENT_ENDED!");
		//Default save image file function
		if (this->onSaveSolidColorBgImage(false) && this->onSaveTilingResultImage())
		{
			//
			this->pageView_main->scrollToPage(PAGE_VIEW_VERIFIED);
			//
			this->scrollView_verified->setBackGroundColor(cocos2d::ccColor3B::WHITE);
			//Keep state
			this->ori_image_verified_pos = this->imageView_verified->getPosition();
		}
		break;
	default:
		break;
	}
}
void HelloWorld::onTypesetNaviButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onTypesetNaviButtonTouch,TOUCH_EVENT_ENDED!");
		//
		this->pageView_main->scrollToPage(PAGE_VIEW_TYPESET);
		//
		this->imageView_verified->loadTexture(HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME);
		break;
	default:
		break;
	}
}
void HelloWorld::onScrollViewEdtiorTouch(Object *pSender, ui::ScrollviewEventType type)
{
	CCLOG("onScrollViewEdtiorTouch! %d", this->panel_editor->isTouchEnabled());
	//this->pageView_main->setTouchEnabled(false);
	//
	switch (type)
	{
	case SCROLLVIEW_EVENT_SCROLL_TO_LEFT:
		this->panel_editor->setTouchEnabled(false);
		break;
	case SCROLLVIEW_EVENT_SCROLL_TO_RIGHT:
		CCLOG("onScrollViewEdtiorTouch,TOUCH_EVENT_ENDED!");
		//
		break;
	default:
		break;
	}
}
//@see http://www.cocos2d-x.org/wiki/How_to_read_and_write_file_on_different_platforms
//@see http://msdn.microsoft.com/en-us/library/windows/apps/dn263165.aspx
//@see http://www.cocos2d-x.org/wiki/How_to_read_and_write_file_on_different_platforms
void HelloWorld::onOpenFilePicker()
{
	this->progressBar_upload->setPercent(10);
	//
	this->cur_photo_file_path = FileOperation::openFileDialog();
	if (this->cur_photo_file_path.size() == 0)
	{
		this->progressBar_upload->setPercent(0);
		return;//User cancel file picker;
	}
	this->progressBar_upload->setPercent(50);
	//TODO:ChineseCharacter issue;
	//this->pageView_main->scrollToPage(PAGE_VIEW_EDITOR);
	//this->imageView_editor->loadTexture(this->cur_photo_file_path);
	//return;
	//
	if (!OpenCvOperation::iplImageAttributesCheck(this->cur_photo_file_path))
	{
		//MessageBox("Invalid image with attributes(width/height/size..)!", "Error");
		this->centerPopupLayer(HW_DataModel::HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_SIZE);
		this->progressBar_upload->setPercent(0);
		return;
	}
	this->progressBar_upload->setPercent(90);
	//OpenCV handler here:
	int detectedFaces = OpenCvOperation::faceDetection(this->cur_photo_file_path, HW_OPENCV_DEBUG).size();
	if (detectedFaces != 1)//Only one face required for certification photo.
	{
		//return MessageBox("Required face invalid!", "ERROR");
		this->centerPopupLayer(HW_DataModel::HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_FACE);
		this->progressBar_upload->setPercent(0);
		return;
	}
	//All steps of panel_upload has complete.
	this->progressBar_upload->setPercent(100);
	//OpenCvOperation::fullbodyDetectAndDisplay_Haar(this->cur_photo_file_path);
	//OpenCvOperation::fullbodyDetectAndDisplay_Hog(this->cur_photo_file_path);
	//Image file on Panel_upload,go to panel_editor
	//this->imageView_fore_ground->loadTexture(this->cur_photo_file_path); return;
	this->pageView_main->scrollToPage(PAGE_VIEW_EDITOR);
	//Read image file for Panel_editor
	this->imageView_editor->loadTexture(this->cur_photo_file_path);
}
///
void HelloWorld::centerPopupLayer(const char *bgFilePath)
{
	if (bgFilePath == HW_DataModel::HW_DataModel::BG_FILE_OF_SAVE_PHOTO_SUCCESS)
	{
		if (NULL == this->popup_save_photo_success)
		{
			this->popup_save_photo_success = this->createPopupLayer(bgFilePath);
			this->addChild(this->popup_save_photo_success);
		}
	}
	else if (bgFilePath == HW_DataModel::HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_SIZE)
	{
		//
		if (NULL == this->popup_upload_photo_invalid_size)
		{
			this->popup_upload_photo_invalid_size = this->createPopupLayer(bgFilePath);
			this->addChild(this->popup_upload_photo_invalid_size);
		}
	}
	else if (bgFilePath == HW_DataModel::HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_FACE)
	{
		//
		if (NULL == this->popup_upload_photo_invalid_face)
		{
			this->popup_upload_photo_invalid_face = this->createPopupLayer(bgFilePath);
			this->addChild(this->popup_upload_photo_invalid_face);
		}
	}
	else
	{
		MessageBox("Invalid popupLayer parameter!", "Error");
		return;
	}
	//Schedule to remove the popuplayer
	this->schedule(schedule_selector(HelloWorld::removePopupLayer), 3, 1, 1);
}
///
PopupLayer* HelloWorld::createPopupLayer(const char *bgFilePath)
{
	PopupLayer *popup = PopupLayer::create(bgFilePath);
	popup->setTitle("");//As required
	//popup->setContentSize(CCSizeMake(400, 360));
	//popup->setContentText("xxxxxxx，yyyyyyy。xxxxxxx，yyyyyyy。", 20, 50, 150);
	// 设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮  
	// 这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了  
	//popup->setCallbackFunc(this, callfuncN_selector(HelloWorld::popupButtonCallback));
	// 添加按钮，设置图片，文字，tag 信息  
	//popup->addButton("CocoStudioUI/GUI/button.png", "CocoStudioUI/GUI/button.png", "OK", 0);
	//popup->addButton("CocoStudioUI/GUI/button.png", "CocoStudioUI/GUI/button.png", "Cancel", 1);
	return popup;
}
///
void HelloWorld::removePopupLayer(float interval)
{
	CCLOG("Scheduled for removePopupLayer:%f",interval);
	if (NULL != this->popup_upload_photo_invalid_size)
	{
		this->removeChild(this->popup_upload_photo_invalid_size);
		this->popup_upload_photo_invalid_size = NULL;
	}
	//
	if (NULL != this->popup_save_photo_success)
	{
		this->removeChild(this->popup_save_photo_success);
		this->popup_save_photo_success = NULL;
	}
	//
	if (NULL != this->popup_upload_photo_invalid_face)
	{
		this->removeChild(this->popup_upload_photo_invalid_face);
		this->popup_upload_photo_invalid_face = NULL;
	}
}
//Set up list views with size values.
void HelloWorld::setupListViews()
{
	//ui::Button *listView_default_button = ui::Button::create("CocoStudioUI/GUI/button.png", "CocoStudioUI/GUI/button.png");
	//listView_default_button->setTitleText(StringUtils::WStrToUTF8(L"护照"));
	//listView_certificates->pushBackDefaultItem();
	ssize_t count_size_intro = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int ii = 0; ii < count_size_intro; ++ii) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ii] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ii] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[i]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());
		//custom_button->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onCertListViewItemButtonTouch);

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_intro_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_size_upload = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int ij = 0; ij < count_size_upload; ++ij) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ij] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ij] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[i]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());
		//custom_button->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onCertListViewItemButtonTouch);

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_upload_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_editor = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int ik = 0; ik < count_editor; ++ik) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ik] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[ik] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_editor_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_verifing = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int il = 0; il < count_verifing; ++il) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[il] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[il] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_verifing_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_verified = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int il = 0; il < count_verified; ++il) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[il] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[il] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_verified_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_typeset = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_SIZES.size();
	for (int j = 0; j < count_typeset; ++j) {
		//insert custom item
		const std::string btn_up_str = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_LABELS[j] + ".png";
		const std::string btn_pd_str = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_LABELS[j] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_PRINT_LABELS[k]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_typeset_size->pushBackCustomItem(custom_item);
	}
	//
	/*
	this->listView_intro_size->setItemModel(listView_default_button);
	this->listView_upload_size->setItemModel(listView_default_button);
	this->listView_editor_size->setItemModel(listView_default_button);
	this->listView_verify_size->setItemModel(listView_default_button);
	*/
	//
	HW_UserDataModel::Instance()->cur_listView_selected_index = 0;//Default index selection.
	//
	this->listView_intro_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onIntroListViewItemSelected));
	this->listView_upload_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onUploadListViewItemSelected));
	this->listView_editor_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onEditorListViewItemSelected));
	//this->listView_verifing_size->setTouchEnabled(false);//Disable it for verifing.
	//this->listView_verified_size->setTouchEnabled(false);//Disable it for verified.
	this->listView_verifing_size->setEnabled(false);//Disable it for verifing.
	this->listView_verified_size->setEnabled(false);//Disable it for verified.
	this->listView_typeset_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onTypesetListViewItemSelected));
}
//
void HelloWorld::changeCurrentInstructionImage()
{
	std::string filePath =  HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_INSTRUCTION_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	this->imageView_instruction_upload->loadTexture(filePath);
	this->imageView_instruction_editor->loadTexture(filePath);
}
//
void HelloWorld::changeCurrentVerifiedResults()
{
	this->imageView_verified_result_0->loadTexture(HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_VALID_LABELS[0]);
	this->imageView_verified_result_1->loadTexture(HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_VALID_LABELS[1]);
	this->imageView_verified_result_2->loadTexture(HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_VALID_LABELS[2]);
}
//
void HelloWorld::applyUploadSettingChanges()
{
	this->progressBar_upload->setPercent(0);
	//Panel_upload
	std::string forground_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	std::string frame_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FRAME_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	std::string background_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint frame_position = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint foreground_position = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint background_position = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	//
	std::string cur_instruction_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_INSTRUCTION_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	//
	this->imageView_fore_ground->loadTexture(forground_file_path);
	//CCLOG("this->imageView_fore_ground->getPosition().x:%f,y:%f",this->imageView_fore_ground->getPosition().x, this->imageView_fore_ground->getPosition().y);
	this->imageView_fore_ground->setPosition(foreground_position);
	//
	this->imageView_back_ground->loadTexture(background_file_path);
	//CCLOG("this->imageView_back_ground->getPosition().x:%f,y:%f", this->imageView_back_ground->getPosition().x, this->imageView_back_ground->getPosition().y);
	this->imageView_back_ground->setPosition(background_position);
	//
	this->imageView_frame->setPosition(frame_position);
	//CCLOG("this->imageView_frame->getPosition().x:%f,y:%f", this->imageView_frame->getPosition().x, this->imageView_frame->getPosition().y);
	this->imageView_frame->loadTexture(frame_file_path);
}
void HelloWorld::applyEditorSettingChanges()
{
	//Panel_editor
	std::string guide_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_GUIDE_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	std::string scrollView_file_path = HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_SHADE_LABELS[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint imageView_guide_position = HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_GUIDE_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint imageView_editor_position = HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_PHOTO_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	cocos2d::CCPoint scrollView_position = HW_DataModel::HW_DataModel::ARRAY_OF_VERIFY_SHADE_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	//
	this->imageView_guide->loadTexture(guide_file_path);
	CCLOG("this->imageView_guide->getPosition().x:%f,y:%f", this->imageView_guide->getPosition().x, this->imageView_guide->getPosition().y);
	//this->imageView_guide->setPosition(imageView_guide_position);
	//this->imageView_editor->setPosition(imageView_editor_position);
	CCLOG("this->imageView_editor->getPosition().x:%f,y:%f", this->imageView_editor->getPosition().x, this->imageView_editor->getPosition().y);
	this->imageView_editor->setPosition(imageView_editor_position);
	//ScrollView with UIDragPanel
	this->scrollView_editor->setBackGroundImage(scrollView_file_path);
	CCLOG("this->scrollView_editor->getPosition().x:%f,y:%f", this->scrollView_editor->getPosition().x, this->scrollView_editor->getPosition().y);
	//this->scrollView_editor->setPosition(scrollView_position);
	//this->imageView_editor->setSize(definedSize);
	this->cur_defined_size = HW_DataModel::HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY[HW_UserDataModel::Instance()->cur_listView_selected_index];
	this->scrollView_editor->setInnerContainerSize(this->cur_defined_size);
	//this->scrollView_editor->setSize(this->cur_defined_size);
}
///Utility functions
cocos2d::Size HelloWorld::getUserDefinedSize()
{
	cocos2d::Size definedSize = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index];
	CCLOG("current user defined frame size is:(%f,%f)", definedSize.width, definedSize.height);
	return definedSize;
}
int HelloWorld::getCalculatedTileRows()
{
	int row = 1;
	cocos2d::Size definedSize = HelloWorld::getUserDefinedSize();
	cocos2d::Size cellSize = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_TMX_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index];
	row = (int)cellSize.height % (int)definedSize.height;
	//
	return row;
}
int HelloWorld::getCalculatedTileCols()
{
	int col = 1;
	//
	cocos2d::Size definedSize = HelloWorld::getUserDefinedSize();
	cocos2d::Size cellSize = HW_DataModel::HW_DataModel::ARRAY_OF_TYPESET_TMX_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index];
	col = (int)cellSize.width % (int)definedSize.width;
	//
	return col;
}
//Verify functions
bool HelloWorld::onVerify_Background()
{
	bool result = true;
	//
	return result;
}
bool HelloWorld::onVerify_Clothing()
{
	bool result = true;
	//
	return result;
}
bool HelloWorld::onVerify_Resolutiony()
{
	bool result = true;
	//
	return result;
}
//Save functions
bool HelloWorld::onSaveSolidColorBgImage(bool dialog)
{
	bool saved = false;
	cocos2d::Size definedSize = HelloWorld::getUserDefinedSize();
	//Get user defined save photo path:
	if (dialog)
	{
		this->userDefinedFolderFilePath = FileOperation::saveFileDialog();
		this->cur_output_file_path = this->userDefinedFolderFilePath + HW_DataModel::HW_DataModel::OUT_PUT_PRE_RESULT_FILE_NAME;
		this->cur_output_tiled_file_path = this->userDefinedFolderFilePath + HW_DataModel::HW_DataModel::OUT_PUT_FIN_RESULT_FILE_NAME;
	}
	else
	{
		this->cur_output_file_path = HW_DataModel::HW_DataModel::OUT_PUT_PRE_RESULT_FILE_NAME;
		this->cur_output_tiled_file_path =  HW_DataModel::HW_DataModel::OUT_PUT_FIN_RESULT_FILE_NAME;
	}
	CCLOG("cur_output_file_folder: %s", this->cur_output_file_path.c_str());
	//OpenCV save colored background image file:
	saved = OpenCvOperation::saveColoredImageFile(this->cur_colored_value, (int)definedSize.width, (int)definedSize.height, HW_DataModel::HW_DataModel::OUT_PUT_BACKGROUND_FILE_NAME.c_str());

	return saved;
}
bool HelloWorld::onSaveTilingResultImage()
{
	bool saved = false;
	//OpenCV add images(foreground,background):
	this->cur_foreground_file_path = HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME.c_str();
	this->cur_background_file_path = HW_DataModel::HW_DataModel::OUT_PUT_BACKGROUND_FILE_NAME.c_str();
	saved = OpenCvOperation::addingTwoImages(this->cur_foreground_file_path, this->cur_background_file_path, this->cur_output_file_path, HW_OPENCV_DEBUG);
	return saved;
}