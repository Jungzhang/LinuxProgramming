//
// Created by zhanggen on 16-10-13.
// 状态表
//

#ifndef LEXER_STATUSTABLE_H
#define LEXER_STATUSTABLE_H

#include <map>
#include <string>
#include "Status.h"

class StatusTable {
private:

    std::map<std::string, Status> statusTable;

public:

    //构造函数，默认添加开始状态和结束状态
    StatusTable() {
        statusTable.clear();
        statusTable.insert({"Start", {"Start", false}});
        statusTable.insert({"Error", {"Error", false}});
    }

    //添加状态
    void addStatus(const Status &status) { statusTable.insert({status.getName(), status}); }

    //通过状态名字获取状态
    Status getStatus(const std::string name) { return statusTable[name];}

};

#endif //LEXER_STATUSTABLE_H
