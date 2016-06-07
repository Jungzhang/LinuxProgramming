/*************************************************************************
	> File Name: myDB.cpp
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月04日 星期六 19时19分14秒
	> Description:
 ************************************************************************/
#include <iostream>
#include <cstdlib>
#include "myDB.h"
#include <mysql/mysql.h>

//构造函数
myDB::myDB()
{
    if ((client = mysql_init(nullptr)) == nullptr) {
        std::cerr << "The database init failed." << std::endl;
    }
}

//析构函数
myDB::~myDB()
{
    if (resource) {
        mysql_free_result(resource);
        resource = nullptr;
    }

    if (client) {
        mysql_close(client);
    }
}

//连接函数
bool myDB::connectDB(const std::string host, const std::string user, const std::string passwd, 
                const std::string db, const unsigned int port, const std::string unix_socket, const unsigned int flag)
{
    if (!mysql_real_connect(client, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, unix_socket.c_str(), flag)) {
        std::cerr << "The database connect failed:" << mysql_error(client) << std::endl;
        return false;
    }

    return true;
}

bool myDB::connectDB(const std::string host, const std::string user, const std::string passwd, 
                const std::string db, const unsigned int port, const unsigned int flag)
{
    if (!mysql_real_connect(client, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, flag)) {
        std::cerr << "The database connect failed:" << mysql_error(client) << std::endl;
        return false;
    }

    return true;
}

//使用SQL语句查询数据库
bool myDB::useSqlQuery(const std::string sql)
{
    if (resource != nullptr) {
        mysql_free_result(resource);
        resource = nullptr;
    }

    if (mysql_real_query(client, sql.c_str(), sql.size())) {
        std::cerr << "query failed:" << mysql_error(client) << std::endl;
        return false;
    }

    if ((resource = mysql_store_result(client)) == nullptr) {
        std::cerr << "store failed:" << mysql_error(client) << std::endl;
        return false;
    }

    return true;
}

//使用SQL增删改数据库的值
bool myDB::useSqlModify(const std::string sql)
{
    if (mysql_real_query(client, sql.c_str(), sql.size())) {
        std::cerr << "modify failed:" << mysql_error(client) << std::endl;
        return false;
    }

    return true;
}

//逐行读取获取到的信息
int myDB::loadRowResult()
{
    if (resource) {
        row = mysql_fetch_row(resource);
        return 1;
    } else {
        return 0;
    }
}

//获取结果集中有多少行数据
unsigned int myDB::getNumRows()
{
    if (resource != nullptr) {
        return mysql_num_rows(resource);
    }

    return 0;
}

//获取结果集中有多少个字段
unsigned int myDB::getNumFields()
{
    if (resource != nullptr) {
        return mysql_num_fields(resource);
    }

    return 0;
}
