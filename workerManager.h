#pragma once         //防止头文件重复包含
#include<iostream>   //包含输入输出流头文件
using namespace std; //使用标准命名空间
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>

#define FILENAME "empFile.txt"

class workerManager
{
public:
    //构造函数
    workerManager();

    //成员函数
    //展示菜单
    void Show_Menu();

    //退出功能
    void exitSystem();

    //增加职工
    void Add_Emp();

    //保存数据至文件
    void save();

    //统计人数
    int get_Empnum();
    
    //初始化员工
    void init_Emp();

    //显示员工
    void show_Emp();

    //判断员工是否存在 很多功能都需要判断员工是否存在，不存在返回-1
    int isExist(int id);

    //删除员工
    void del_Emp();

    //修改职工
    void mod_Emp();

    //查找职工
    void find_Emp();

    //排序员工
    void Sort_Emp();

    //清空文件
    void clear_file();





    //成员属性
    //记录文件中的人员个数
    int m_EmpNum;

    //员工数组的指针（指向的是堆区中的数组）
    Worker** m_EmpArray;

    //判断文件是否为空
    bool m_Fileisempty;


    //析构函数
    ~workerManager();
};

