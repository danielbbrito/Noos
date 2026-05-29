#include "sema/analyzer.h"

void SemanticAnalyzer::err(Loc loc, const std::string& msg)
{
    errors_.push_back({loc, msg});
}

bool SemanticAnalyzer::analyze(Program* p)
{
    hoist(p);
    check_program(p);
    return errors_.empty();
}

void SemanticAnalyzer::hoist(Program* p)
{
    /*
        PT: Registra todas as assinaturas de funções antes de verificar qualquer coisa.
        Isso permite que uma função chame outra declarada mais abaixo no arquivo.
        EN: Registers all function signatures before checking anything.
        This allows a function to call another declared further down the file.
    */
    for (auto* item : p->items)
    {
        FuncDecl* f = dynamic_cast<FuncDecl*>(item);
        if (!f) continue;

        Symbol s;
        s.name = f->name;
        s.kind = SymKind::Func;
        s.type = f->return_type;
        for (auto& param : f->params)
            s.param_types.push_back(param.type);

        if (!sym_table_.declare(s))
            err(f->loc, "redeclaration of function '" + f->name + "'");
    }
}

void SemanticAnalyzer::check_program(Program* p)
{
    for (auto* item : p->items)
    {
        if (auto* f = dynamic_cast<FuncDecl*>(item))
            check_func_decl(f);
        else if (auto* s = dynamic_cast<Stmt*>(item))
            check_stmt(s);
    }
}

void SemanticAnalyzer::check_func_decl(FuncDecl* f)
{
    // PT: Cada função tem o seu próprio escopo; os parâmetros vivem nele
    // EN: Each function has its own scope; parameters live inside it
    current_return_ = f->return_type;
    in_function_    = true;
    sym_table_.enter_scope();

    for (auto& param : f->params)
    {
        Symbol s;
        s.name = param.name;
        s.kind = SymKind::Param;
        s.type = param.type;

        if (!sym_table_.declare(s))
            err(f->loc, "duplicate parameter '" + param.name + "'");
    }

    for (auto* stmt : f->body)
        check_stmt(stmt);

    sym_table_.exit_scope();
    in_function_ = false;
}

void SemanticAnalyzer::check_stmt(Stmt* s)
{
    if (auto* v = dynamic_cast<VarDecl*>(s))
    {
        check_var_decl(v);
    }
    else if (auto* a = dynamic_cast<AssignStmt*>(s))
    {
        check_assign(a);
    }
    else if (auto* i = dynamic_cast<IfStmt*>(s))
    {
        // PT: Abre um novo escopo para o bloco do verify
        // EN: Open a new scope for the verify block
        sym_table_.enter_scope();
        for (auto* st : i->then_body) check_stmt(st);
        sym_table_.exit_scope();

        if (!i->else_body.empty())
        {
            sym_table_.enter_scope();
            for (auto* st : i->else_body) check_stmt(st);
            sym_table_.exit_scope();
        }
    }
    else if (auto* w = dynamic_cast<WhileStmt*>(s))
    {
        sym_table_.enter_scope();
        for (auto* st : w->body) check_stmt(st);
        sym_table_.exit_scope();
    }
    else if (auto* c = dynamic_cast<CallStmt*>(s))
    {
        check_call_stmt(c);
    }
    else if (auto* r = dynamic_cast<ReturnStmt*>(s))
    {
        check_return(r);
    }
}

void SemanticAnalyzer::check_var_decl(VarDecl* v)
{
    // PT: Tenta declarar a variável, falha se o nome já existe neste escopo
    // EN: Try to declare the variable, fail if the name already exists in this scope
    Symbol s;
    s.name = v->name;
    s.kind = SymKind::Var;
    s.type = v->decl_type;

    if (!sym_table_.declare(s))
    {
        err(v->loc, "redeclaration of '" + v->name + "'");
        return;
    }

    // PT: Se há um valor inicial, verifica se o tipo bate com o declarado
    // EN: If there is an initial value, check that its type matches the declared type
    if (v->init)
    {
        Type t = expr_type(v->init);
        if (t != v->decl_type)
            err(v->loc, "type mismatch in initializer of '" + v->name + "'");
    }
}

void SemanticAnalyzer::check_assign(AssignStmt* a)
{
    Symbol* sym = sym_table_.lookup(a->name);

    if (!sym)
    {
        err(a->loc, "undeclared variable '" + a->name + "'");
        return;
    }

    Type rhs = expr_type(a->rhs);

    if (a->index)
    {
        // PT: Atribuição a elemento de array: arr[i] = rhs
        // EN: Array element assignment: arr[i] = rhs
        if (!sym->type.is_array)
        {
            err(a->loc, "'" + a->name + "' has not been consecrated as an array");
            return;
        }
        Type elem = sym->type;
        elem.is_array = false;
        elem.array_size = -1;
        if (rhs != elem)
            err(a->loc, "type mismatch in assignment to '" + a->name + "'");
    }
    else
    {
        // PT: Verifica se o tipo do lado direito bate com o tipo da variável
        // EN: Check that the type of the right-hand side matches the variable's type
        if (rhs != sym->type)
            err(a->loc, "type mismatch in assignment to '" + a->name + "'");
    }
}

void SemanticAnalyzer::check_call_stmt(CallStmt* c)
{
    check_call(c->call);
}

void SemanticAnalyzer::check_return(ReturnStmt* r)
{
    if (!in_function_)
    {
        err(r->loc, "transmit outside of ritus");
        return;
    }

    bool is_void = (current_return_.base == BaseType::VOID);

    if (is_void && r->value)
    {
        // PT: Função void não pode retornar um valor
        // EN: Void function must not return a value
        err(r->loc, "nullrite ritus must not return a value");
    }
    else if (!is_void && !r->value)
    {
        // PT: Função não-void deve retornar um valor
        // EN: Non-void function must return a value
        err(r->loc, "ritus must return a value of type '" + std::string(type_name(current_return_.base)) + "'");
    }
    else if (r->value)
    {
        Type t = expr_type(r->value);
        if (t != current_return_)
            err(r->loc, "return type mismatch: expected '" + std::string(type_name(current_return_.base)) +
                "', got '" + std::string(type_name(t.base)) + "'");
    }
}

Type SemanticAnalyzer::check_call(CallExpr* c)
{
    Symbol* sym = sym_table_.lookup(c->name);

    if (!sym)
    {
        err(c->loc, "undeclared function '" + c->name + "'");
        return mk_error();
    }

    if (sym->kind != SymKind::Func)
    {
        err(c->loc, "'" + c->name + "' is not a ritus");
        return mk_error();
    }

    // PT: Verifica se o número de argumentos bate com o número de parâmetros
    // EN: Check that the number of arguments matches the number of parameters
    if (c->args.size() != sym->param_types.size())
    {
        err(c->loc, "'" + c->name + "' expects " + std::to_string(sym->param_types.size()) +
            " arguments, got " + std::to_string(c->args.size()));
    }

    return sym->type;
}

Type SemanticAnalyzer::check_binary(BinaryExpr* b)
{
    Type lhs = expr_type(b->lhs);
    Type rhs = expr_type(b->rhs);

    switch (b->op)
    {
        case OpKind::Add: case OpKind::Sub:
        case OpKind::Mul: case OpKind::Div:
            if (!is_numeric(lhs) || !is_numeric(rhs))
            {
                err(b->loc, "arithmetic operators require numeric operands");
                return mk_error();
            }
            // PT: Se um dos lados é flux, o resultado também é flux
            // EN: If either side is flux, the result is flux
            return (lhs.base == BaseType::FLOAT || rhs.base == BaseType::FLOAT)
                   ? mk_float() : mk_int();

        case OpKind::Lt: case OpKind::Gt:
        case OpKind::Lte: case OpKind::Gte:
            if (!is_numeric(lhs) || !is_numeric(rhs))
            {
                err(b->loc, "comparison operators require numeric operands");
                return mk_error();
            }
            return mk_bool();

        case OpKind::Eq: case OpKind::Neq:
            if (lhs != rhs)
            {
                err(b->loc, "equality comparison between incompatible types");
                return mk_error();
            }
            return mk_bool();

        case OpKind::And: case OpKind::Or:
            if (lhs != mk_bool() || rhs != mk_bool())
            {
                err(b->loc, "conjunction/divergence require veritas operands");
                return mk_error();
            }
            return mk_bool();

        default:
            return mk_error();
    }
}

Type SemanticAnalyzer::check_unary(UnaryExpr* u)
{
    Type t = expr_type(u->operand);

    if (u->op == OpKind::Neg)
    {
        if (!is_numeric(t))
        {
            err(u->loc, "unary '-' requires a numeric operand");
            return mk_error();
        }
        return t;
    }

    if (u->op == OpKind::Not)
    {
        if (t != mk_bool())
        {
            err(u->loc, "unary '!' requires a veritas operand");
            return mk_error();
        }
        return mk_bool();
    }

    return mk_error();
}

Type SemanticAnalyzer::expr_type(Expr* e)
{
    if (dynamic_cast<IntLit*>(e))    return mk_int();
    if (dynamic_cast<FloatLit*>(e))  return mk_float();
    if (dynamic_cast<StringLit*>(e)) return mk_string();
    if (dynamic_cast<BoolLit*>(e))   return mk_bool();

    if (auto* vr = dynamic_cast<VarRef*>(e))
    {
        Symbol* s = sym_table_.lookup(vr->name);
        if (!s)
        {
            err(vr->loc, "undeclared variable '" + vr->name + "'");
            return mk_error();
        }
        return s->type;
    }

    if (auto* ie = dynamic_cast<IndexExpr*>(e))
    {
        Symbol* s = sym_table_.lookup(ie->name);
        if (!s) { err(ie->loc, "undeclared variable '" + ie->name + "'"); return mk_error(); }
        if (!s->type.is_array) { err(ie->loc, "'" + ie->name + "' has not been consecrated as an array"); return mk_error(); }
        Type elem = s->type;
        elem.is_array = false;
        elem.array_size = -1;
        return elem;
    }

    if (auto* ce = dynamic_cast<CallExpr*>(e))
        return check_call(ce);

    if (auto* be = dynamic_cast<BinaryExpr*>(e))
        return check_binary(be);

    if (auto* ue = dynamic_cast<UnaryExpr*>(e))
        return check_unary(ue);

    return mk_error();
}
