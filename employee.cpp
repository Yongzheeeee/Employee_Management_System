#include"employee.h"


//构造函数
employee::employee(int id, string name, int Did)
{
    this->m_ID = id;
    this->m_Name = name;
    this->m_DeptID = Did;
}

//显示个人信息
void employee :: ShowInfo()\
{
    cout << "职工编号:" << this->m_ID
         << "\t员工姓名:" << this->m_Name
         << "\t岗位:"   << this->getDeptName()
         << "\t职责:完成经理交给的任务" << endl;
}

//获取岗位名称
string employee :: getDeptName()
{
    return string("员工");
}
