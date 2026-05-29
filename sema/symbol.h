#pragma once
#include <string>
#include <vector>
#include "type.h"

/*
    PT: Um símbolo representa qualquer nome declarado no programa:
    uma variável, um parâmetro ou uma função
    EN: A symbol represents any declared name in the program:
    a variable, a parameter, or a function
*/
enum class SymKind { Var, Param, Func };

struct Symbol
{
    std::string       name;
    SymKind           kind;
    Type              type;         // PT: tipo da variável/parâmetro, ou tipo de retorno se for função
                                    // EN: type of the variable/param, or return type if it's a function
    std::vector<Type> param_types;  // PT: apenas usado para funções
                                    // EN: only used for functions
};
