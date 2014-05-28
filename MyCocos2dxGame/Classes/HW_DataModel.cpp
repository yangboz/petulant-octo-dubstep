﻿#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(140, 196), cocos2d::CCSizeMake(132, 192), cocos2d::CCSizeMake(156, 227), cocos2d::CCSizeMake(154, 220), cocos2d::CCSizeMake(154, 198), cocos2d::CCSizeMake(200, 200) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE, cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_CERT_LABELS = { "button_photosize_25_35", "button_photosize_22_32","button_photosize_33_48", "button_photosize_35_45","button_photosize_35_50","button_photosize_50_50"};
	//default sizes of print
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_PRINT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330)};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_PRINT_LABELS = { "button_papersize_4x6", "button_papersize_5x7","button_papersize_a4"};
	//default file sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_FILE_SIZES = { cocos2d::CCSizeMake(14336, 30720), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200) };
	//Popup related
	const char* HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID = "CocoStudioUI_1/notification/pattern_notification_01.png";
	const char* HW_DataModel::BG_FILE_OF_SAVE_PHOTO_SUCCESS = "CocoStudioUI_1/notification/pattern_notification_02.png";
	//default position of certificates for editor/verify display
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_DISPLAY = { cocos2d::CCPointMake(323, 500-187), cocos2d::CCPointMake(327, 187), cocos2d::CCPointMake(415, 187), cocos2d::CCPointMake(416, 187), cocos2d::CCPointMake(416, 187), cocos2d::CCPointMake(393, 187) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY = { cocos2d::CCPointMake(321,185), cocos2d::CCPointMake(325,185), cocos2d::CCPointMake(413, 185), cocos2d::CCPointMake(414, 185), cocos2d::CCPointMake(414, 185), cocos2d::CCPointMake(391, 185) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_guide_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_guide_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_upload_photo_guide_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_guide_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_guide_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_upload_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_frame_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_frame_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_upload_photo_frame_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_frame_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_frame_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_upload_photo_frame_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_notice_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_notice_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_upload_photo_notice_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_notice_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_notice_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_upload_photo_notice_50x50.png" };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_PHOTO_DISPLAY = { cocos2d::CCPointMake(346, 187), cocos2d::CCPointMake(350, 187), cocos2d::CCPointMake(338, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(316, 187) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_DISPLAY = { cocos2d::CCPointMake(342, 183), cocos2d::CCPointMake(346, 183), cocos2d::CCPointMake(334, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(312, 183) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_GUIDE_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_edit_photo_guide_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_edit_photo_guide_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_edit_photo_guide_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_edit_photo_guide_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_edit_photo_guide_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_edit_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_edit_photo_frame_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_edit_photo_frame_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_edit_photo_frame_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_edit_photo_frame_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_edit_photo_frame_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_edit_photo_frame_50x50.png" };
}