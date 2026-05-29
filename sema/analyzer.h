#pragma once
#include <string>
#include <vector>
#include "ast.h"
#include "sema/scope.h"

struct SemanticError
{
    Loc         loc;
    std::string message;
};

class SemanticAnalyzer
{
    SymbolTable                sym_table_;
    std::vector<SemanticError> errors_;
    Type                       current_return_ = mk_void(); // PT: tipo de retorno da função atual
                                                            // EN: return type of the current function
    bool                       in_function_    = false;

    void hoist(Program* p);
    void check_program(Program* p);
    void check_func_decl(FuncDecl* f);
    void check_stmt(Stmt* s);
    void check_var_decl(VarDecl* v);
    void check_assign(AssignStmt* a);
    void check_call_stmt(CallStmt* c);
    void check_return(ReturnStmt* r);
    Type check_call(CallExpr* c);
    Type check_binary(BinaryExpr* b);
    Type check_unary(UnaryExpr* u);
    Type expr_type(Expr* e);

    void err(Loc loc, const std::string& msg);

public:
    bool analyze(Program* p);
    const std::vector<SemanticError>& errors() const { return errors_; }
};
