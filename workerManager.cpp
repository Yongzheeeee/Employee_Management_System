#include "workerManager.h"



workerManager::workerManager()
{
    //初始化人数
    this->m_EmpNum = 0;

    //初始化数组指针
    this->m_EmpArray = NULL;

    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    //文件不存在情况
    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        
        //初始化人数
        this->m_EmpNum = 0; 

        //初始化数组指针
        this->m_EmpArray = NULL;

        //初始化文件为空标志
        this->m_Fileisempty = true;

        //ifs.close(); 文件流未打开，不需要关闭
        return;
    }

    //文件已存在，且没有记录
    char ch;
    ifs >> ch;  //只读一个字符，文档的结尾时eof 字符 ，
    if(ifs.eof())  //就算空文档不被读取，ifs.eof() 也 = false
    {
        cout << "文件已存在，且为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_Fileisempty = true;
        ifs.close();  //文件流打开，必须关闭
        return;
    }

    //文件已存在，且内部已有数据
    int num = this->get_Empnum();
    //cout << "职工的人数为：" << num << endl;
    this->m_EmpNum = num;
    this->m_Fileisempty = false;
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //初始化职工
    init_Emp();
    // //测试代码
    // for (int i = 0; i < m_EmpNum; i++)
    // {
    //     cout << this->m_EmpArray[i]->m_ID << " "
    //         << this->m_EmpArray[i]->m_Name << " "
    //         << this->m_EmpArray[i]->m_DeptID << endl;
    // }
    


}

//展示菜单
void workerManager::Show_Menu()
{
    cout << "**********************************************" << endl;
    cout << "**************欢迎使用职工管理系统*************" << endl;
    cout << "***************** 0.退出管理程序 **************" << endl;
    cout << "***************** 1.增加职工信息 **************" << endl;
    cout << "***************** 2.显示职工信息 **************" << endl;
    cout << "***************** 3.删除离职职工 **************" << endl;
    cout << "***************** 4.修改职工信息 **************" << endl;
    cout << "***************** 5.查找职工信息 **************" << endl;
    cout << "***************** 6.按照编号排序 **************" << endl;
    cout << "***************** 7.清空所有文档 **************" << endl;
    cout << "**********************************************" << endl;
    cout << endl;
}

void workerManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void workerManager::Add_Emp()
{
    cout << "请输入增加员工的数量：" << endl;
    
    int addNum = 0;
    cin >> addNum;
    
    if(addNum > 0)
    {
        //计算新的人数
        int newSize = this->m_EmpNum + addNum;

        //根据新人数 开辟符合大小的空间
        Worker** newSpace = new Worker*[newSize];

        //将原空间下内容 存放到新空间下
        if(this->m_EmpArray != NULL)
        {
            for(int i=0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //输入新的数据
        for(int i = 0 ;i < addNum; i++)
        {
            int id;
            string name;
            int dselect;

            cout << "请输入第"<< i+1 << "个员工编号:" << endl;
            cin >> id;

            cout << "请输入第"<< i+1 << "个员工姓名:" << endl;
            cin >> name;

            cout << "请输入岗位编号:" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dselect;

            Worker * worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new employee(id,name,1);
                break;
            case 2:
                worker = new manager(id,name,2);
                break;
            case 3:
                worker = new boss(id,name,3);
                break;
            
            default:
                break;
            }

            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新新的人数
        this->m_EmpNum = newSize;

        //更新职工表不为空标志
        this->m_Fileisempty = false;

        //提示信息
        cout << addNum <<"个新员工已添加成功" << endl;

        //保存到文件中
        this->save();
    }
    else
    {
        cout << "输入有误,请重新输入" << endl;
    }

    //按任意键后，清屏回答上级目录
    system("pause");
    system("cls");
}

void workerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for(int i=0;i < this->m_EmpNum ;i++)
    {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptID << endl;
    }

    ofs.close();

}

int workerManager::get_Empnum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int did;

    int num = 0;

    while(ifs >> id && ifs >> name && ifs >> did)
    {
        //记录人数
        num++;
    }
    ifs.close();

    return num;
}

void workerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int did;

    int index = 0;
    while(ifs >> id && ifs >> name && ifs >> did)
    {
        Worker * worker = NULL;
        if(did == 1)
        {
            worker = new employee(id,name,did);
        }
        else if (did == 2)
        {
            worker = new manager(id,name,did);
        }
        else
        {
            worker = new boss(id,name,did);
        }
        //存放进数组
        this->m_EmpArray[index] = worker;
        index++;
    }
    

}

void workerManager::show_Emp()
{
    if (this->m_Fileisempty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            //利用多态调用接口
            this->m_EmpArray[i]->ShowInfo();
        }     
    }
    system("pause");
    system("cls");
}

void workerManager::del_Emp()   //数组删除的本质就是 数据前移
{
    if (this->m_Fileisempty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        //按照职工编号删除
        int id = 0;
        cin >> id;

        int index = this->isExist(id);
        if(index != -1)  //员工存在，且删除index位置的信息
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum -- ;
            this->save();
            cout << "添加成功 " << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
    }
    system("pause");
    system("cls");
}

int workerManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_ID == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void workerManager::mod_Emp()
{
    if (this->m_Fileisempty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入想修改员工的编号" << endl;
        int id;
        cin >> id;

        int ret = this->isExist(id);
        if (ret != -1)
        {
            delete this->m_EmpArray[ret];

            int newid = 0;
            string newname = " ";
            int dselect = 0;

            cout << "查到：" << id << "号职工，请输入新编号：" << endl;
            cin >> newid;

            cout << "请输入新姓名:" << endl;
            cin >> newname;

            cout << "请输入岗位编号:" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dselect;

            Worker * worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new employee(id,newname,1);
                break;
            case 2:
                worker = new manager(id,newname,2);
                break;
            case 3:
                worker = new boss(id,newname,3);
                break;
            
            default:
                break;
            }

            this->m_EmpArray[ret]= worker;

            cout << "修改成功" << endl;
            this->save();
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    system("pause");
    system("cls");
}

void workerManager::find_Emp()
{
    if (this->m_Fileisempty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入查找方式：" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按姓名查找" << endl;

        int select = 0;
        cin >> select;

        if(select == 1)
        {
            int id;
            cout << "请输入查找的员工编号" << endl;
            cin >> id;

            int ret = this->isExist(id);
            if(ret != -1)
            {
                cout << "已查到 " << endl;
                this->m_EmpArray[ret]->ShowInfo();
            }
            else
            {
                cout << "查无此人 " << endl;    
            }
            
        }
        else if (select == 2)
        {
            string name;
            cout << "请输入查找的姓名：" << endl;
            cin >> name;
            
            bool flag = false; //查找到的标志
            for(int i; i < m_EmpNum; i++)
            {
                if(m_EmpArray[i]->m_Name == name)
                {
                    cout << "已查到 " << endl;
                    flag = true;
                    m_EmpArray[i]->ShowInfo();
                }
            }
            if (flag = false)
            {
                cout << "查无此人 " << endl;    
            }
        }
        else
        {
            cout << "输入有误" << endl;    
        }
    }
    system("pause");
    system("cls");
}

void workerManager::Sort_Emp()
{
    if (this->m_Fileisempty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
        system("cls");  
    }
    else
    {
        cout << "选择排序方式" << endl;
        cout << "1、升序" << endl;
        cout << "2、降序" << endl;

        int select = 0;
        cin >> select;

        for (int i = 0; i < m_EmpNum; i++)
        {
            int maxormin = i;
            for (int j = i+1; j < m_EmpNum; j++)
            {
                if (select ==1)
                {
                    if (m_EmpArray[maxormin]->m_ID > m_EmpArray[j]->m_ID)
                    {
                        maxormin = j;
                    }
                }
                else
                {
                    if (m_EmpArray[maxormin]->m_ID < m_EmpArray[j]->m_ID)
                    {
                        maxormin = j;
                    }
                }
            }
            if (i != maxormin)
            {
                Worker * temp = m_EmpArray[i];
                m_EmpArray[i] = m_EmpArray[maxormin];
                m_EmpArray[maxormin] = temp;
            }
        }
        cout << "排序成功" <<endl;
        this->save();
        this->show_Emp();
        

    }
}

void workerManager::clear_file()
{
    cout << "确认？" << endl;
    cout << "1、确认" << endl;
    cout << "2、取消" << endl;

    int select = 0;
    cin >> select;

    if (select ==1)
    {
        ofstream ofs;
        //trunc 如果存在 删除文件并新建
        ofs.open(FILENAME, ios::trunc);
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                }
        
            }
            this->m_EmpNum =0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_Fileisempty = true;
        }
        cout << " 清空完成" << endl;
    }
    system("pause");
    system("cls"); 
}

workerManager::~workerManager()
{
    if(this->m_EmpArray != NULL)
    {   
        // 先释放数组中每个指针指向的对象
        for(int i = 0; i < this->m_EmpNum; i++)
        {
            delete this->m_EmpArray[i];  // 释放每个Worker对象
            this->m_EmpArray[i] = NULL;
        }
        
        // 再释放指针数组本身
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }

}