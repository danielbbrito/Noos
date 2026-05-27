#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#define BUFFER_SIZE 1024

enum TokenType {
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
    NOT,
    QUOTE, 

    LPAR,
    RPAR,
    COMMA,
    LBRACE,
    RBRACE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

int check_char(char c)
{
    // Returns the index of the character type on the transition table
    if (std::isalpha(c))
        return 0;

    if (std::isdigit(c))
        return 1;

    if (c == '_')
        return 2;
    return 3;
}

Token init_token(TokenType type, std::string lexeme, int line, int column)
{
    Token token;
    token.type = type;
    token.lexeme = lexeme;
    token.line = line;
    token.column = column;

    return token;
}

int main()
{

    std::map<std::string, TokenType> keywords = {
        {"codex", CODEX},
        {"ritus", RITUS},
        {"cycle", CYCLE},
        {"verify", IF},
        {"fallback", ELSE},
        {"initiate", INITIATE},
        {"terminate", TERMINATE},
        {"transmit", RETURN},
        {"numerus", TYPE_INT},
        {"flux", TYPE_FLOAT},
        {"veritas", TYPE_BOOLEAN},
        {"scriptum", TYPE_STRING},
        {"verum", TRUE},
        {"falsum", FALSE},
        {"vox", PRINT}
    };

    std::map<std::string, TokenType> symbols_and_ops = {
        {"=", ASSIGN},
        {"+", PLUS},
        {"-", MINUS},
        {"*", MULT},
        {"/", DIV},
        {"==", EQ},
        {"!=", NEQ},
        {">", GT},
        {"<", LT},
        {">=", GTE},
        {"<=", LTE},
        {"(", LPAR},
        {")", RPAR},
        {"[", LBRACE},
        {"]", RBRACE},
        {",", COMMA},
        {"!", NOT},
        {"\"", QUOTE}
    };

    // States for the automaton that recognizes identifiers
    std::map<int, std::vector<int>> states = {
        {0, {1, 2, 2, 2}},
        {1, {1, 1, 1, 2}},
        {2, {2, 2, 2, 2}}
    };

    // Input file stream (change later)
    std::fstream noo_program("example.noo", std::ios::in);

    // Character buffer
    char buffer[BUFFER_SIZE];

    std::vector<Token> tokens;

    int line = 0, column = 0;

    // Helper variables for string scanning
    bool scanning_string = false;
    std::string literal;

    if (!noo_program.is_open())
    {
        throw std::runtime_error("[ERROR::LEX] :: MACHINE_SPIRIT_FRACTURED\n\nSIGNAL :: FILE COULD NOT BE OPENED\n\nRECOVERY :: ENSURE CORRECT NAMING RITUALS");
    }


    while (noo_program.read(&buffer[0], BUFFER_SIZE) || noo_program.gcount() > 0)
    {
        int bytes_read = noo_program.gcount();
        int state = 0;
        
        std::string lexeme = "";

        
        for (int i = 0; i < bytes_read; i++)
        {  
            // If a string is not completed in the previous chunk, keep scanning
            if (scanning_string)
            {
                while (i < bytes_read)
                {
                    if (buffer[i] == '"')
                    {
                        scanning_string = false;
                        tokens.push_back(init_token(STRING, literal, line, column));
                        tokens.push_back(init_token(symbols_and_ops[std::string(1, buffer[i])], "\"", line, column));
                        break;
                    }
                    else
                    {
                        literal += buffer[i];
                    }

                    i++;
                }

                continue;
            }
            if (buffer[i] == '\r')
                continue;

            int new_state = states[state][check_char(buffer[i])];
            
            if (new_state == 2)
            {
                if (state == 1)
                {
                    // Check if it's a keyword
                    if (keywords.find(lexeme) != keywords.end())
                        tokens.push_back(init_token(keywords[lexeme], lexeme, line, column));
                    
                    // If not then it must be an identifier
                    else
                        tokens.push_back(init_token(IDENTIFIER, lexeme, line, column));
                    
                    i--;
                    lexeme = "";
                }
                else if (state == 0 && buffer[i] != '\n' && buffer[i] != ' ')
                {
                    // Check if next char is =, making sure we don't go out of bounds
                    if (i + 1 < bytes_read && buffer[i + 1] == '=')
                    {
                        if (buffer[i] == '<' || buffer[i] == '>' || buffer[i] == '!' || buffer[i] == '=')
                        {
                            std::string op = std::string(1, buffer[i]) + buffer[i + 1];
                            tokens.push_back(init_token(symbols_and_ops[op], op, line, column));
                            i++;
                        }
                        else if (buffer[i] != ' ') // Next token may be an assign or equal if it is blank
                        {
                            throw std::runtime_error(std::string("[ERROR::LEX] :: MACHINE_SPIRIT_DORMANT\n\nSIGNAL :: UNRECOGNIZED TOKEN") + buffer[i] + buffer[i + 1] + "\n\nRECOVERY :: ENSURE CORRECT RITES OF AWAKENING");
                        }
                    }
                    else if (buffer[i] == '"')
                    {
                        tokens.push_back(init_token(symbols_and_ops[std::string(1, buffer[i])], "\"", line, column));

                        literal = "";
                        i++;

                        // Might want to work on this
                        while (i < bytes_read - 1 && buffer[i] != '"')
                        {
                            literal += buffer[i];

                            if (buffer[i] == '\n')
                                line++;
                            else
                                column++;

                            i++; 
                        }

                        if (buffer[i] == '"')
                        {
                            tokens.push_back(init_token(STRING, literal, line, column));
                            tokens.push_back(init_token(symbols_and_ops[std::string(1, buffer[i])], "\"", line, column));
                        }
                        else
                        {
                            // Keep scanning if literal is not closed
                            scanning_string = true;
                        }
                    }
                    else
                    {
                        if (symbols_and_ops.find(std::string(1, buffer[i])) != symbols_and_ops.end())
                        {
                            tokens.push_back(init_token(symbols_and_ops[std::string(1, buffer[i])], std::string(1, buffer[i]), line, column));
                        }
                        else
                        {
                            std::cout << column << std::endl;
                            throw std::runtime_error(std::string("[ERROR::LEX] :: MACHINE_SPIRIT_DORMANT\n\nSIGNAL :: UNRECOGNIZED TOKEN ") + buffer[i]  + "\n\nRECOVERY :: ENSURE CORRECT RITES OF AWAKENING");
                        }
                    }

                    // Update positional info
                    column++;
                    
                } 
                else if (buffer[i] == '\n')
                {
                    line++;
                    column = 1;
                }

                // Restart the automaton
                state = 0;
    
            }

            else if (new_state == 1)
            {
                lexeme += buffer[i];
                state = new_state;
                column++;
            }
        }
    }

    // Unclosed literal
    if (scanning_string && noo_program.gcount() == 0)
    {
        throw std::runtime_error("[ERROR::LEX] :: MACHINE_SPIRIT_FRACTURED\n\nSIGNAL :: OPEN LITERAL\n\nRECOVERY :: ENSURE CORRECT SCRIPTUM FORMULATION");
    }
    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << "<" << tokens[i].type << "," << tokens[i].lexeme << "> ";
    }
    

    noo_program.close();
    return 0;
}