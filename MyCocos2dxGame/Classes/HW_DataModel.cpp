#include "HW_DataModel.h"
namespace HW_DataModel
{
	//default sizes of certificates
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_CERT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(500, 500), cocos2d::CCSizeMake(350, 450) };
	//default colors of certificates
	const std::vector<cocos2d::Color3B> HW_DataModel::ARRAY_OF_CERT_COLORS = { cocos2d::Color3B::RED, cocos2d::Color3B::GREEN, cocos2d::Color3B::BLUE, cocos2d::Color3B::WHITE, cocos2d::Color3B::BLACK, cocos2d::Color3B::GRAY};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_CERT_LABELS = { HW_StringUtils::WStrToUTF8(L"驾驶证（220X320）"), HW_StringUtils::WStrToUTF8(L"中国护照 （480X330）"), HW_StringUtils::WStrToUTF8(L"港澳通行证（480X330）"), HW_StringUtils::WStrToUTF8(L"台湾通行证（480X330）"), HW_StringUtils::WStrToUTF8(L"赴美签证（500X500）"), HW_StringUtils::WStrToUTF8(L"申根签证（350X450）") };
	//default sizes of print
	const std::vector<cocos2d::Size> HW_DataModel::ARRAY_OF_PRINT_SIZES = { cocos2d::CCSizeMake(220, 320), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330), cocos2d::CCSizeMake(480, 330)};
	//default labels of certificates
	const std::vector<std::string> HW_DataModel::ARRAY_OF_PRINT_LABELS = { HW_StringUtils::WStrToUTF8(L"4x6"), HW_StringUtils::WStrToUTF8(L"5x5"), HW_StringUtils::WStrToUTF8(L"6x6"), HW_StringUtils::WStrToUTF8(L"其它")};
}