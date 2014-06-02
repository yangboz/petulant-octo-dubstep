#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(140, 196), cocos2d::CCSizeMake(132, 192), cocos2d::CCSizeMake(156, 227), cocos2d::CCSizeMake(154, 220), cocos2d::CCSizeMake(154, 198), cocos2d::CCSizeMake(200, 200) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE, cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_CERT_LABELS = { "CocoStudioUI_1/photosize_menu/button_photosize_25_35", "CocoStudioUI_1/photosize_menu/button_photosize_22_32","CocoStudioUI_1/photosize_menu/button_photosize_33_48", "CocoStudioUI_1/photosize_menu/button_photosize_35_45","CocoStudioUI_1/photosize_menu/button_photosize_35_50","CocoStudioUI_1/photosize_menu/button_photosize_50_50"};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_EDITOR_INSTRUCTION_LABELS = { "CocoStudioUI_1/background/text/infomation_editphoto_01.png", "CocoStudioUI_1/background/text/infomation_editphoto_02.png", "CocoStudioUI_1/background/text/infomation_editphoto_03.png", "CocoStudioUI_1/background/text/infomation_editphoto_05.png", "CocoStudioUI_1/background/text/infomation_editphoto_04.png", "CocoStudioUI_1/background/text/infomation_editphoto_06.png" };
	//default sizes of print
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_TYPESET_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330) };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_TYPESET_LABELS = { "CocoStudioUI_1/papersize_menu/button_papersize_4x6", "CocoStudioUI_1/papersize_menu/button_papersize_5x7","CocoStudioUI_1/papersize_menu/button_papersize_a4"};
	//default file sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_FILE_SIZES = { cocos2d::CCSizeMake(14336, 30720), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200) };
	//Popup related
	const char* HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID = "CocoStudioUI_1/notification/pattern_notification_01.png";
	const char* HW_DataModel::BG_FILE_OF_SAVE_PHOTO_SUCCESS = "CocoStudioUI_1/notification/pattern_notification_02.png";
	//default position of certificates for editor/verify display
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_DISPLAY = { cocos2d::CCPointMake(323, 187), cocos2d::CCPointMake(327, 187), cocos2d::CCPointMake(415, 187), cocos2d::CCPointMake(416, 187), cocos2d::CCPointMake(416, 187), cocos2d::CCPointMake(393, 187) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY = { cocos2d::CCPointMake(800-321,450-185), cocos2d::CCPointMake(800-325,450-185), cocos2d::CCPointMake(900-413, 450-185), cocos2d::CCPointMake(900-414, 450-185), cocos2d::CCPointMake(900-414, 450-185), cocos2d::CCPointMake(900-391, 450-185) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_guide_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_guide_22x32.png", "CocoStudioUI_1/Photo_33x48/pattern_upload_photo_guide_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_guide_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_guide_35x50.png", "CocoStudioUI_1/Photo_50x50/pattern_upload_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_frame_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_frame_22x32.png", "CocoStudioUI_1/Photo_33x48/pattern_upload_photo_frame_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_frame_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_frame_35x50.png", "CocoStudioUI_1/Photo_50x50/pattern_upload_photo_frame_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_upload_photo_notice_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_upload_photo_notice_22x32.png", "CocoStudioUI_1/Photo_33x48/pattern_upload_photo_notice_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_upload_photo_notice_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_upload_photo_notice_35x50.png", "CocoStudioUI_1/Photo_50x50/pattern_upload_photo_notice_50x50.png" };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_PHOTO_DISPLAY = { cocos2d::CCPointMake(346, 187), cocos2d::CCPointMake(350, 187), cocos2d::CCPointMake(338, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(316, 187) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_DISPLAY = { cocos2d::CCPointMake(342, 183), cocos2d::CCPointMake(346, 183), cocos2d::CCPointMake(334, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(312, 183) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_GUIDE_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_edit_photo_guide_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_edit_photo_guide_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_edit_photo_guide_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_edit_photo_guide_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_edit_photo_guide_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_edit_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_LABELS = { "CocoStudioUI_1/Photo_25x35/pattern_edit_photo_frame_25x35.png", "CocoStudioUI_1/Photo_22x32/pattern_edit_photo_frame_22x32.png", "CocoStudioUI_1/photo_33x48/pattern_edit_photo_frame_33x48.png", "CocoStudioUI_1/Photo_35x45/pattern_edit_photo_frame_35x45.png", "CocoStudioUI_1/Photo_35x50/pattern_edit_photo_frame_35x50.png", "CocoStudioUI_1/photo_50x50/pattern_edit_photo_frame_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_VALID_LABELS = { "CocoStudioUI_1/background/icon_checklist_pass.png", "CocoStudioUI_1/background/icon_checklist_pass.png", "CocoStudioUI_1/background/icon_checklist_pass.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_INVALID_LABELS = { "CocoStudioUI_1/background/icon_checklist_error.png", "CocoStudioUI_1/background/icon_checklist_error.png", "CocoStudioUI_1/background/icon_checklist_error.png"};
	///Panel_typeset
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_TYPESET_FRAME_LABELS = { "CocoStudioUI_1/photo_on_paper/pattern_photo_on_paper_4x6.png", "CocoStudioUI_1/photo_on_paper/pattern_photo_on_paper_5x7.png", "CocoStudioUI_1/photo_on_paper/pattern_photo_on_paper_a4.png" };
	///Output file name
	const std::string HW_DataModel::OUT_PUT_PRE_RESULT_FILE_NAME = "\\HP_ID_Print_result_.jpg";
	const std::string HW_DataModel::OUT_PUT_FIN_RESULT_FILE_NAME = "\\HP_ID_Print_result_.jpg";
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME = "C:\\HP_ID_Print_output_foreground_.jpg";
	const std::string HW_DataModel::OUT_PUT_BACKGROUND_FILE_NAME = "C:\\HP_ID_Print_output_background_.jpg";
}