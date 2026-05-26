#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BUFFER_SIZE 1024

enum Tokens {
    IDENTIFIER,
    CODEX, // Start block
    RITUS, // Function declaration
    CYCLE, // While
    IF,
    ELSE,
    INITIATE,
    TERMINATE,
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

    LPAR,
    RPAR,
    COMMA,
    LBRACE,
    RBRACE
};

int main()
{
    std::fstream noo_program("example.noo", std::ios::in);
    char buffer[BUFFER_SIZE];
    int state = 0;

    if (!noo_program.is_open())
    {
        throw std::runtime_error("[ERROR::LEX] :: MACHINE_SPIRIT_FRACTURED\n\nSIGNAL :: FILE COULD NOT BE OPENED\n\nRECOVERY :: ENSURE CORRECT NAMING RITUALS");
    }


    while (noo_program.read(&buffer[0], BUFFER_SIZE) || noo_program.gcount() > 0)
    {
        int bytes_read = noo_program.gcount();
        int last_accepting_char, curr_char, state = 0;
        
        for (int i = 0; i < bytes_read; i++)
        {
            
        }
    }
    

    noo_program.close();
    return 0;
}