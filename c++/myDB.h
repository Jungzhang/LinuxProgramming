/*************************************************************************
	> File Name: myDB.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年06月03日 星期五 15时24分24秒
	> Description:
 ************************************************************************/
#ifndef _MYDB_H
#define _MYDB_H
#include <mysql/mysql.h>

class myDB {
public :
    
    myDB();    //构造函数
    //myDB()=default;
    ~myDB();   //析构函数
    
    //连接数据库(无unix_socket参数),成功返回true,失败返回false
    bool connectDB(const std::string host, const std::string user, const std::string passwd, const std::string db, const unsigned int port, const unsigned int flag);
    //连接数据库,成功返回true,失败返回false
    bool connectDB(const std::string host, const std::string user, const std::string passwd, const std::string db, const unsigned int port, const std::string unix_socket, const unsigned int flag);
    bool useSqlQuery(const std::string sql); //使用SQL语句查询数据库
    bool useSqlModify(const std::string sql); //使用SQL语句操作数据库
    int loadRowResult(); //逐行输出获取到的信息
    unsigned int getNumRows(); //获取结果集中有多少行数据
    unsigned int getNumFields(); //获取结果集中有多少个字段

public :
    MYSQL_ROW row;

private :
    MYSQL *client = nullptr;
    MYSQL_RES *resource = nullptr;
};

#endif
