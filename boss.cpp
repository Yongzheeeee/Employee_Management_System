#include"boss.h"


//构造函数
boss::boss(int id, string name, int Did)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = Did;
}

//显示个人信息
void boss :: ShowInfo()\
{
    cout << "职工编号:" << this->m_ID
         << "\t员工姓名:" << this->m_Name
         << "\t岗位:"   << this->getDeptName()
         << "\t职责:管理公司所有事务" << endl;
}

//获取岗位名称
string boss :: getDeptName()
{
    return string("总裁");
}
