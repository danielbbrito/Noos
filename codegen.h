#pragma once
#include "ast.h"
#include <string>
#include <sstream>

class CppEmitter
{
    std::ostringstream out_;
    int indent_ = 0;

    void line(const std::string& s);
    void push() { ++indent_; }
    void pop()  { --indent_; }

    std::string type_str(const Type& t);
    std::string emit_expr(Expr* e);
    void emit_stmt(Stmt* s);
    void emit_var_decl(VarDecl* v);
    void emit_func_decl(FuncDecl* f);

public:
    std::string emit(Program* p);
};
