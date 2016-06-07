/*************************************************************************
	> File Name: Student.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月05日 星期日 23时46分04秒
	> Description:
 ************************************************************************/
#ifndef _STUDENT_H
#define _STUDENT_H

#include <vector>

class Student {
public :
    Student() = default;
    int AddStuInfo(Student stu);
    int DelStuInfo(const std::string id);
    int ModStuInfo(const std::string id, const Student stu);
    int ShowStuInfo(const std::string id, Student &result);
    int ShowAllInfo(std::vector<Student> &result);
    int ShowSortScore(std::vector<Student> &result);
private:
    int Clanguage;
    int DataStruct;
    int DB;
    unsigned int TotalScore;
    unsigned double AverScore;
    std::string id;
    std::string name;
};

#endif
