//
// Created by zhanggen on 16-10-14.
// DFA类实现
//

#include "DFA.h"

//初始化字符表
void DFA::initCharacterTable() {
    //算数运算符
    characterTable.addCharacter('+');
    characterTable.addCharacter('-');
    characterTable.addCharacter('*');
    characterTable.addCharacter('/');

    //逻辑运算符
    characterTable.addCharacter('=');
    characterTable.addCharacter('!');
    characterTable.addCharacter('>');
    characterTable.addCharacter('<');

    //界符
    characterTable.addCharacter(';');
    characterTable.addCharacter(' ');
    characterTable.addCharacter(',');
    characterTable.addCharacter('(');
    characterTable.addCharacter(')');
    characterTable.addCharacter('{');
    characterTable.addCharacter('}');
    characterTable.addCharacter('.');

    //字母
    for (char i = 'a'; i <= 'z'; ++i) {
        characterTable.addCharacter(i);
    }

    for (char j = 'A'; j <= 'Z'; ++j) {
        characterTable.addCharacter(j);
    }

    //数字
    for (char k = '0'; k <= '9'; ++k) {
        characterTable.addCharacter(k);
    }
}

//初始化状态表
void DFA::initStatusTable() {
    statusTable.addStatus({"NUM_1_9", true});       //状态I，数字1-9，对0进行特殊处理
    statusTable.addStatus({"NUM_0", true});         //状态H，数字0的状态
    statusTable.addStatus({"LETTER", true});        //状态T，字母的状态
    statusTable.addStatus({"DELIMITER", true});     //状态J，分隔符状态
    statusTable.addStatus({"OPERATOR_A", true});    //状态A，当输入符号/时
    statusTable.addStatus({"OPERATOR_F", false});   //状态F，当输入!时
    statusTable.addStatus({"OPERATOR_B", true});    //状态B，当输入< > =符号时
    statusTable.addStatus({"OPERATOR_G", true});    //状态G，算数运算符和判相等、不等
    statusTable.addStatus({"ANNOTATOR_C", false});  //状态C，A状态时输入*(多行注释)
    statusTable.addStatus({"ANNOTATOR_D", false});   //状态D，C状态时输入*
    statusTable.addStatus({"ANNOTATOR_E", true});    //状态E，D状态输入/结束注释
    statusTable.addStatus({"SPACE", true});         //空格
}

//初始化关键字表
void DFA::initKeyWordTable() {
    keyWordTable.addKeyWord("auto");
    keyWordTable.addKeyWord("short");
    keyWordTable.addKeyWord("long");
    keyWordTable.addKeyWord("struct");
    keyWordTable.addKeyWord("union");
    keyWordTable.addKeyWord("enum");
    keyWordTable.addKeyWord("typedef");
    keyWordTable.addKeyWord("const");
    keyWordTable.addKeyWord("unsigned");
    keyWordTable.addKeyWord("signed");
    keyWordTable.addKeyWord("extern");
    keyWordTable.addKeyWord("register");
    keyWordTable.addKeyWord("static");
    keyWordTable.addKeyWord("volatile");
    keyWordTable.addKeyWord("void");
    keyWordTable.addKeyWord("if");
    keyWordTable.addKeyWord("else");
    keyWordTable.addKeyWord("switch");
    keyWordTable.addKeyWord("case");
    keyWordTable.addKeyWord("for");
    keyWordTable.addKeyWord("do");
    keyWordTable.addKeyWord("while");
    keyWordTable.addKeyWord("goto");
    keyWordTable.addKeyWord("continue");
    keyWordTable.addKeyWord("break");
    keyWordTable.addKeyWord("default");
    keyWordTable.addKeyWord("sizeof");
    keyWordTable.addKeyWord("return");
    keyWordTable.addKeyWord("int");
    keyWordTable.addKeyWord("float");
    keyWordTable.addKeyWord("double");
    keyWordTable.addKeyWord("char");
}

//构建状态转换表
void DFA::initConversionTable() {

    //从Start状态输入1-9即可进入NUM_1_9状态
    for (char i = '1'; i <= '9'; ++i) {
        Conversion temp(statusTable.getStatus("Start"), statusTable.getStatus("NUM_1_9"), i);
        conversionTable.addConversion(i, temp);
    }

    //从NUM_1_9状态输入1-9即可进入NUM_1_9状态
    for (char j = '0'; j <= '9'; ++j) {
        Conversion temp(statusTable.getStatus("NUM_1_9"), statusTable.getStatus("NUM_1_9"), j);
        conversionTable.addConversion(j, temp);
    }

    //从Start状态输入0可进入NUM_0状态
    conversionTable.addConversion('0', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("NUM_0"), '0'));

    //从Start状态输入a-z、A-Z可进入LETTER状态
    for (char k = 'a'; k <= 'z'; ++k) {
        Conversion temp(statusTable.getStatus("Start"), statusTable.getStatus("LETTER"), k);
        conversionTable.addConversion(k, temp);
    }

    for (char l = 'A'; l <= 'Z'; ++l) {
        Conversion temp(statusTable.getStatus("Start"), statusTable.getStatus("LETTER"), l);
        conversionTable.addConversion(l, temp);
    }

    //从LETTER状态输入a-z、A-Z、0-9可进入LETTER状态
    for (char m = '0'; m <= '9'; ++m) {
        Conversion temp(statusTable.getStatus("LETTER"), statusTable.getStatus("LETTER"), m);
        conversionTable.addConversion(m, temp);
    }

    for (char n = 'a'; n <= 'z'; ++n) {
        Conversion temp(statusTable.getStatus("LETTER"), statusTable.getStatus("LETTER"), n);
        conversionTable.addConversion(n, temp);
    }

    for (char i1 = 'A'; i1 < 'Z'; ++i1) {
        Conversion temp(statusTable.getStatus("LETTER"), statusTable.getStatus("LETTER"), i1);
        conversionTable.addConversion(i1, temp);
    }

    conversionTable.addConversion(' ', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("SPACE"), ' '));

    conversionTable.addConversion(' ', Conversion(statusTable.getStatus("SPACE"),
                                                  statusTable.getStatus("SPACE"), ' '));

    conversionTable.addConversion('(', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), '('));

    conversionTable.addConversion(')', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), ')'));

    conversionTable.addConversion(';', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), ';'));

    conversionTable.addConversion(',', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), ','));

    conversionTable.addConversion('.', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), '.'));

    conversionTable.addConversion('"', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), '"'));

    conversionTable.addConversion('{', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), '{'));

    conversionTable.addConversion('}', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("DELIMITER"), '}'));

    conversionTable.addConversion('!', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_F"), '!'));

    conversionTable.addConversion('=', Conversion(statusTable.getStatus("OPERATOR_F"),
                                                  statusTable.getStatus("OPERATOR_G"), '='));

    conversionTable.addConversion('+', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_G"), '+'));

    conversionTable.addConversion('-', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_G"), '-'));

    conversionTable.addConversion('*', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_G"), '*'));

    conversionTable.addConversion('>', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_B"), '>'));

    conversionTable.addConversion('<', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_B"), '<'));

    conversionTable.addConversion('=', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_B"), '='));

    conversionTable.addConversion('=', Conversion(statusTable.getStatus("OPERATOR_B"),
                                                  statusTable.getStatus("OPERATOR_G"), '='));

    conversionTable.addConversion('/', Conversion(statusTable.getStatus("Start"),
                                                  statusTable.getStatus("OPERATOR_A"), '/'));

    conversionTable.addConversion('*', Conversion(statusTable.getStatus("OPERATOR_A"),
                                                  statusTable.getStatus("ANNOTATOR_C"), '*'));

    conversionTable.addConversion('*', Conversion(statusTable.getStatus("ANNOTATOR_C"),
                                                  statusTable.getStatus("ANNOTATOR_D"), '*'));

    conversionTable.addConversion('*', Conversion(statusTable.getStatus("ANNOTATOR_D"),
                                                  statusTable.getStatus("ANNOTATOR_D"), '*'));

    conversionTable.addConversion('/', Conversion(statusTable.getStatus("ANNOTATOR_D"),
                                                  statusTable.getStatus("ANNOTATOR_E"), '/'));

    //注释部分
    for (unsigned char j1 = 0; j1 < 255; ++j1) {
        if (j1 != '*') {
            Conversion temp(statusTable.getStatus("ANNOTATOR_C"), statusTable.getStatus("ANNOTATOR_C"), j1);
            conversionTable.addConversion(j1, temp);
        }
    }

    //注释中*后还有东西则要将状态从ANNOTATOR_D转回ANNOTATOR_C状态
    for (unsigned char K1 = 0; K1 < 255; ++K1) {
        if (K1 != '/') {
            Conversion temp(statusTable.getStatus("ANNOTATOR_D"), statusTable.getStatus("ANNOTATOR_C"), K1);
            conversionTable.addConversion(K1, temp);
        }
    }
}
