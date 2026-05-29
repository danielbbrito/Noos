#include "sema/scope.h"

SymbolTable::SymbolTable()
{
    // PT: Começa com o escopo global já aberto
    // EN: Starts with the global scope already open
    enter_scope();
}

void SymbolTable::enter_scope()
{
    stack_.push_back(Scope{});
}

void SymbolTable::exit_scope()
{
    stack_.pop_back();
}

bool SymbolTable::declare(const Symbol& s)
{
    Scope& current = stack_.back();

    // PT: Verifica se o nome já foi declarado neste escopo
    // EN: Check if the name was already declared in this scope
    if (current.symbols.count(s.name))
        return false;

    current.symbols[s.name] = s;
    return true;
}

Symbol* SymbolTable::lookup(const std::string& name)
{
    // PT: Percorre a pilha de dentro para fora até encontrar o símbolo
    // EN: Walks the stack from innermost to outermost until the symbol is found
    for (int i = (int)stack_.size() - 1; i >= 0; i--)
    {
        auto it = stack_[i].symbols.find(name);
        if (it != stack_[i].symbols.end())
            return &it->second;
    }

    return nullptr;
}
