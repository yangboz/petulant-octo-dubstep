#include "HW_UserDataModel.h"

HW_UserDataModel* HW_UserDataModel::instance = 0;
HW_UserDataModel::HW_UserDataModel()
{
	cur_listView_selected_index = 0;//Default value.
}
HW_UserDataModel::~HW_UserDataModel()
{}

HW_UserDataModel* HW_UserDataModel::Instance()
{
	if (instance == 0) {
		instance = new HW_UserDataModel();
	}
	return instance;
}