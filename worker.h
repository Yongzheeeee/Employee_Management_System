#pragma once         //防止头文件重复包含
#include<iostream>   //包含输入输出流头文件
#include<string.h>
using namespace std; //使用标准命名空间

//职工抽象基类
class Worker
{
public:
    
    //显示个人信息
    virtual void ShowInfo() = 0;

    //获取岗位名称
    virtual string getDeptName() = 0;

    int m_ID;      //员工编号
    string m_Name; //员工名称
    int m_DeptID;  //员工所在部门名称编号
};