#pragma once
#include <string>
#include <map>
#include <vector>
#include "sema/symbol.h"

/*
    PT: A tabela de símbolos é uma pilha de escopos. Cada vez que entramos
    num bloco (verify, cycle, ritus) empurramos um novo escopo. Quando saímos,
    removemos esse escopo e os símbolos declarados nele deixam de existir.
    EN: The symbol table is a stack of scopes. Each time we enter a block
    (verify, cycle, ritus) we push a new scope. When we leave, we pop it
    and the symbols declared inside cease to exist.
*/

struct Scope
{
    std::map<std::string, Symbol> symbols;
};

class SymbolTable
{
    std::vector<Scope> stack_;

public:
    SymbolTable();

    // PT: Entra/sai de um bloco
    // EN: Enter/leave a block
    void enter_scope();
    void exit_scope();

    // PT: Declara um símbolo no escopo atual. Retorna false se o nome já existe no mesmo escopo.
    // EN: Declares a symbol in the current scope. Returns false if the name already exists there.
    bool declare(const Symbol& s);

    // PT: Procura um símbolo em todos os escopos, do mais interno ao mais externo
    // EN: Looks up a symbol across all scopes, from innermost to outermost
    Symbol* lookup(const std::string& name);
};
