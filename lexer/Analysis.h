//
// Created by zhanggen on 16-10-15.
//

#ifndef LEXER_ANALYSIS_H
#define LEXER_ANALYSIS_H

#include <fstream>
#include <iostream>
#include "DFA.h"

class Analysis {

private:
    std::ifstream inputFile;
    std::ofstream outputFile;
    unsigned long line = 0;
    DFA dfa;

private:
    bool openFile(const std::string &input, const std::string &output) {
        inputFile.open(input);
        outputFile.open(output);

        return inputFile.is_open() && outputFile.is_open();
    }

    void addSuccessMessige(const std::string &word, const std::string &result) {
        outputFile << "(" << word << "," << result << ")\n";
    }

    void addErrorMessige(const int &line, const std::string &word, const std::string &result) {
        std::cerr << "第" << line << "行：" << "(" << word << "," << result << ")\n";
    }

    void closeFile() {
        inputFile.close();
        outputFile.close();
    }

    std::string getResult(const std::string &word, const Status &status);
    void loopAnalysis(std::string &strRest, std::string &strLine, Status &nowStatus, Status &preEndSatus,
                      bool &isFindEndStatus, long &preEndStatusPos, long &preOutStrEndPos);

public:
    void runAnalysis(const std::string &fileName);
};

#endif //LEXER_ANALYSIS_H
