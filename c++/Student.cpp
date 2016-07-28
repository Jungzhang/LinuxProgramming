/*************************************************************************
	> File Name: Student.cpp
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月06日 星期一 00时18分10秒
	> Description:
 ************************************************************************/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Student.h"
#include "myDB.h"

Student::Student(const std::string id, const std::string name, const int Clanguage, const int DataStruct, const int DB)
                : id(id), name(name), Clanguage(Clanguage), DataStruct(DataStruct), DB(DB)
{
    
}

//成功返回1,信息有误返回0,数据库连接失败返回-1,SQL语句执行失败返回-2
int Student::AddStuInfo(Student stu)
{

    if (stu.Clanguage >= 0 && stu.DataStruct >= 0 && stu.DB >= 0 && id.size() == 8) {
        
        stu.TotalScore = stu.Clanguage + stu.DataStruct + stu.DB;
        stu.AverScore = stu.TotalScore / 3.0;
        myDB stuDB;
        
        if (stuDB.connectDB("127.0.0.1", "root", "", "Student", 3306, 0)) {
            std::string sql = "";
            sql = sql + "INSERT INTO Info(id, name, Clanguage, DataStruct, DB, TotalScore, AverScore)"+ " VALUES ('" 
                + stu.id + "','" + stu.name + "'," + std::to_string(stu.Clanguage) + "," + std::to_string(stu.DataStruct)
                + "," + std::to_string(stu.DB) + "," + std::to_string(stu.TotalScore) + "," + std::to_string(stu.AverScore) + ")";
            if (stuDB.useSqlModify(sql)) {
                return 1;
            } else {
                return -2;
            }
        } else {
            return -1;
        }
    } else {
        return 0;
    }
}

//成功返回1,记录不存在返回0,数据库连接失败返回-1,SQL语句执行失败返回-2
int Student::DelStuInfo(const std::string id)
{
    myDB stuDB;
    if (stuDB.connectDB("127.0.0.1", "root", "", "Student", 3306, 0)) {
        std::string sql = "";
        sql = sql + "SELECT * FROM Info WHERE id = '" + id + "'";
        if (stuDB.useSqlQuery(sql)) {
            if (!stuDB.getNumRows()) {
                return 0;
            }
            sql = "";
            sql = sql + "DELETE FROM Info WHERE id = '" + id + "'";
            if (stuDB.useSqlModify(sql)) {
                return 1;
            } else {
                return -2;
            }
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

//成功返回1,记录不存在返回-3,数据库连接失败返回-1,SQL语句执行失败返回-2,信息有误返回0
int Student::ModStuInfo(const std::string id, Student stu)
{
    if (stu.Clanguage >= 0 && stu.DataStruct >= 0 && stu.DB >= 0 && id.size() == 8) {
        myDB stuDB;
        std::string sql = "";
        sql = sql + "SELECT * FROM Info WHERE id = '" + id + "'";
        if (stuDB.connectDB("127.0.0.1", "root", "", "Student", 3306, 0)) {
            if (stuDB.useSqlQuery(sql)) {
                if (!stuDB.getNumRows()) {
                    return -3;
                }
            }
            stu.TotalScore = stu.Clanguage + stu.DataStruct + stu.DB;
            stu.AverScore = stu.TotalScore / 3.0;
            sql = "";
            sql = sql + "UPDATE Info SET id = '" + stu.id + "', name = '" + stu.name + "', Clanguage = " +
                std::to_string(stu.Clanguage) + ", DataStruct = " + std::to_string(stu.DataStruct) + ", DB = " + 
                std::to_string(stu.DB) + ", TotalScore = " + std::to_string(stu.TotalScore) + ", AverScore = " + std::to_string(stu.AverScore)
                + " WHERE id = '" + id + "'";
            if (stuDB.useSqlModify(sql)) {
                return 1;
            } else {
                return -2;
            }
        } else {
            return -1;
        }
    } else {
        return 0;
    }
}

//成功返回1,记录不存在返回0,数据库连接失败返回-1,SQL语句执行失败返回-2
int Student::ShowStuInfo(const std::string id, Student &stu)
{
    myDB stuDB;
    if (stuDB.connectDB("127.0.0.1", "root", "", "Student", 3306, 0)) {
        std::string sql = "";
        sql = sql + "SELECT * FROM Info WHERE id = '" + id + "'";
        if (stuDB.useSqlQuery(sql)) {
            if (!stuDB.getNumRows()) {
                return 0;
            } else {
                while (stuDB.loadRowResult() != 0) {
                    stu.id = std::string(stuDB.row[0]);
                    stu.name = std::string(stuDB.row[1]);
                    stu.Clanguage = atoi(stuDB.row[2]);
                    stu.DataStruct = atoi(stuDB.row[3]);
                    stu.DB = atoi(stuDB.row[4]);
                    stu.TotalScore = atoi(stuDB.row[5]);
                    stu.AverScore = atof(stuDB.row[6]);
                }
                return 1;
            }
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

//成功返回1,记录不存在返回0,数据库连接失败返回-1,SQL语句执行失败返回-2
int Student::ShowAllInfo(std::vector<Student> &result)
{
    result.clear();
    myDB stuDB;
    if (stuDB.connectDB("127.0.0.1", "root", "", "Student", 3306, 0)) {
        std::string sql = "";
        sql = sql + "SELECT * FROM Info";
        if (stuDB.useSqlQuery(sql)) {
            if (!stuDB.getNumRows()) {
                return 0;
            } else {
                while (stuDB.loadRowResult()) {
                    Student stu;
                    stu.id = stuDB.row[0];
                    stu.name = stuDB.row[1];
                    stu.Clanguage = atoi(stuDB.row[2]);
                    stu.DataStruct = atoi(stuDB.row[3]);
                    stu.DB = atoi(stuDB.row[4]);
                    stu.TotalScore = atoi(stuDB.row[5]);
                    stu.AverScore = atof(stuDB.row[6]);
                    result.push_back(stu);
                }
                return 1;
            }
        } else {
            return -2;
        }
    } else {
        return -1;
    }
    
}

//成功返回1,记录不存在返回0,数据库连接失败返回-1,SQL语句执行失败返回-2
int Student::ShowSortScore(std::vector<Student> &result)
{
    int returnVal;
    returnVal = ShowAllInfo(result);
    if (returnVal == 1) {
        std::sort(result.begin(), result.end(), [](const Student &a, const Student &b){return a.TotalScore > b.TotalScore;});
        return 1;
    } else {
        return returnVal;
    }
}
