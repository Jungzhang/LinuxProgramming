#include <iostream>
#include "Analysis.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "参数错误" << std::endl;
        std::cerr << argv[0] << " " << "文件名" << std::endl;
        return 1;
    }

    Analysis analysis;
    analysis.runAnalysis(argv[1]);

    return 0;
}