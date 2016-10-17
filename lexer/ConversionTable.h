//
// Created by zhanggen on 16-10-14.
//

#ifndef LEXER_CONVERSIONTABLE_H
#define LEXER_CONVERSIONTABLE_H

#include "Conversion.h"
#include "StatusTable.h"

class ConversionTable {

private:
    //通过输入的字符建立索引，后续需要输入某字符得到转换后的状态时就可以节省时间
    std::multimap<char, Conversion> conversionTable;

    //状态表
    StatusTable statusTable;

public:

    void init(const StatusTable &statusTable1) {
        statusTable = statusTable1;
    }

    void addConversion(const char &ch, const Conversion &conversion) {
        conversionTable.insert({ch, conversion});
    }

    //根据现在状态和输入字符获取下一个状态
    Status getNextStatus(const Status &nowStatus, const char &ch);
};

#endif //LEXER_CONVERSIONTABLE_H
