#include "codegen.h"

// PT: Mapeia os tipos de Noos para os equivalentes em C++
// EN: Maps Noos types to their C++ equivalents
std::string CppEmitter::type_str(const Type& t)
{
    std::string base;
    switch (t.base)
    {
        case BaseType::INT:    base = "int";         break;
        case BaseType::FLOAT:  base = "double";      break;
        case BaseType::BOOL:   base = "bool";        break;
        case BaseType::STRING: base = "std::string"; break;
        case BaseType::VOID:   base = "void";        break;
        default:               base = "/*unknown*/"; break;
    }
    if (t.is_array) return "std::vector<" + base + ">";
    return base;
}

void CppEmitter::line(const std::string& s)
{
    out_ << std::string(indent_ * 4, ' ') << s << "\n";
}

// PT: Converte uma expressão da AST para uma string C++
// EN: Converts an AST expression to a C++ string
std::string CppEmitter::emit_expr(Expr* e)
{
    if (auto* il = dynamic_cast<IntLit*>(e))    return std::to_string(il->value);
    if (auto* fl = dynamic_cast<FloatLit*>(e))  return std::to_string(fl->value);
    if (auto* sl = dynamic_cast<StringLit*>(e)) return "\"" + sl->value + "\"";
    if (auto* bl = dynamic_cast<BoolLit*>(e))   return bl->value ? "true" : "false";
    if (auto* vr = dynamic_cast<VarRef*>(e))    return vr->name;
    if (auto* ie = dynamic_cast<IndexExpr*>(e)) return ie->name + "[" + emit_expr(ie->index) + "]";

    if (auto* ce = dynamic_cast<CallExpr*>(e))
    {
        std::string s = ce->name + "(";
        for (int i = 0; i < (int)ce->args.size(); i++)
        {
            if (i) s += ", ";
            s += emit_expr(ce->args[i]);
        }
        return s + ")";
    }

    if (auto* be = dynamic_cast<BinaryExpr*>(e))
    {
        std::string op;
        switch (be->op)
        {
            case OpKind::Add: op = "+";  break;
            case OpKind::Sub: op = "-";  break;
            case OpKind::Mul: op = "*";  break;
            case OpKind::Div: op = "/";  break;
            case OpKind::Eq:  op = "=="; break;
            case OpKind::Neq: op = "!="; break;
            case OpKind::Lt:  op = "<";  break;
            case OpKind::Gt:  op = ">";  break;
            case OpKind::Lte: op = "<="; break;
            case OpKind::Gte: op = ">="; break;
            case OpKind::And: op = "&&"; break;
            case OpKind::Or:  op = "||"; break;
            default: op = "?";
        }
        return "(" + emit_expr(be->lhs) + " " + op + " " + emit_expr(be->rhs) + ")";
    }

    if (auto* ue = dynamic_cast<UnaryExpr*>(e))
    {
        std::string op = (ue->op == OpKind::Neg) ? "-" : "!";
        return op + emit_expr(ue->operand);
    }

    return "/*unknown expr*/";
}

// PT: Emite um statement da AST como código C++
// EN: Emits an AST statement as C++ code
void CppEmitter::emit_stmt(Stmt* s)
{
    if (auto* v = dynamic_cast<VarDecl*>(s))
    {
        emit_var_decl(v);
    }
    else if (auto* a = dynamic_cast<AssignStmt*>(s))
    {
        if (a->index)
            line(a->name + "[" + emit_expr(a->index) + "] = " + emit_expr(a->rhs) + ";");
        else
            line(a->name + " = " + emit_expr(a->rhs) + ";");
    }
    else if (auto* pr = dynamic_cast<PrintStmt*>(s))
    {
        line("std::cout << " + emit_expr(pr->arg) + ";");
    }
    else if (auto* cs = dynamic_cast<CallStmt*>(s))
    {
        line(emit_expr(cs->call) + ";");
    }
    else if (auto* r = dynamic_cast<ReturnStmt*>(s))
    {
        line(r->value ? "return " + emit_expr(r->value) + ";" : "return;");
    }
    else if (auto* i = dynamic_cast<IfStmt*>(s))
    {
        line("if (" + emit_expr(i->cond) + ") {");
        push();
        for (auto* st : i->then_body) emit_stmt(st);
        pop();
        if (!i->else_body.empty())
        {
            line("} else {");
            push();
            for (auto* st : i->else_body) emit_stmt(st);
            pop();
        }
        line("}");
    }
    else if (auto* w = dynamic_cast<WhileStmt*>(s))
    {
        line("while (" + emit_expr(w->cond) + ") {");
        push();
        for (auto* st : w->body) emit_stmt(st);
        pop();
        line("}");
    }
}

void CppEmitter::emit_var_decl(VarDecl* v)
{
    if (v->array_size >= 0)
    {
        std::string t = type_str(v->decl_type); // already "std::vector<base>"
        if (!v->array_init.empty())
        {
            std::string init = "{";
            for (int i = 0; i < (int)v->array_init.size(); i++)
            {
                if (i) init += ", ";
                init += emit_expr(v->array_init[i]);
            }
            line(t + " " + v->name + " = " + init + "};");
        }
        else
        {
            line(t + " " + v->name + "(" + std::to_string(v->array_size) + ");");
        }
    }
    else
    {
        if (v->init)
            line(type_str(v->decl_type) + " " + v->name + " = " + emit_expr(v->init) + ";");
        else
            line(type_str(v->decl_type) + " " + v->name + ";");
    }
}

void CppEmitter::emit_func_decl(FuncDecl* f)
{
    std::string sig = type_str(f->return_type) + " " + f->name + "(";
    for (int i = 0; i < (int)f->params.size(); i++)
    {
        if (i) sig += ", ";
        sig += type_str(f->params[i].type) + " " + f->params[i].name;
    }
    sig += ") {";
    line(sig);
    push();
    for (auto* st : f->body) emit_stmt(st);
    pop();
    line("}");
}

std::string CppEmitter::emit(Program* p)
{
    line("#include <iostream>");
    line("#include <string>");
    line("#include <vector>");
    line("");

    // PT: Emite as funções primeiro, depois os statements globais dentro do main
    // EN: Emit functions first, then global statements inside main
    for (auto* item : p->items)
    {
        if (auto* f = dynamic_cast<FuncDecl*>(item))
        {
            emit_func_decl(f);
            line("");
        }
    }

    line("int main() {");
    push();
    for (auto* item : p->items)
    {
        if (auto* s = dynamic_cast<Stmt*>(item))
            emit_stmt(s);
    }
    line("return 0;");
    pop();
    line("}");

    return out_.str();
}
