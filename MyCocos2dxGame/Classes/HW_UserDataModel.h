#ifndef __HW_USER_DATA_MODEL_H__
#define __HW_USER_DATA_MODEL_H__

#include <stddef.h>// defines NULL

class HW_UserDataModel
{
private:
	HW_UserDataModel();
	static HW_UserDataModel *instance;

public:
	static HW_UserDataModel * Instance();
	//Current displayed list view's seleted index.
	int cur_listView_selected_index;
	//
	~HW_UserDataModel();
};

#endif