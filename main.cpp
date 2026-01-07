#include<iostream>
using namespace std;
#include<string>
#include "workerManager.h"

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{

    // //测试代码
    // Worker * worker1 = NULL;
    // worker1 = new employee(1, "张三", 1);
    // worker1->ShowInfo();
    
    // Worker * worker2 = NULL;
    // worker2 = new manager(2, "李四", 2);
    // worker2->ShowInfo();
    
    // Worker * worker3 = NULL;
    // worker3 = new boss(3, "王五", 3);
    // worker3->ShowInfo();

    workerManager vm;
    int choice = 0;
    while (1)
    {
        vm.Show_Menu();
        cout << "请输入你的选择" << endl;
        cin >> choice;
        switch (choice)
        {
            case 0:  //退出系统
                vm.exitSystem();
                break;
            case 1:  //添加职工
                vm.Add_Emp();
                break;
            case 2:  //显示职工
                vm.show_Emp();
                break;
            case 3:  //删除职工
                vm.del_Emp();
                break;
            case 4:  //修改职工
                vm.mod_Emp();
                break;
            case 5:  //查找职工
                vm.find_Emp(); 
                break;
            case 6:  //排序职工
                vm.mod_Emp();
                break;
            case 7:  //清空文件
                vm.clear_file();
                break;
            
            default:
                system("cls");
                break;
        }
    }
    

    system("pause");
    return 0;
}