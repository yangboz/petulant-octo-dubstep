#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(500, 500), cocos2d::CCSizeMake(350, 450) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B(0, 0, 0), cocos2d::Color3B(50, 50, 50), cocos2d::Color3B(100, 100, 100), cocos2d::Color3B(150, 150, 150), cocos2d::Color3B(200, 200, 200), cocos2d::Color3B(250, 250, 250) };
}