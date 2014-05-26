#include "HelloWorldScene.h"

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
	this->uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioUI_1/CocoStudioUI_1.json");
	addChild(uiLayout);
	//PageViews(index,editor)
	this->pageView_main = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_main"));
	//Window buttons
	this->btn_window_min = dynamic_cast<ui::Button*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_intro")->getChildByName("Button_window_min"));
	this->btn_window_min->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowMinButtonTouch);
	this->btn_window_close = dynamic_cast<ui::Button*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_intro")->getChildByName("Button_window_close"));
	this->btn_window_close->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onWindowCloseButtonTouch);
	//Buttons in PageViewMain->Panel_intro/Panel_editor/Panel_typeset
	this->btn_zoom_in = dynamic_cast<ui::Button*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_zoom_in"));
	this->btn_zoom_in->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onZoomInButtonTouch);
	this->btn_zoom_out = dynamic_cast<ui::Button*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_zoom_out"));
	this->btn_zoom_out->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onZoomOutButtonTouch);
	this->btn_rotate = dynamic_cast<ui::Button*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_rotate"));
	this->btn_rotate->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onRotateButtonTouch);
	this->btn_open = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_open"));
	//this->btn_open->setTitleText(HW_StringUtils::WStrToUTF8(L"打开"));
	this->btn_open->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onOpenButtonTouch);
	this->btn_verify = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_verify"));
	//this->btn_verify->setTitleText(HW_StringUtils::WStrToUTF8(L"验证"));
	this->btn_verify->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onVerifyButtonTouch);
	this->btn_typeset = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_typeset")->getChildByName("Button_typeset"));
	//this->btn_typeset->setTitleText(HW_StringUtils::WStrToUTF8(L"排版"));
	this->btn_typeset->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onTypesetButtonTouch);
	this->btn_print = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_print")->getChildByName("Button_print"));
	//this->btn_print->setTitleText(HW_StringUtils::WStrToUTF8(L"打印"));
	this->btn_print->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onPrintButtonTouch);
	this->btn_reset = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Button_reset"));
	//this->btn_reset->setTitleText(HW_StringUtils::WStrToUTF8(L"重置"));
	this->btn_reset->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onResetButtonTouch);
	//ImageViews
	this->scrollView_editor = dynamic_cast<ui::ScrollView*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("ScrollView_cert"));
	this->imageView_cert_origin = NULL;
	//ListViews
	this->listView_index_size = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_intro")->getChildByName("ListView_size"));
	this->listView_index_validate = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("ListView_size"));
	this->listView_index_print = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_typeset")->getChildByName("ListView_size"));
	//Sliders
	this->slider_photo_size = dynamic_cast<ui::Slider*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Slider_editor"));
	this->slider_photo_size->addEventListenerSlider(this, sliderpercentchangedselector(HelloWorld::onSliderValueChanged));
	//ListView item model
	this->assembleListViewOfPhotoSize();
	//
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
void HelloWorld::onOpenButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onOpenButtonTouch,TOUCH_EVENT_ENDED!");
		this->onOpenFilePicker();
		//For popup testing
		//this->popupLayerTesting();
		break;
	default:
			break;
	}
}

void HelloWorld::popupButtonCallback(cocos2d::CCNode *pNode)
{
	CCLOG("popup button call back. tag: %d", pNode->getTag());
}

void HelloWorld::onResetButtonTouch(Object *pSender, ui::TouchEventType type)
{
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onResetButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Reset function here:

		//Navigate to PageView_editor
		this->pageView_main->scrollToPage(0);
		break;
	default:
		break;
	}
}

void HelloWorld::onVerifyButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onValidateButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Photo validate function call here:

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
		//TODO:Photo print function call here:

		break;
	default:
		break;
	}
}
void HelloWorld::onPrintButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onPrintButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Photo system print function call here:
		
		break;
	default:
		break;
	}
}

void HelloWorld::onCertListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		HW_UserDataModel::Instance()->cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		CCLOG("listView_cert selected child index: %d", HW_UserDataModel::Instance()->cur_listView_selected_index);
		this->pageView_main->scrollToPage(1);
		break;
	default:
		break;
	}
}

void HelloWorld::onPrintListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		HW_UserDataModel::Instance()->cur_listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		CCLOG("listView_print selected child index: %d", HW_UserDataModel::Instance()->cur_listView_selected_index);
		break;
	default:
		break;
	}
}

void HelloWorld::onSliderValueChanged(Object *pSender, ui::SliderEventType type)
{
	ui::Slider *slider = static_cast<ui::Slider*>(pSender);
	//const cocos2d::Size size = this->imageView_cert_origin->getSize();
	float scaleValue = 1.00;
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		slider_changed_value = slider->getPercent();
		scaleValue = (1.00 + slider_changed_value / 100.00);
		CCLOG("onSliderValueChanged,TOUCH_EVENT_ENDED,scale value: %f", scaleValue);
		//this->imageView_cert_origin->setSize(cocos2d::CCSizeMake(size.width*slider_changed_value / 100, size.height*slider_changed_value / 100));
		if (this->imageView_cert_origin)
		{
			this->imageView_cert_origin->setScale(scaleValue);
		}
		break;
	default:
		break;
	}
}

void HelloWorld::onWindowMinButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onWindowMinButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Windows minize function here:

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

void HelloWorld::onCertListViewItemButtonTouch(Object *pSender, ui::TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		CCLOG("onCertListViewItemButtonTouch,TOUCH_EVENT_BEGAN!");
		//this->popupLayerTesting();
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onCertListViewItemButtonTouch,TOUCH_EVENT_ENDED!");
		break;
	default:
		break;
	}
}

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
		this->slider_photo_size->setPercent(this->slider_changed_value++);
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
		this->slider_photo_size->setPercent(this->slider_changed_value--);
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
		this->imageView_cert_origin->setRotation(this->cur_roate_value+90.0f);
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
	std::string filePath = FileOperation::openFile();
	if (filePath.size() == 0)
	{
		return;//User cancel file picker;
	}
	if (!OpenCvOperation::iplImageAttributesCheck(filePath))
	{
		MessageBox("Invalid image with attributes(width/height/size..)!", "Error");
	}
	//MessageBox(NULL,"Welcome to Win32 Application Development!\n");
	//Read image file
	//FileOperation::readFile(filePath);
	if (NULL == this->imageView_cert_origin)
	{
		this->imageView_cert_origin = ui::ImageView::create();
		this->scrollView_editor->addChild(this->imageView_cert_origin);
	}
	this->imageView_cert_origin->loadTexture(filePath);
	//TODO:Solid the parent panel
	//ui::Layout *panel_editor = dynamic_cast<ui::Layout*>(this->uiLayout->getChildByName("PageView_main")->getChildByName("Panel_eitor"));
	//panel_editor->setTouchEnabled(false);
	//FIXME:fixed ImageView loadTexture issue.
	//ui::ImageView *imageView_user_photo = dynamic_cast<ui::ImageView*>(uiLayout->getChildByName("PageView_main")->getChildByName("Panel_editor")->getChildByName("Image_user_photo"));
	//imageView_user_photo->loadTexture(filePath);
	//ScrollView with UIDragPanel
	cocos2d::CCSize size = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index];
	this->imageView_cert_origin->setSize(size);
	//this->scrollView_editor->setInnerContainerSize(cocos2d::CCSizeMake(size.width*(slider_changed_value / 100), size.height*(slider_changed_value / 100));
	//cocos2d::CCPoint centerPoint = CCPointMake(centerPoint.x + this->imageView_cert_origin->getSize().width / 2, centerPoint.y + this->imageView_cert_origin->getSize().height / 2);
	//this->imageView_cert_origin->setPosition(centerPoint);
	//this->imageView_cert_origin->setAnchorPoint(centerPoint);
	//this->scrollView_editor->scrollToPercentBothDirection(cocos2d::Point(50, 50), 1, true);
	this->scrollView_editor->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	this->scrollView_editor->setBackGroundColor(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_COLORS[HW_UserDataModel::Instance()->cur_listView_selected_index]);
	//OpenCV handler here:
	OpenCvOperation::faceDetectAndDisplay(filePath);
	//OpenCvOperation::fullbodyDetectAndDisplay_Haar(filePath);
	//OpenCvOperation::fullbodyDetectAndDisplay_Hog(filePath);
}

void HelloWorld::popupLayerTesting()
{
	//Testing code here:
	PopupLayer *popup = PopupLayer::create("C:\\lena.png");
	popup->setTitle("Popup!");
	//popup->setContentSize(CCSizeMake(400, 360));
	popup->setContentText("xxxxxxx，yyyyyyy。xxxxxxx，yyyyyyy。", 20, 50, 150);
	// 设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮  
	// 这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了  
	popup->setCallbackFunc(this, callfuncN_selector(HelloWorld::popupButtonCallback));
	// 添加按钮，设置图片，文字，tag 信息  
	popup->addButton("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png", "OK", 0);
	popup->addButton("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png", "Cancel", 1);
	this->addChild(popup);
}

void HelloWorld::assembleListViewOfPhotoSize()
{
	ui::Button *listView_default_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
	//listView_default_button->setTitleText(StringUtils::WStrToUTF8(L"护照"));
	//listView_certificates->pushBackDefaultItem();
	ssize_t count_size = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int i = 0; i < count_size; ++i) {
		//insert custom item
		const std::string btn_up_str = "CocoStudioUI_1/photosize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[i] + ".png";
		const std::string btn_pd_str = "CocoStudioUI_1/photosize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[i] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[i]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());
		custom_button->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onCertListViewItemButtonTouch);

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_index_size->pushBackCustomItem(custom_item);
	}
	ssize_t count_validate = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int j = 0; j < count_validate; ++j) {
		//insert custom item
		const std::string btn_up_str = "CocoStudioUI_1/photosize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j] + ".png";
		const std::string btn_pd_str = "CocoStudioUI_1/photosize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_index_validate->pushBackCustomItem(custom_item);
	}
	ssize_t count_print = HW_DataModel::HW_DataModel::ARRAY_OF_PRINT_LABELS.size();
	for (int k = 0; k < count_print; ++k) {
		//insert custom item
		const std::string btn_up_str = "CocoStudioUI_1/papersize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_PRINT_LABELS[k] + ".png";
		const std::string btn_pd_str = "CocoStudioUI_1/papersize_menu/" + HW_DataModel::HW_DataModel::ARRAY_OF_PRINT_LABELS[k] + "_pd.png";
		ui::Button *custom_button = ui::Button::create(btn_up_str, btn_pd_str);
		//custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_PRINT_LABELS[k]);
		//custom_button->setScale9Enabled(true);
		//custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		//
		listView_index_print->pushBackCustomItem(custom_item);
	}
	//
	this->listView_index_size->setItemModel(listView_default_button);
	this->listView_index_validate->setItemModel(listView_default_button);
	this->listView_index_print->setItemModel(listView_default_button);
	//
	HW_UserDataModel::Instance()->cur_listView_selected_index = 0;//Default index selection.
	//
	listView_index_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onCertListViewItemSelected));
	listView_index_validate->addEventListenerListView(this, listvieweventselector(HelloWorld::onCertListViewItemSelected));
	listView_index_print->addEventListenerListView(this, listvieweventselector(HelloWorld::onPrintListViewItemSelected));
}