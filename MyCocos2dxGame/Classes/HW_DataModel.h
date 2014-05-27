#ifndef __HW_DATA_MODEL_H__
#define __HW_DATA_MODEL_H__

#include "cocos2d.h"
#include "HW_StringUtils.h"

USING_NS_CC;
namespace HW_DataModel
{
	class HW_DataModel
	{
	public:
		//Size_cert related
		//default sizes of certificates
		static const std::vector<cocos2d::Size> ARRAY_OF_CERT_SIZES;
		//default colors of certificates
		static const std::vector<cocos2d::Color3B> ARRAY_OF_CERT_COLORS;
		//default labels of certificates
		static const std::vector<std::string> ARRAY_OF_CERT_LABELS;
		//default position of certificates for editor/verify display
		//static const std::vector<cocos2d::Point> ARRAY_OF_EDITOR_BACKGROUND_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_EDITOR_FRAME_DISPLAY;
		static const std::vector<std::string> ARRAY_OF_EDITOR_BACKGROUND_LABELS;
		static const std::vector<std::string> ARRAY_OF_EDITOR_FRAME_LABELS;
		static const std::vector<std::string> ARRAY_OF_EDITOR_FOREGROUND_LABELS;
		static const std::vector<cocos2d::Point> ARRAY_OF_VERIFY_PHOTO_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_VERIFY_SHADE_DISPLAY;
		static const std::vector<std::string> ARRAY_OF_VERIFY_PHOTO_LABELS;
		static const std::vector<std::string> ARRAY_OF_VERIFY_SHADE_LABELS;
		//Size_print related
		//default sizes of print
		static const std::vector<cocos2d::Size> ARRAY_OF_PRINT_SIZES;
		//default labels of certificates
		static const std::vector<std::string> ARRAY_OF_PRINT_LABELS;
		//ImageAttributes validation
		static const std::vector<cocos2d::Size> ARRAY_OF_CERT_FILE_SIZES;
		//Popup related
		static const char* BG_FILE_OF_UPLOAD_PHOTO_INVALID;
		static const char* BG_FILE_OF_SAVE_PHOTO_SUCCESS;
	private:
	
	};
}
#endif