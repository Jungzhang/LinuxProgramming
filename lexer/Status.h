//
// Created by zhanggen on 16-10-13.
// 状态类
//

#ifndef LEXER_STATUS_H
#define LEXER_STATUS_H

#include <string>

class Status {
private:
    std::string sta_name = "none";  //状态名字
    bool endStatus = false;         //是否为终态

public:

    Status() = default;
    Status(const std::string &sta_name, const bool &endStatus)
            : sta_name(sta_name), endStatus(endStatus) {};
    std::string getName()const { return sta_name;}   //获取状态名字
    bool isEndStatus(){ return endStatus;}      //是否为终态
    bool operator==(const Status &name) const {
        return this->sta_name == name.sta_name;
    }
};

#endif //LEXER_STATUS_H
