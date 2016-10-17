//
// Created by zhanggen on 16-10-14.
// 构建DFA
//

#ifndef LEXER_DFA_H
#define LEXER_DFA_H

#include "StatusTable.h"
#include "CharacterTable.h"
#include "ConversionTable.h"
#include "KeyWordTable.h"

class DFA {

private:

    StatusTable statusTable;        //状态表
    CharacterTable characterTable;  //字母表
    KeyWordTable keyWordTable;      //关键字表
    Status nowStatus = statusTable.getStatus("Start");           //当前状态

    ConversionTable conversionTable;


private:
    //初始化状态表
    void initStatusTable();

    //初始化字母表
    void initCharacterTable();

    //初始化关键字表
    void initKeyWordTable();

    //初始化状态转换表
    void initConversionTable();

public:

    DFA() {
        initCharacterTable();
        initKeyWordTable();
        initStatusTable();
        conversionTable.init(statusTable);
        initConversionTable();
    }

    //根据字符获取输入该字符后的状态
    Status getStatusByCharacter(const char &ch) {
        return nowStatus = conversionTable.getNextStatus(nowStatus, ch);
    }

    bool isKeyWord(const std::string &word) {
        return keyWordTable.isExist(word);
    }

    bool isExistWord(const char &word) {
        return characterTable.isExist(word);
    }

    Status restart() {
        return nowStatus = statusTable.getStatus("Start");
    }
};

#endif //LEXER_DFA_H
