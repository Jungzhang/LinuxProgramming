/*************************************************************************
	> File Name: myDB.cpp
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月04日 星期六 19时10分05秒
	> Description:
 ************************************************************************/
#include <iostream>
#include <cstdlib>
#include "myDB.h"

int main(int argc, char *argv[])
{
    myDB db;
    if (db.connectDB("127.0.0.1", "root", "", "Student", 3306, 0) == false) {
        std::cout << "连接失败" <<std::endl;
    }

    return EXIT_SUCCESS;
}
