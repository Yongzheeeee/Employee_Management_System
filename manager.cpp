#include"manager.h"


//构造函数
manager::manager(int id, string name, int Did)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = Did;
}

//显示个人信息
void manager :: ShowInfo()\
{
    cout << "职工编号:" << this->m_ID
         << "\t员工姓名:" << this->m_Name
         << "\t岗位:"   << this->getDeptName()
         << "\t职责:完成老板交给的任务,并下发任务给员工" << endl;
}

//获取岗位名称
string manager :: getDeptName()
{
    return string("经理");
}
