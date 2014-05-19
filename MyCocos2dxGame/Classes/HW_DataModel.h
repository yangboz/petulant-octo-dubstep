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
		//Size_print related
		//default sizes of print
		static const std::vector<cocos2d::Size> ARRAY_OF_PRINT_SIZES;
		//default labels of certificates
		static const std::vector<std::string> ARRAY_OF_PRINT_LABELS;
	private:
	
	};
}
#endif