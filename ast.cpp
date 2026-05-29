#include "ast.h"
#include <iostream>
#include <string>

Arena    g_arena;
Program* g_program = nullptr;

static const char* op_str(OpKind op) {
    switch (op) {
        case OpKind::Add: return "+";   case OpKind::Sub: return "-";
        case OpKind::Mul: return "*";   case OpKind::Div: return "/";
        case OpKind::Eq:  return "==";  case OpKind::Neq: return "!=";
        case OpKind::Lt:  return "<";   case OpKind::Gt:  return ">";
        case OpKind::Lte: return "<=";  case OpKind::Gte: return ">=";
        case OpKind::And: return "&&";  case OpKind::Or:  return "||";
        case OpKind::Neg: return "-";   case OpKind::Not: return "!";
    }
    return "?";
}

static std::string type_str(const Type& t) {
    std::string s = type_name(t.base);
    if (t.is_array) s += "[]";
    return s;
}

static std::string pad(int indent) { return std::string(indent * 2, ' '); }

void print_ast(const Node* node, int indent) {
    if (!node) { std::cout << pad(indent) << "<null>\n"; return; }

    if (auto* p = dynamic_cast<const Program*>(node)) {
        std::cout << pad(indent) << "Program\n";
        for (auto* item : p->items) print_ast(item, indent + 1);
    }
    else if (auto* f = dynamic_cast<const FuncDecl*>(node)) {
        std::cout << pad(indent) << "FuncDecl " << type_str(f->return_type)
                  << (f->returns_array ? "[]" : "") << " " << f->name << "(";
        for (int i = 0; i < (int)f->params.size(); i++) {
            auto& pr = f->params[i];
            if (i) std::cout << ", ";
            std::cout << type_str(pr.type) << (pr.is_array ? "[]" : "") << " " << pr.name;
        }
        std::cout << ")\n";
        for (auto* s : f->body) print_ast(s, indent + 1);
    }
    else if (auto* v = dynamic_cast<const VarDecl*>(node)) {
        std::cout << pad(indent) << "VarDecl " << type_str(v->decl_type) << " " << v->name;
        if (v->array_size >= 0) std::cout << "[" << v->array_size << "]";
        std::cout << "\n";
        if (v->init) print_ast(v->init, indent + 1);
        for (auto* e : v->array_init) print_ast(e, indent + 1);
    }
    else if (auto* a = dynamic_cast<const AssignStmt*>(node)) {
        std::cout << pad(indent) << "Assign " << a->name;
        if (a->index) { std::cout << "[]\n"; print_ast(a->index, indent + 1); }
        else std::cout << "\n";
        print_ast(a->rhs, indent + 1);
    }
    else if (auto* pr = dynamic_cast<const PrintStmt*>(node)) {
        std::cout << pad(indent) << "Print\n";
        print_ast(pr->arg, indent + 1);
    }
    else if (auto* cs = dynamic_cast<const CallStmt*>(node)) {
        print_ast(cs->call, indent);
    }
    else if (auto* r = dynamic_cast<const ReturnStmt*>(node)) {
        std::cout << pad(indent) << "Return\n";
        if (r->value) print_ast(r->value, indent + 1);
    }
    else if (auto* i = dynamic_cast<const IfStmt*>(node)) {
        std::cout << pad(indent) << "If\n";
        print_ast(i->cond, indent + 1);
        std::cout << pad(indent + 1) << "Then:\n";
        for (auto* s : i->then_body) print_ast(s, indent + 2);
        if (!i->else_body.empty()) {
            std::cout << pad(indent + 1) << "Else:\n";
            for (auto* s : i->else_body) print_ast(s, indent + 2);
        }
    }
    else if (auto* w = dynamic_cast<const WhileStmt*>(node)) {
        std::cout << pad(indent) << "While\n";
        print_ast(w->cond, indent + 1);
        for (auto* s : w->body) print_ast(s, indent + 2);
    }
    else if (auto* b = dynamic_cast<const BinaryExpr*>(node)) {
        std::cout << pad(indent) << "Binary " << op_str(b->op) << "\n";
        print_ast(b->lhs, indent + 1);
        print_ast(b->rhs, indent + 1);
    }
    else if (auto* u = dynamic_cast<const UnaryExpr*>(node)) {
        std::cout << pad(indent) << "Unary " << op_str(u->op) << "\n";
        print_ast(u->operand, indent + 1);
    }
    else if (auto* c = dynamic_cast<const CallExpr*>(node)) {
        std::cout << pad(indent) << "Call " << c->name << "\n";
        for (auto* a : c->args) print_ast(a, indent + 1);
    }
    else if (auto* ie = dynamic_cast<const IndexExpr*>(node)) {
        std::cout << pad(indent) << "Index " << ie->name << "\n";
        print_ast(ie->index, indent + 1);
    }
    else if (auto* vr = dynamic_cast<const VarRef*>(node)) {
        std::cout << pad(indent) << "VarRef " << vr->name << "\n";
    }
    else if (auto* il = dynamic_cast<const IntLit*>(node)) {
        std::cout << pad(indent) << "Int " << il->value << "\n";
    }
    else if (auto* fl = dynamic_cast<const FloatLit*>(node)) {
        std::cout << pad(indent) << "Float " << fl->value << "\n";
    }
    else if (auto* sl = dynamic_cast<const StringLit*>(node)) {
        std::cout << pad(indent) << "String \"" << sl->value << "\"\n";
    }
    else if (auto* bl = dynamic_cast<const BoolLit*>(node)) {
        std::cout << pad(indent) << "Bool " << (bl->value ? "verum" : "falsum") << "\n";
    }
    else {
        std::cout << pad(indent) << "<unknown node>\n";
    }
}
