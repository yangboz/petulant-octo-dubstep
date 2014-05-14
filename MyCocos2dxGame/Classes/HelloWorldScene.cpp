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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	//Load Layout
	this->uiLayout = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioUI_1/CocoStudioUI_1.json");
	addChild(uiLayout);

	//UIElements behaviour
	//Labels、
	
	ui::TextField *lbl_list_view_cert = dynamic_cast<ui::TextField*>(uiLayout->getChildByName("TextField_list_view_cert"));
	lbl_list_view_cert->setText(HW_StringUtils::WStrToUTF8(L"常用尺寸"));
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
	//
	ui::Button *button_verify = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Button_verify"));
	button_verify->setTitleText(HW_StringUtils::WStrToUTF8(L"验证"));
	//
	ui::Button *button_reset = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Button_reset"));
	button_reset->setTitleText(HW_StringUtils::WStrToUTF8(L"重置"));
	button_reset->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onResetButtonTouch);
	//ListView
	ui::ListView *listView_certificates = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("ListView_certificates"));
	listView_certificates->setDirection(SCROLLVIEW_DIR_VERTICAL);
	//ListView item model
	//
	ui::Button *listView_default_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
	//listView_default_button->setTitleText(StringUtils::WStrToUTF8(L"护照"));
	//
	std::vector<std::string> _array_of_certs;
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"驾驶证（220X320）"));
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"中国护照 （480X330）"));
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"港澳通行证（480X330）"));
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"台湾通行证（480X330）"));
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"赴美签证（500X500）"));
	_array_of_certs.push_back(HW_StringUtils::WStrToUTF8(L"申根签证（350X450）"));
	//listView_certificates->pushBackDefaultItem();

	ssize_t count = _array_of_certs.size();
	for (int j = 0; j < count; ++j) {
		//insert custom item
		ui::Button *custom_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
		custom_button->setTitleText(_array_of_certs[j]);
		custom_button->setScale9Enabled(true);
		custom_button->setSize(listView_default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		listView_certificates->pushBackCustomItem(custom_item);
	}

	//
	ui::Layout *layout_listView = ui::Layout::create();
	layout_listView->setTouchEnabled(true);
	layout_listView->setSize(listView_default_button->getSize());
	layout_listView->setPosition(Point(layout_listView->getSize().width / 2.0f, layout_listView->getSize().height / 2.0f));
	layout_listView->addChild(listView_default_button);
	//
	listView_certificates->setItemModel(listView_default_button);
	//
	listView_certificates->addEventListenerListView(this, listvieweventselector(HelloWorld::onListViewItemSelected));
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
	ui::PageView *pageView = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_editor"));
	//
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("onResetButtonTouch,TOUCH_EVENT_ENDED!");
		//TODO:Reset function here:

		//Navigate to PageView_editor
		pageView->scrollToPage(0);
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

//@see http://www.cocos2d-x.org/wiki/How_to_read_and_write_file_on_different_platforms
//@see http://msdn.microsoft.com/en-us/library/windows/apps/dn263165.aspx
//@see http://www.cocos2d-x.org/wiki/How_to_read_and_write_file_on_different_platforms
void HelloWorld::onOpenFilePicker()
{
	std::string filePath = FileOperation::openFile();
	//MessageBox(NULL,"Welcome to Win32 Application Development!\n");
	//Navigate to PageView_editor
	ui::PageView *pageView = dynamic_cast<ui::PageView*>(this->uiLayout->getChildByName("PageView_editor"));
	pageView->scrollToPage(1);
	//Read image file
	//FileOperation::readFile(filePath);
	ui::ImageView *imageView_cert_origin = dynamic_cast<ui::ImageView*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Image_cert_origin"));
	//imageView_cert_origin->loadTexture(filePath);
	//
	//ScrollView with UIDragPanel
	ui::ScrollView *scrollView_cert = dynamic_cast<ui::ScrollView*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("ScrollView_cert"));
	cocos2d::CCSize size = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[listView_selected_index];
	scrollView_cert->setSize(size);
	//scrollView_cert->addChild(imageView_cert_origin);
}
