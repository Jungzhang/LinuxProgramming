//
// Created by zhanggen on 16-10-15.
//

#include "Analysis.h"

std::string Analysis::getResult(const std::string &word, const Status &status) {
    std::string name = status.getName();

    if (name == "NUM_1_9" || name == "NUM_0") {
        return "数字";
    } else if (name == "LETTER") {
        if (dfa.isKeyWord(word)) {
            return "关键字";
        } else {
            return "标识符";
        }
    } else if (name == "DELIMITER") {
        return "分隔符";
    } else if (name == "OPERATOR_A") {
        return "算数运算符";
    } else if (name == "OPERATOR_G") {
        if (word == "+" || word == "-" || word == "*") {
            return "算数运算符";
        } else {
            return "逻辑运算符";
        }
    } else if (name == "OPERATOR_B") {
        if (word == "=") {
            return "算数运算符";
        } else {
            return "逻辑运算符";
        }
    } else if (name == "ANNOTATOR_E") {
        return "注释";
    } else if (name == "SPACE") {
        return "空格";
    }
}

void Analysis::runAnalysis(const std::string &fileName) {

    if (!openFile(fileName, fileName + ".result")) {
        std::cerr << "文件打开失败" << std::endl;
        exit(1);
    }

    std::string strLine = "";        //从文件读出一行数据
    std::string strRest = "";

    // 因为编程方便（用-1表示初始状态所以此处未使用std::string::size_type）
    long preOutStrEndPos;       //上一个输出的字符串的尾字符位置
    long preEndStatusPos;       //上一个被识别到的终结符的字符位置

    preEndStatusPos = -1;
    preOutStrEndPos = -1;

    Status nowStatus;
    Status preEndSatus;             //上一个终结状态
    bool isFindEndStatus = false;   //是否找到终结符
    auto i = strRest.length();

    while (!inputFile.eof()) {
        ++line;
        getline(inputFile, strLine);
        strLine = strRest + strLine;

        //循环解析
        loopAnalysis(strRest, strLine, nowStatus, preEndSatus, isFindEndStatus, preEndStatusPos,preOutStrEndPos);

        //有可能会出现一行写不完的代码换行后继续写，所以此处要将未处理完的字符继续留到读取完下一行后继续处理
        strRest = std::string(strLine, preOutStrEndPos + 1, strLine.length());
        preEndStatusPos = preEndStatusPos  - (preOutStrEndPos + 1);
        preOutStrEndPos = -1;
    }

    //循环解析可能到文件末尾但是还有缓存区中未解析完的字符
//    loopAnalysis(strRest, strLine, nowStatus, preEndSatus, isFindEndStatus, preEndStatusPos,preOutStrEndPos);

    closeFile();
}

void Analysis::loopAnalysis(std::string &strRest, std::string &strLine, Status &nowStatus, Status &preEndSatus,
                            bool &isFindEndStatus, long &preEndStatusPos, long &preOutStrEndPos) {
    for (auto i = strRest.length(); i < strLine.length(); ++i) {
        nowStatus = dfa.getStatusByCharacter(strLine[i]);   //当输入当前扫描到的字符后的状态

        if (nowStatus.isEndStatus()) {
            preEndSatus = nowStatus;    //上一次出现终态的状态
            isFindEndStatus = true;     //找到终态
            preEndStatusPos = i;       //上一次出现终结符的索引
        }

        if (nowStatus.getName() == "Error") {
            if (isFindEndStatus) {
                std::string word = std::string(strLine, preOutStrEndPos + 1, preEndStatusPos - preOutStrEndPos);
                std::string result = getResult(word, preEndSatus);
                addSuccessMessige(word, result);
                isFindEndStatus = false; //置位
                i = preEndStatusPos;  //从缓存区归还
                preOutStrEndPos = i;
            } else {
                std::string word = std::string(strLine, preOutStrEndPos + 1, i - preOutStrEndPos);
                std::cout << "未知 : " << (int)word[0] << std::endl;
                if (!dfa.isExistWord(strLine[i])) {
                    addErrorMessige(line, word, "含有未知字符");
                    preOutStrEndPos = preEndStatusPos = i;
                } else {
                    addErrorMessige(line, word, "未知错误");
                    --i;    //归还
                    preEndStatusPos = preOutStrEndPos = i;
                }
            }
            dfa.restart();      //重新开始
        }
    }
}