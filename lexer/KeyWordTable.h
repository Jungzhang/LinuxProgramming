//
// Created by zhanggen on 16-10-14.
//

#ifndef LEXER_KEYWORDTABLE_H
#define LEXER_KEYWORDTABLE_H

#include <set>
#include <string>

class KeyWordTable {

private:
    std::set<std::string> keyWords;
public:

    void addKeyWord(const std::string &word) {keyWords.insert(word);}
    bool isExist(const std::string &word) { return !(keyWords.find(word) == keyWords.end());}

};

#endif //LEXER_KEYWORDTABLE_H
