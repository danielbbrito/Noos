#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include "token.h"
#include "lexer.h"

int check_char(char c)
{
    /* Returns the index of the character type on the transition table */
    if (std::isalpha(c))
        return 0;

    if (std::isdigit(c))
        return 1;

    if (c == '_')
        return 2;

    if (c == '.')
        return 3;

    return 4;
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

std::string remove_comments(const std::string& source)
{
    /*
        PT: Remove comentários
        EN: Removes comments
    */
    std::string result;
    size_t i = 0;
    while (i < source.size())
    {
        if (i + 1 < source.size() && source[i] == '-' && source[i + 1] == '-')
        {
            while (i < source.size() && source[i] != '\n')
                i++;
        }
        else
        {
            result += source[i++];
        }
    }
    return result;
}

std::string normalize_whitespace(const std::string& source)
{
    /*
        PT: Remove espaços em branco consecutivos e no início de linhas
        EN: Removes consecutive whitespaces and whitespace at the start of a line
    */

    std::string result;
    bool in_space = false;
    for (int i = 0; i < (int)source.length(); i++)
    {
        if (source[i] == ' ' || source[i] == '\t')
        {
            // PT: Não permitimos espaços consecutivos e nem em inicio de linhas
            // EN: We allow neither consecutive whitespaces nor whitespace at the start of a line 
            if (i > 0 && !in_space && source[i - 1] != '\n')
            {
                result += ' ';
                in_space = true;
            }
        }
        else
        {
            in_space = false;
            result += source[i];
        }
    }
    return result;
}

std::vector<Token> scan_source(std::string file_path, bool debug)
{
    /*
        PT: Lógica principal do scanner
        EN: The scanner's main lógic
    */

    std::map<std::string, TokenType> keywords = {
        {"codex", CODEX},
        {"ritus", RITUS},
        {"cycle", CYCLE},
        {"verify", IF},
        {"fallback", ELSE},
        {"initiate", INITIATE},
        {"transmit", RETURN},
        {"numerus", TYPE_INT},
        {"flux", TYPE_FLOAT},
        {"veritas", TYPE_BOOLEAN},
        {"scriptum", TYPE_STRING},
        {"verum", TRUE},
        {"falsum", FALSE},
        {"vox", PRINT},
        {"codexterminate", END_CODEX},
        {"ritusterminate", END_RITUS},
        {"verifyterminate", END_IF},
        {"cycleterminate", END_CYCLE},
        {"conjunction", AND},
        {"divergence", OR},
        {"nullrite", VOID}
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
        {"[", LBRACK},
        {"]", RBRACK},
        {",", COMMA},
        {"!", NOT},
        {"{", LBRACE},
        {"}", RBRACE},
        {"\n", NEWLINE}
    };

    // PT: Transições para ao autômato que reconhece indentificadores, inteiros e reais
    // EN: Transitions for the automaton that recognizes identifiers, integers and floats
    std::map<int, std::vector<int>> transitions = {
        {0, {1, 3, 2, 2, 2}},
        {1, {1, 1, 1, 2, 2}}, // Accepts identifier candidates
        {2, {2, 2, 2, 2, 2}},
        {3, {2, 3, 2, 4, 2}}, // Accepts integers
        {4, {2, 5, 2, 2, 2}},
        {5, {2, 5, 2, 2, 2}}  // Acceps floating point numbers
    };

    // Input file stream
    std::fstream noo_program(file_path, std::ios::in);

    std::vector<Token> tokens;

    int line = 0, column = 0;

    // PT: Variável ajudante para escanear strings
    // EN: Helper variable for string scanning
    std::string literal;

    if (!noo_program.is_open())
    {
        throw std::runtime_error("[ERROR::LEX] :: MACHINE_SPIRIT_FRACTURED\n\nSIGNAL :: FILE COULD NOT BE OPENED\n\nRECOVERY :: ENSURE CORRECT NAMING RITUALS");
    }

    std::string file_content((std::istreambuf_iterator<char>(noo_program)), std::istreambuf_iterator<char>());

    // PT: Aqui ocorre o pré-processamento do fonte
    // EN: Source pre-processing
    file_content = remove_comments(file_content);
    file_content = normalize_whitespace(file_content);

    int bytes_read = (int)file_content.size();
    const char* buffer = file_content.data();

    int state = 0;

    std::string lexeme = "";

    
    for (int i = 0; i <= bytes_read; i++)
    {  
        if (buffer[i] == '\r') // PT: Compatibilidade com Windows EN: Compatibility with Windows files
            continue;

        int new_state = transitions[state][check_char(buffer[i])];
        
        if (new_state == 2)
        {
            if (state == 1)
            {
                // PT: Verifica palavra-chave e caso não seja aceita um identificador
                // EN: Check if it's a keyword and accepts an identifier it it's not
                if (keywords.find(lexeme) != keywords.end())
                    tokens.push_back(init_token(keywords[lexeme], lexeme, line, column));
                else
                    tokens.push_back(init_token(IDENTIFIER, lexeme, line, column));
                
                i--;
                lexeme = "";
                column--;
            }

            else if (state == 3)
            {
                // PT: Encontramos um inteiro
                // EN: Found an integer
                tokens.push_back(init_token(INTEGER, lexeme, line, column));
                lexeme = "";
                i--;
                column--;

            }
            else if (state == 4)
            {
                throw std::runtime_error(std::string("[ERROR::LEX] :: MACHINE_SPIRIT_AGITATED\n\nSIGNAL :: MALFORMED FLUX LITERAL ") + buffer[i - 1] + buffer[i] +" at line " + std::to_string(line) + " and column " + std::to_string(column) + " \n\nRECOVERY :: Ensure all flux literals follow the sanctioned pattern '<numerus>.<numerus>'.");
            }
            else if (state == 5)
            {
                // PT: Encontramos um número real
                // EN: Found a float
                tokens.push_back(init_token(FLOAT, lexeme, line, column));
                lexeme = "";
                i--;
                column--;
            }
            else if (state == 0 && buffer[i] != ' ')
            {
                // PT: Verificamos operadores de dois caracteres
                // EN: Check for two-character operators
                if ((buffer[i] == '<' || buffer[i] == '>' || buffer[i] == '!' || buffer[i] == '=')
                    && i + 1 < bytes_read && buffer[i + 1] == '=')
                {
                    std::string op = std::string(1, buffer[i]) + buffer[i + 1];
                    tokens.push_back(init_token(symbols_and_ops[op], op, line, column));
                    i++;
                }
                else if (buffer[i] == '"')
                {
                    literal = "";
                    i++;

                    while (i < bytes_read - 1 && buffer[i] != '"')
                    {
                        literal += buffer[i];

                        if (buffer[i] == '\n')
                        {
                            line++;
                            column = 1;
                        }
                        else
                            column++;

                        i++;
                    }

                    if (buffer[i] == '"')
                    {
                        tokens.push_back(init_token(STRING, literal, line, column));
                    }
                    else
                    {
                        // PT: Não encontramos finalização da string
                        // EN: Unterminated literal
                        throw std::runtime_error("[ERROR::LEX] :: MACHINE_SPIRIT_FRACTURED\n\nSIGNAL :: OPEN LITERAL\n\nRECOVERY :: ENSURE CORRECT SCRIPTUM FORMULATION");
                    }
                }
                else if (buffer[i] == '\0')
                {
                    tokens.push_back(init_token(END_OF_FILE, "", line, column));
                }
                else
                {
                    if (symbols_and_ops.find(std::string(1, buffer[i])) != symbols_and_ops.end())
                    {
                        tokens.push_back(init_token(symbols_and_ops[std::string(1, buffer[i])], std::string(1, buffer[i]), line, column));
                    }
                    else
                    {
                        throw std::runtime_error(std::string("[ERROR::LEX] :: MACHINE_SPIRIT_AGITATED\n\nSIGNAL :: UNRECOGNIZED TOKEN ") +  buffer[i] +" at line " + std::to_string(line) + " and column " + std::to_string(column) +  "\n\nRECOVERY :: ENSURE CORRECT RITES OF AWAKENING");
                    }
                }
        
            }

            // PT: Atualizar informação de posição
            // EN: Update positional info
            if (buffer[i] == '\n')
            {
                line++;
                column = 1;
            }
            else
            {
                column++;
            }

            // PT: Reiniciar o autômato
            // EN: Restart the automaton
            state = 0;

        }

        else if (new_state == 1 || new_state == 3 || new_state == 4 || new_state == 5)
        {
            lexeme += buffer[i];
            state = new_state;
            column++;
        }
    }

    if (debug)
    {
        for (int i = 0; i < (int)tokens.size(); i++)
        {
            std::cout << "<" << tokens[i].type << "," << tokens[i].lexeme << "> ";
        }
        std::cout << '\n';
    }

    noo_program.close();

    return tokens;    
}