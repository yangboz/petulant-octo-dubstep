#include "HelloWorldScene.h"

#include "FileOperation.h"


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
	//Buttons
	//
	ui::Button *button_open = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_intro")->getChildByName("Button_open"));
	button_open->setTitleText(WStrToUTF8(L"打开"));
	button_open->addTouchEventListener(this, (ui::SEL_TouchEvent)&HelloWorld::onOpenButtonTouch);
	//
	ui::Button *button_verify = dynamic_cast<ui::Button*>(uiLayout->getChildByName("PageView_editor")->getChildByName("Panel_editor")->getChildByName("Button_verify"));
	button_verify->setTitleText(WStrToUTF8(L"验证"));
	//
	ui::Button *button_more_certs = dynamic_cast<ui::Button*>(uiLayout->getChildByName("Button_more_certs"));
	button_more_certs->setTitleText(WStrToUTF8(L"+ 添加常用尺寸"));
	//ListView
	ui::ListView *listView_certificates = dynamic_cast<ui::ListView*>(uiLayout->getChildByName("ListView_certificates"));
	listView_certificates->setDirection(SCROLLVIEW_DIR_VERTICAL);
	//ListView item model
	//
	ui::Button *listView_default_button = ui::Button::create("CocoStudioUI_1/GUI/button.png", "CocoStudioUI_1/GUI/button.png");
	//listView_default_button->setTitleText(WStrToUTF8(L"护照"));
	//
	std::vector<std::string> _array_of_certs;
	_array_of_certs.push_back(WStrToUTF8(L"驾驶证（220X320）"));
	_array_of_certs.push_back(WStrToUTF8(L"中国护照 （480X330）"));
	_array_of_certs.push_back(WStrToUTF8(L"港澳通行证（480X330）"));
	_array_of_certs.push_back(WStrToUTF8(L"台湾通行证（480X330）"));
	_array_of_certs.push_back(WStrToUTF8(L"赴美签证（500X500）"));
	_array_of_certs.push_back(WStrToUTF8(L"申根签证（350X450）"));
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

//Chinese character warpper
//! convert from wstring to UTF8 using self-coding-converting  
void HelloWorld::WStrToUTF8Convert(std::string& dest, const std::wstring& src){
	dest.clear();

	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation  
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}
std::string HelloWorld::WStrToUTF8(const std::wstring &str)
{
	std::string result;
	WStrToUTF8Convert(result, str);
	return result;
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
	imageView_cert_origin->loadTexture(filePath);
}
