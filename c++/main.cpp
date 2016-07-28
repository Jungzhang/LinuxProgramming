/*************************************************************************
	> File Name: myDB.cpp
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月04日 星期六 19时10分05秒
	> Description:
 ************************************************************************/
#include <iostream>
#include <cstdlib>
#include <vector>

#include <unistd.h>

#include "Student.h"

void MainMenu()
{
    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　 学生成绩管理系统\n" << std::endl;
    std::cout << "\t\t\t\t\t1. 增 加 学 生 信 息\n" << std::endl;
    std::cout << "\t\t\t\t\t2. 删 除 学 生 信 息\n" << std::endl;
    std::cout << "\t\t\t\t\t3. 修 改 学 生 成 绩\n" << std::endl;
    std::cout << "\t\t\t\t\t4. 查 询 学 生 成 绩\n" << std::endl;
    std::cout << "\t\t\t\t\t0. 退 出 管 理 系 统\n" << std::endl;
    std::cout << "\t\t\t\t  　请选择：";
}

void QueryMenu()
{
    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　　 查询学生成绩\n" << std::endl;
    std::cout << "\t\t\t\t\t1. 根 据 学 号 查 询\n" << std::endl;
    std::cout << "\t\t\t\t\t2. 查 询 所 有 成 绩\n" << std::endl;
    std::cout << "\t\t\t\t\t3. 排 序 查 询 所 有\n" << std::endl;
    std::cout << "\t\t\t\t\t9. 返 回 上 一 级 菜 单\n" << std::endl;
    std::cout << "\t\t\t\t\t0. 退 出 管 理 系 统\n" << std::endl;
    std::cout << "\t\t\t\t  　请选择：";
}

void AddStudent()
{
    std::string id;
    std::string name;
    int Clanguage;
    int DataStruct;
    int DB;
    unsigned int TotalScore;

    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　 请您输入学生信息\n" << std::endl;
    std::cout << "\t\t\t\t\t学号：";
    std::cin >> id;
    std::cout << "\t\t\t\t\t姓名：";
    std::cin >> name;
    std::cout << "\t\t\t\t\tC语言：";
    std::cin >> Clanguage;
    std::cout << "\t\t\t\t\t数据结构：";
    std::cin >> DataStruct;
    std::cout << "\t\t\t\t\t数据库：";
    std::cin >> DB;

    Student stu(id, name, Clanguage, DataStruct, DB);

    int returnVal = stu.AddStuInfo(stu);
    
    if (returnVal == 1) {
        std::cout << "\n\t\t\t\t\t　 学生信息添加成功\n" << std::endl;
    } else if (returnVal == 0) {
        std::cout << "\n\t\t\t\t\t　 学生信息输入有误\n" << std::endl;
    } else if (returnVal == -1) {
        std::cout << "\n\t\t\t\t\t　 数据库连接失败\n" << std::endl;
    } else {
        std::cout << "\n\t\t\t\t\t　 您输入的学生信息已存在\n" << std::endl;
    }
    std::cout << "\n按回车键继续。。。";
    setbuf(stdin, nullptr);
    getchar();
}

void delStuInfo()
{
    std::string id;
    Student stu;

    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　 删除学生信息\n" << std::endl;
    std::cout << "\t\t\t\t\t请输入学号：";
    std::cin >> id;
    
    int returnVal = stu.DelStuInfo(id);

    if (returnVal == 1) {
        std::cout << "\n\t\t\t\t\t　 学生信息删除成功\n" << std::endl;
    } else if (returnVal == 0) {
        std::cout << "\n\t\t\t\t\t　 学生记录不存在\n" << std::endl;
    } else if (returnVal == -1) {
        std::cout << "\n\t\t\t\t\t　 数据库连接失败\n" << std::endl;
    } else {
        std::cout << "\n\t\t\t\t\t　 SQL语句执行错误\n" << std::endl;
    }
    std::cout << "\n按回车键继续。。。";
    setbuf(stdin, nullptr);
    getchar();
}

void ModStuInfo()
{ 
    std::string id;
    std::string name;
    int Clanguage;
    int DataStruct;
    int DB;
    unsigned int TotalScore;

    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　 请输入修改后的学生信息\n" << std::endl;
    std::cout << "\t\t\t\t\t学号：";
    std::cin >> id;
    std::cout << "\t\t\t\t\t姓名：";
    std::cin >> name;
    std::cout << "\t\t\t\t\tC语言：";
    std::cin >> Clanguage;
    std::cout << "\t\t\t\t\t数据结构：";
    std::cin >> DataStruct;
    std::cout << "\t\t\t\t\t数据库：";
    std::cin >> DB;

    Student stu(id, name, Clanguage, DataStruct, DB);

    int returnVal = stu.ModStuInfo(id, stu);
    
    if (returnVal == 1) {
        std::cout << "\n\t\t\t\t\t　 学生信息修改成功\n" << std::endl;
    } else if (returnVal == 0) {
        std::cout << "\n\t\t\t\t\t　 学生信息输入有误\n" << std::endl;
    } else if (returnVal == -1) {
        std::cout << "\n\t\t\t\t\t　 数据库连接失败\n" << std::endl;
    } else if (returnVal == -3){
        std::cout << "\n\t\t\t\t\t　 您输入的学生信息不存在\n" << std::endl;
    } else {
        std::cout << "\n\t\t\t\t\t　 SQL语句执行失败\n" << std::endl;
    }
    std::cout << "\n按回车键继续。。。";
    setbuf(stdin, nullptr);
    getchar();
}

void QueryStuInfo()
{
    std::string id;
    Student stu;

    system("/clear");
    std::cout << "\n\n\n\n\n\t\t\t\t\t　 查询学生信息\n" << std::endl;
    std::cout << "\t\t\t\t\t请输入学号：";
    std::cin >> id;

    int returnVal = stu.ShowStuInfo(id, stu);

    if (returnVal == 1) {
        std::cout << "\n学　　号\t姓　　名\tC语 言\t\t数据结构\t数 据 库\t总成绩\t\t平均成绩\n" << std::endl;
        std::cout << stu.id << "\t" << stu.name << "\t\t" << stu.Clanguage << "\t\t" << stu.DataStruct << "\t\t" << stu.DB << "\t\t" << stu.TotalScore << "\t\t" << stu.AverScore << "\n" << std::endl;
    } else if (returnVal == 0) {
        std::cout << "\n\t\t\t\t\t　 您查询的学生信息不存在\n" << std::endl;
    } else if (returnVal == -1) {
        std::cout << "\n\t\t\t\t\t　 数据库连接失败\n" << std::endl;
    } else {
        std::cout << "\n\t\t\t\t\t　 SQL语句执行失败\n" << std::endl;
    }
    
    std::cout << "\n按回车键继续。。。";
    setbuf(stdin, nullptr);
    getchar();
}

void QueryAllInfo(bool flag)
{
    Student tmp;
    std::vector<Student> stus;
    
    int returnVal;
    if (flag) {
        returnVal = tmp.ShowAllInfo(stus);
    } else {
        returnVal = tmp.ShowSortScore(stus);
    }

    if (returnVal == 1) {
        std::cout << "\n学　　号\t姓　　名\tC语 言\t\t数据结构\t数 据 库\t总成绩\t\t平均成绩\n" << std::endl;
        for (auto &stu : stus) {
            std::cout << stu.id << "\t" << stu.name << "\t\t" << stu.Clanguage << "\t\t" << stu.DataStruct << "\t\t" << stu.DB << "\t\t" << stu.TotalScore << "\t\t" << stu.AverScore << "\n" << std::endl;
        }
    } else if(returnVal == 0) {
        std::cout << "\n\t\t\t\t\t　 无记录\n" << std::endl;
    } else if (returnVal == -1) {
        std::cout << "\n\t\t\t\t\t　 数据库连接失败\n" << std::endl;
    } else if (returnVal == -2) {
        std::cout << "\n\t\t\t\t\t　 SQL语句执行失败\n" << std::endl;
    }
    std::cout << "\n按回车键继续。。。";
    setbuf(stdin, nullptr);
    getchar();
}

int main(int argc, char *argv[])
{
    int type = -1;

    while (true) {
        MainMenu();
        std::cin >> type;
        if (type == 0) {
            break;
        } else if (type == 1) {
            AddStudent();
        } else if (type == 2) {
            delStuInfo();
        } else if(type == 3) {
            ModStuInfo();
        } else if (type == 4) {
            QueryMenu();
            std::cin >> type;
            if (type == 1) {
                QueryStuInfo();
            } else if (type == 2) {
                QueryAllInfo(true);
            } else if (type == 3) {
                QueryAllInfo(false);
            } else if (type == 9) {
                continue;
            } else if (type == 0) {
                break;
            } else {
                std::cout << "您的输入有误,按回车键继续。。。" << std::endl;
                setbuf(stdin, nullptr);
                getchar();
            }
        } else {
            std::cout << "您的输入有误,按回车键继续。。。" << std::endl;
            setbuf(stdin, nullptr);
            getchar();
        }
    }

    return EXIT_SUCCESS;
}
