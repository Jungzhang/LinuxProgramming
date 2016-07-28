CREATE DATABASE Student;

USE Student;

CREATE TABLE Info
(
    id CHAR(8) NOT NULL,
    name CHAR(50) NOT NULL,
    CLanguage INT DEFAULT 0,
    DataStruct INT DEFAULT 0,
    DB INT DEFAULT 0,
    TotalScore INT DEFAULT 0,
    AverScore double DEFAULT 0,
    PRIMARY KEY(id)
);
