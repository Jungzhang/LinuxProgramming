//
// Created by zhanggen on 16-10-13.
// 字母表类,存储支持的字符
//

#ifndef LEXER_CHARACTERTABLE_H
#define LEXER_CHARACTERTABLE_H

#include <set>
#include <cstdio>

class CharacterTable {
private:

    std::set<char> characters;

public:

    //添加字符
    void addCharacter(const char &ch) {characters.insert(ch);}

    //判断某字母是否在字母表中
    bool isExist(const char &ch) { return !(characters.find(ch) == characters.end());}

};


#endif //LEXER_CHARACTERTABLE_H
