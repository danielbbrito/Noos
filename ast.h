#pragma once
#include <string>
#include <vector>
#include <memory>
#include "type.h"

struct Loc { int line = 0, col = 0; };

enum class OpKind {
    Add, Sub, Mul, Div,
    Eq, Neq, Lt, Gt, Lte, Gte,
    And, Or,
    Neg, Not
};

// ---- Base nodes ----
struct Node { Loc loc; virtual ~Node() = default; };
struct Expr : Node { Type resolved_type; };
struct Stmt : Node {};

// ---- Expressions ----
struct IntLit    : Expr { long value = 0; };
struct FloatLit  : Expr { double value = 0.0; };
struct StringLit : Expr { std::string value; };
struct BoolLit   : Expr { bool value = false; };

struct VarRef : Expr { std::string name; };

struct IndexExpr : Expr {
    std::string name;
    Expr* index = nullptr;
};

struct CallExpr : Expr {
    std::string name;
    std::vector<Expr*> args;
};

struct UnaryExpr : Expr {
    OpKind op;
    Expr* operand = nullptr;
};

struct BinaryExpr : Expr {
    OpKind op;
    Expr* lhs = nullptr;
    Expr* rhs = nullptr;
};

// ---- Statements ----
struct VarDecl : Stmt {
    Type        decl_type;
    std::string name;
    int         array_size = -1;
    Expr*       init       = nullptr;
    std::vector<Expr*> array_init;
};

struct AssignStmt : Stmt {
    std::string name;
    Expr* index = nullptr;
    Expr* rhs   = nullptr;
};

struct PrintStmt  : Stmt { Expr* arg = nullptr; };
struct CallStmt   : Stmt { CallExpr* call = nullptr; };
struct ReturnStmt : Stmt { Expr* value = nullptr; };

struct IfStmt : Stmt {
    Expr* cond = nullptr;
    std::vector<Stmt*> then_body;
    std::vector<Stmt*> else_body;
};

struct WhileStmt : Stmt {
    Expr* cond = nullptr;
    std::vector<Stmt*> body;
};

// ---- Function ----
struct Param { Type type; std::string name; bool is_array = false; };

struct FuncDecl : Node {
    Type        return_type;
    bool        returns_array = false;
    std::string name;
    std::vector<Param> params;
    std::vector<Stmt*> body;
};

// ---- Program ----
struct Program : Node { std::vector<Node*> items; };

// ---- Arena ----
class Arena {
    std::vector<std::unique_ptr<Node>> pool_;
public:
    template<typename T, typename... Args>
    T* make(Args&&... args) {
        auto p = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = p.get();
        pool_.push_back(std::move(p));
        return raw;
    }
};

extern Arena    g_arena;
extern Program* g_program;

void print_ast(const Node* node, int indent = 0);
