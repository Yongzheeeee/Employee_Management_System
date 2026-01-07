#pragma once         //防止头文件重复包含
#include<iostream>   //包含输入输出流头文件
#include<string.h>
using namespace std; //使用标准命名空间
#include"worker.h"

//员工类
class boss : public Worker
{
public:

    //构造函数
    boss(int id, string name, int Did);
    
    //显示个人信息
    virtual void ShowInfo();

    //获取岗位名称
    virtual string getDeptName();

};