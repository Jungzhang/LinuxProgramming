//
// Created by zhanggen on 16-10-15.
// 状态转换类
//

#ifndef LEXER_CONVERSION_H
#define LEXER_CONVERSION_H

#include "Status.h"

class Conversion {
private:
    Status nowStatus;           //目前的状态
    Status toStatus;            //下一个状态
    char inputCharacter; //输入的字符

public:
    Conversion(Status now, Status to, char input)
            : nowStatus(now), toStatus(to), inputCharacter(input) {}
    Status getNowStatus() { return nowStatus;}
    Status getToStatus() { return toStatus;}
};

#endif //LEXER_CONVERSION_H
