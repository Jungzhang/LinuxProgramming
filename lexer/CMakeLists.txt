cmake_minimum_required(VERSION 3.5)
project(lexer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CharacterTable.h Status.h StatusTable.h DFA.h ConversionTable.h DFA.cpp KeyWordTable.h Conversion.h Analysis.cpp Analysis.h ConversionTable.cpp)
add_executable(lexer ${SOURCE_FILES})
