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

    /////////////////////////////
    // 3. add your codes below...
	//UIElements behaviour
	//Load Layout
	this->uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioUI_1/CocoStudioUI_1.json");
	addChild(uiLayout);
	//PageViews(index,editor)
	this->pageView_index = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_index"));
	this->pageView_editor = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_editor"));
	//Editor view related
	this->scrollView_editor = dynamic_cast<ui::ScrollView*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("ScrollView_cert"));
	this->imageView_cert_origin = ui::ImageView::create();
	//Labels
	this->panel_index_lbl_size = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_size")->getChildByName("Panel_index_label"));
	this->panel_index_lbl_validate = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_validate")->getChildByName("Panel_index_label"));
	this->panel_index_lbl_print = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_print")->getChildByName("Panel_index_label"));
	//ListViews
	this->listView_index_lbl_size = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_size")->getChildByName("TextField_list_view_title"));
	this->listView_index_lbl_validate = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_validate")->getChildByName("TextField_list_view_title"));
	this->listView_index_lbl_print = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_print")->getChildByName("TextField_list_view_title"));
	this->listView_index_size = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_size")->getChildByName("ListView_size"));
	this->listView_index_validate = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_validate")->getChildByName("ListView_validate"));
	this->listView_index_print = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("PageView_index")->getChildByName("Panel_index_print")->getChildByName("ListView_print"));
	//Labels
	listView_index_lbl_size->setText(HW_StringUtils::WStrToUTF8(L"常用尺寸"));
	//
	ui::TextField *tl_panel_intro_note = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("TextField_panel_intro_notes"));
	tl_panel_intro_note->setText(HW_StringUtils::WStrToUTF8(L"护照照片注意事项"));
	//
	ui::TextField *tl_panel_intro_opt_0= dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("TextField_panel_intro_opt_0"));
	//tl_panel_intro_note->setText(HW_StringUtils::WStrToUTF8(L"护照照片注意事项"));
	//
	ui::TextField *tl_panel_intro_opt_1 = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("TextField_panel_intro_opt_1"));
	//tl_panel_intro_note->setText(HW_StringUtils::WStrToUTF8(L"护照照片注意事项"));
	//
	ui::TextField *tl_panel_intro_opt_2 = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("TextField_panel_intro_opt_2"));
	//tl_panel_intro_note->setText(HW_StringUtils::WStrToUTF8(L"护照照片注意事项"));
	//Buttons
	//
	ui::Button *button_open = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("Button_open"));
	button_open->setTitleText(HW_StringUtils::WStrToUTF8(L"打开"));
	button_open->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onOpenButtonTouch);
	
	//ui::ImageView *imageView_cert_origin = dynamic_cast<ui::ImageView*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Image_cert_origin"));
	//this->imageView_cert_origin = ui::ImageView::create();
	//
	ui::Button *button_verify = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Button_verify"));
	button_verify->setTitleText(HW_StringUtils::WStrToUTF8(L"验证"));
	button_verify->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onValidateButtonTouch);
	//
	ui::Slider *slider_editor = dynamic_cast<ui::Slider*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Slider_editor"));
	slider_editor->addEventListenerSlider(this, sliderpercentchangedselector(HelloWorld::onSliderValueChanged));
	//
	ui::Button *button_reset = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Button_reset"));
	button_reset->setTitleText(HW_StringUtils::WStrToUTF8(L"重置"));
	button_reset->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onResetButtonTouch);
	//ListView item model
	//
	ui::Button *listView_default_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
	//listView_default_button->setTitleText(StringUtils::WStrToUTF8(L"护照"));
	//listView_certificates->pushBackDefaultItem();

	ssize_t count = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS.size();
	for (int j = 0; j < count; ++j) {
		//insert custom item
		ui::Button *custom_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
		custom_button->setTitleText(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_LABELS[j]);
		custom_button->setScale9Enabled(true);
		custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(cocos2d::Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		listView_index_size->pushBackCustomItem(custom_item);
	}

	//
	ui::Layout *layout_listView = ui::Layout::create();
	layout_listView->setTouchEnabled(true);
	layout_listView->setSize(listView_default_button->getSize());
	layout_listView->setPosition(cocos2d::Point(layout_listView->getSize().width / 2.0f, layout_listView->getSize().height / 2.0f));
	layout_listView->addChild(listView_default_button);
	//
	listView_index_size->setItemModel(listView_default_button);
	//
	this->listView_selected_index = 0;//Default index selection.
	listView_index_size->addEventListenerListView(this, listvieweventselector(HelloWorld::onListViewItemSelected));
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
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onOpenButtonTouch,TOUCH_EVENT_ENDED!");
		this->onOpenFilePicker();
		break;
	default:
			break;
	}
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
		this->pageView_editor->scrollToPage(0);
		break;
	default:
		break;
	}
}

void HelloWorld::onValidateButtonTouch(Object *pSender, ui::TouchEventType type)
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


void HelloWorld::onListViewItemSelected(Object *pSender, ui::ListViewEventType type)
{
	ui::ListView *listView = static_cast<ListView*>(pSender);
	//
	switch (type)
	{
	case LISTVIEW_ONSELECTEDITEM_END:
		listView_selected_index = static_cast<int>(listView->getCurSelectedIndex());
		CCLOG("listView selected child index: %d", listView_selected_index);
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
		this->imageView_cert_origin->setScale(scaleValue);
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
	//MessageBox(NULL,"Welcome to Win32 Application Development!\n");
	//Navigate to PageView_editor
	this->pageView_editor->scrollToPage(1);
	//Read image file
	//FileOperation::readFile(filePath);
	this->imageView_cert_origin = ui::ImageView::create();
	this->imageView_cert_origin->loadTexture(filePath);
	//
	//ScrollView with UIDragPanel
	cocos2d::CCSize size = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[listView_selected_index];
	this->imageView_cert_origin->setSize(size);
	//this->scrollView_editor->setInnerContainerSize(cocos2d::CCSizeMake(size.width*(slider_changed_value / 100), size.height*(slider_changed_value / 100));
	this->scrollView_editor->addChild(this->imageView_cert_origin);
	this->scrollView_editor->scrollToPercentBothDirection(cocos2d::Point(50, 50), 1, true);
	this->scrollView_editor->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	this->scrollView_editor->setBackGroundColor(HW_DataModel::HW_DataModel::ARRAY_OF_CERT_COLORS[listView_selected_index]);
	//OpenCV handler here:
	cv::Mat img = imread(filePath);
	//Window display for testing.
	/*
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
	cv::imshow("image", img);
	cv::waitKey();
	*/
}
