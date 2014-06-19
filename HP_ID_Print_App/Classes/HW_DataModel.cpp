#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(140, 196), cocos2d::CCSizeMake(132, 192), cocos2d::CCSizeMake(156, 227), cocos2d::CCSizeMake(154, 220), cocos2d::CCSizeMake(154, 198), cocos2d::CCSizeMake(200, 200) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE, cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_CERT_LABELS = { "CocoStudioUI/photosize_menu/button_photosize_25_35", "CocoStudioUI/photosize_menu/button_photosize_22_32","CocoStudioUI/photosize_menu/button_photosize_33_48", "CocoStudioUI/photosize_menu/button_photosize_35_45","CocoStudioUI/photosize_menu/button_photosize_35_50","CocoStudioUI/photosize_menu/button_photosize_50_50"};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_EDITOR_INSTRUCTION_LABELS = { "CocoStudioUI/background/text/infomation_editphoto_01.png", "CocoStudioUI/background/text/infomation_editphoto_02.png", "CocoStudioUI/background/text/infomation_editphoto_03.png", "CocoStudioUI/background/text/infomation_editphoto_05.png", "CocoStudioUI/background/text/infomation_editphoto_04.png", "CocoStudioUI/background/text/infomation_editphoto_06.png" };
	//default sizes of print
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_TYPESET_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330) };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_TYPESET_LABELS = { "CocoStudioUI/papersize_menu/button_papersize_4x6", "CocoStudioUI/papersize_menu/button_papersize_5x7","CocoStudioUI/papersize_menu/button_papersize_a4"};
	//default file sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_FILE_SIZES = { cocos2d::CCSizeMake(14336, 30720), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200) };
	//Popup related
	const char* HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_SIZE = "CocoStudioUI/notification/pattern_notification_01.png";
	const char* HW_DataModel::BG_FILE_OF_SAVE_PHOTO_SUCCESS = "CocoStudioUI/notification/pattern_notification_02.png";
	const char* HW_DataModel::BG_FILE_OF_UPLOAD_PHOTO_INVALID_FACE = "CocoStudioUI/notification/pattern_notification_03.png";
	//default position of certificates for editor/verify display
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_DISPLAY = { cocos2d::CCPointMake(72, 110), cocos2d::CCPointMake(70, 105), cocos2d::CCPointMake(80, 120), cocos2d::CCPointMake(80, 110), cocos2d::CCPointMake(80, 120), cocos2d::CCPointMake(100, 105) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_DISPLAY = { cocos2d::CCPointMake(72, 90), cocos2d::CCPointMake(70, 90), cocos2d::CCPointMake(80, 100), cocos2d::CCPointMake(80, 100), cocos2d::CCPointMake(80, 100), cocos2d::CCPointMake(100, 110) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_DISPLAY = { cocos2d::CCPointMake(800-321,450-185), cocos2d::CCPointMake(800-325,450-185), cocos2d::CCPointMake(900-413, 450-185), cocos2d::CCPointMake(900-414, 450-185), cocos2d::CCPointMake(900-414, 450-185), cocos2d::CCPointMake(900-391, 450-185) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_BACKGROUND_LABELS = { "CocoStudioUI/Photo_25x35/pattern_upload_photo_guide_25x35.png", "CocoStudioUI/Photo_22x32/pattern_upload_photo_guide_22x32.png", "CocoStudioUI/Photo_33x48/pattern_upload_photo_guide_33x48.png", "CocoStudioUI/Photo_35x45/pattern_upload_photo_guide_35x45.png", "CocoStudioUI/Photo_35x50/pattern_upload_photo_guide_35x50.png", "CocoStudioUI/Photo_50x50/pattern_upload_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FRAME_LABELS = { "CocoStudioUI/Photo_25x35/pattern_upload_photo_frame_25x35.png", "CocoStudioUI/Photo_22x32/pattern_upload_photo_frame_22x32.png", "CocoStudioUI/Photo_33x48/pattern_upload_photo_frame_33x48.png", "CocoStudioUI/Photo_35x45/pattern_upload_photo_frame_35x45.png", "CocoStudioUI/Photo_35x50/pattern_upload_photo_frame_35x50.png", "CocoStudioUI/Photo_50x50/pattern_upload_photo_frame_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_EDITOR_FOREGROUND_LABELS = { "CocoStudioUI/Photo_25x35/pattern_upload_photo_notice_25x35.png", "CocoStudioUI/Photo_22x32/pattern_upload_photo_notice_22x32.png", "CocoStudioUI/Photo_33x48/pattern_upload_photo_notice_33x48.png", "CocoStudioUI/Photo_35x45/pattern_upload_photo_notice_35x45.png", "CocoStudioUI/Photo_35x50/pattern_upload_photo_notice_35x50.png", "CocoStudioUI/Photo_50x50/pattern_upload_photo_notice_50x50.png" };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_GUIDE_DISPLAY = { cocos2d::CCPointMake(346, 187), cocos2d::CCPointMake(350, 187), cocos2d::CCPointMake(338, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(339, 187), cocos2d::CCPointMake(316, 187) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_PHOTO_DISPLAY = { cocos2d::CCPointMake(100, 165), cocos2d::CCPointMake(100, 165), cocos2d::CCPointMake(100, 165), cocos2d::CCPointMake(100, 165), cocos2d::CCPointMake(100, 165), cocos2d::CCPointMake(100, 165) };
	const std::vector<cocos2d::Point>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_DISPLAY = { cocos2d::CCPointMake(342, 183), cocos2d::CCPointMake(346, 183), cocos2d::CCPointMake(334, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(335, 183), cocos2d::CCPointMake(312, 183) };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_GUIDE_LABELS = { "CocoStudioUI/Photo_25x35/pattern_edit_photo_guide_25x35.png", "CocoStudioUI/Photo_22x32/pattern_edit_photo_guide_22x32.png", "CocoStudioUI/photo_33x48/pattern_edit_photo_guide_33x48.png", "CocoStudioUI/Photo_35x45/pattern_edit_photo_guide_35x45.png", "CocoStudioUI/Photo_35x50/pattern_edit_photo_guide_35x50.png", "CocoStudioUI/photo_50x50/pattern_edit_photo_guide_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_SHADE_LABELS = { "CocoStudioUI/Photo_25x35/pattern_edit_photo_frame_25x35.png", "CocoStudioUI/Photo_22x32/pattern_edit_photo_frame_22x32.png", "CocoStudioUI/photo_33x48/pattern_edit_photo_frame_33x48.png", "CocoStudioUI/Photo_35x45/pattern_edit_photo_frame_35x45.png", "CocoStudioUI/Photo_35x50/pattern_edit_photo_frame_35x50.png", "CocoStudioUI/photo_50x50/pattern_edit_photo_frame_50x50.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_VALID_LABELS = { "CocoStudioUI/background/icon_checklist_pass.png", "CocoStudioUI/background/icon_checklist_pass.png", "CocoStudioUI/background/icon_checklist_pass.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_VERIFY_INVALID_LABELS = { "CocoStudioUI/background/icon_checklist_error.png", "CocoStudioUI/background/icon_checklist_error.png", "CocoStudioUI/background/icon_checklist_error.png"};
	///Panel_typeset
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_TYPESET_FRAME_LABELS = { "CocoStudioUI/photo_on_paper/pattern_photo_on_paper_4x6.png", "CocoStudioUI/photo_on_paper/pattern_photo_on_paper_5x7.png", "CocoStudioUI/photo_on_paper/pattern_photo_on_paper_a4.png" };
	const std::vector<std::string>  HW_DataModel::ARRAY_OF_TYPESET_TMX_LABELS = { "data//tmx//305x220.tmx", "data//tmx//450x300.tmx", "data//tmx//465x330.tmx" };
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_TYPESET_TMX_SIZES = { cocos2d::CCSizeMake(2, 2), cocos2d::CCSizeMake(3, 2), cocos2d::CCSizeMake(3, 2)};
	///Output file name
	const std::string HW_DataModel::OUT_PUT_PRE_RESULT_FILE_NAME = "\\HP_ID_Print_result_pre.png";
	const std::string HW_DataModel::OUT_PUT_FIN_RESULT_FILE_NAME = "\\HP_ID_Print_result_fin.png";
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME = "HP_ID_Print_output_foreground_.png";//e.g:"C:\Users\yangboz\git\petulant-octo-dubstep\MyCocos2dxGame\Resources"
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_ROTATED_FILE_NAME = "HP_ID_Print_output_foreground_rotated_.png";
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_SCALED_FILE_NAME = "HP_ID_Print_output_foreground_scaled_.png";
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_MOVED_FILE_NAME = "HP_ID_Print_output_foreground_moved_.png";
	const std::string HW_DataModel::OUT_PUT_FOREGROUND_TRANSFORMED_FILE_NAME = "HP_ID_Print_output_foreground_transformed_.png";
	const std::string HW_DataModel::OUT_PUT_BACKGROUND_FILE_NAME = "HP_ID_Print_output_background_.png";
	const std::string HW_DataModel::OUT_PUT_RAW_FILE_NAME = "C:\\HP_ID_Print.jpg";
}