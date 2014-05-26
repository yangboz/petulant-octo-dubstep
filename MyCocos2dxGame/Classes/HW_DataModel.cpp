﻿#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(500, 500), cocos2d::CCSizeMake(350, 450) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE, cocos2d::Color3B::RED, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE };
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_CERT_LABELS = { "button_photosize_25_35", "button_photosize_22_32","button_photosize_33_45", "button_photosize_33_48", "button_photosize_35_45","button_photosize_35_50","button_photosize_50_50"};
	//default sizes of print
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_PRINT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330)};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_PRINT_LABELS = { "button_papersize_4x6", "button_papersize_5x7","button_papersize_a4"};
	//default file sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_FILE_SIZES = { cocos2d::CCSizeMake(14336, 30720), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200), cocos2d::CCSizeMake(40960, 51200) };
}