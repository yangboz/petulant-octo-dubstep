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
		//default position of certificates for upload/editor/verify display
		///Panel_Editor && Panel_Upload
		static const std::vector<cocos2d::Point> ARRAY_OF_EDITOR_FOREGROUND_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_EDITOR_BACKGROUND_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_EDITOR_FRAME_DISPLAY;
		static const std::vector<std::string> ARRAY_OF_EDITOR_INSTRUCTION_LABELS;
		static const std::vector<std::string> ARRAY_OF_EDITOR_BACKGROUND_LABELS;
		static const std::vector<std::string> ARRAY_OF_EDITOR_FRAME_LABELS;
		static const std::vector<std::string> ARRAY_OF_EDITOR_FOREGROUND_LABELS;
		///Panel_Verify
		static const std::vector<cocos2d::Point> ARRAY_OF_VERIFY_GUIDE_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_VERIFY_PHOTO_DISPLAY;
		static const std::vector<cocos2d::Point> ARRAY_OF_VERIFY_SHADE_DISPLAY;
		static const std::vector<std::string> ARRAY_OF_VERIFY_SHADE_LABELS;
		static const std::vector<std::string> ARRAY_OF_VERIFY_GUIDE_LABELS;
		static const std::vector<std::string> ARRAY_OF_VERIFY_VALID_LABELS;
		static const std::vector<std::string> ARRAY_OF_VERIFY_INVALID_LABELS;
		//Size_typeset related
		//default sizes of typeset
		static const std::vector<cocos2d::Size> ARRAY_OF_TYPESET_SIZES;
		//default labels of certificates
		static const std::vector<std::string> ARRAY_OF_TYPESET_LABELS;
		//ImageAttributes validation
		static const std::vector<cocos2d::Size> ARRAY_OF_CERT_FILE_SIZES;
		//Popup related
		static const char* BG_FILE_OF_UPLOAD_PHOTO_INVALID_SIZE;
		static const char* BG_FILE_OF_UPLOAD_PHOTO_INVALID_FACE;
		static const char* BG_FILE_OF_SAVE_PHOTO_SUCCESS;
		///Panel_typeset
		static const std::vector<std::string> ARRAY_OF_TYPESET_FRAME_LABELS;
		static const std::vector<std::string> ARRAY_OF_TYPESET_TMX_LABELS;
		static const std::vector<cocos2d::Size> ARRAY_OF_TYPESET_TMX_SIZES;
		///Output file name
		static const std::string OUT_PUT_PRE_RESULT_FILE_NAME;
		static const std::string OUT_PUT_FIN_RESULT_FILE_NAME;
		static const std::string OUT_PUT_FOREGROUND_FILE_NAME;
		static const std::string OUT_PUT_FOREGROUND_ROTATED_FILE_NAME;
		static const std::string OUT_PUT_FOREGROUND_SCALED_FILE_NAME;
		static const std::string OUT_PUT_FOREGROUND_MOVED_FILE_NAME;
		static const std::string OUT_PUT_FOREGROUND_TRANSFORMED_FILE_NAME;
		static const std::string OUT_PUT_BACKGROUND_FILE_NAME;
		static const std::string OUT_PUT_RAW_FILE_NAME;
	private:
	
	};
}
#endif