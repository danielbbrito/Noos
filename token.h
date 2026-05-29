#pragma once
#include <string>

enum TokenType {
    IDENTIFIER,
    CODEX,
    RITUS,
    CYCLE,
    IF,
    ELSE,
    INITIATE,
    END_CODEX,
    END_RITUS,
    END_IF,
    END_CYCLE,
    RETURN,
    TRUE,
    FALSE,
    INTEGER,
    FLOAT,
    STRING,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOLEAN,
    PRINT,
    ASSIGN,
    PLUS,
    MINUS,
    MULT,
    DIV,
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE,
    NOT,
    AND,
    OR,
    VOID,
    LPAR,
    RPAR,
    COMMA,
    LBRACE,
    RBRACE,
    LBRACK,
    RBRACK,
    NEWLINE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};
