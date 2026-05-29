%require "3.2"
%skeleton "lalr1.cc"
%defines "parser.hh"

%define api.token.prefix {T_}
%define api.value.type variant
%define api.token.constructor
%define parse.error detailed
%define parse.lac full
%locations
%expect 0

/* ---- types needed in the generated header ---- */
%code requires {
    #include "ast.h"
    #include "type.h"
    #include <vector>
    #include <string>
}

/* ---- code placed in generated parser.cpp only ---- */
%code {
    #include "lexer_bridge.h"
    extern Arena    g_arena;
    extern Program* g_program;
    // Forward-declare the yylex function implemented in lexer_bridge.cpp
    yy::parser::symbol_type yylex();
}

/* ---- tokens with string values ---- */
%token <std::string> IDENTIFIER "identifier"
%token <std::string> INTEGER    "integer"
%token <std::string> FLOAT      "float"
%token <std::string> STRING     "string"

/* ---- keyword / punctuation tokens (no value) ---- */
%token CODEX        "codex"
%token RITUS        "ritus"
%token CYCLE        "cycle"
%token IF           "verify"
%token ELSE         "fallback"
%token INITIATE     "initiate"
%token END_CODEX    "codexterminate"
%token END_RITUS    "ritusterminate"
%token END_IF       "verifyterminate"
%token END_CYCLE    "cycleterminate"
%token RETURN       "transmit"
%token TRUE         "verum"
%token FALSE        "falsum"
%token TYPE_INT     "numerus"
%token TYPE_FLOAT   "flux"
%token TYPE_STRING  "scriptum"
%token TYPE_BOOLEAN "veritas"
%token PRINT        "vox"
%token VOID         "nullrite"
%token ASSIGN       "="
%token PLUS         "+"
%token MINUS        "-"
%token MULT         "*"
%token DIV          "/"
%token EQ           "=="
%token NEQ          "!="
%token GT           ">"
%token LT           "<"
%token GTE          ">="
%token LTE          "<="
%token NOT          "!"
%token AND          "conjunction"
%token OR           "divergence"
%token LPAR         "("
%token RPAR         ")"
%token COMMA        ","
%token LBRACE       "{"
%token RBRACE       "}"
%token LBRACK       "["
%token RBRACK       "]"
%token NEWLINE      "newline"

/* ---- non-terminal types ---- */
%type <Program*>             program
%type <std::vector<Node*>>   global_sequence
%type <std::vector<Stmt*>>   statement_sequence
%type <Stmt*>                statement
%type <Stmt*>                variable_declaration
%type <Stmt*>                assignment_statement
%type <Stmt*>                print_statement
%type <Stmt*>                function_call_stmt
%type <Stmt*>                return_statement
%type <Stmt*>                if_statement
%type <Stmt*>                while_statement
%type <std::vector<Stmt*>>   else_clause
%type <FuncDecl*>            function_declaration
%type <std::vector<Param>>   parameter_list
%type <Param>                parameter
%type <Expr*>                expression
%type <Expr*>                logical_or_expression
%type <Expr*>                logical_and_expression
%type <Expr*>                equality_expression
%type <Expr*>                relational_expression
%type <Expr*>                additive_expression
%type <Expr*>                multiplicative_expression
%type <Expr*>                unary_expression
%type <Expr*>                primary_expression
%type <std::vector<Expr*>>   expression_list
%type <std::vector<Expr*>>   argument_list
%type <std::vector<Expr*>>   array_initializer
%type <Type>                 value_type
%type <Type>                 return_type

%%

/* ================================================================
   Program
   ================================================================ */

program:
    CODEX INITIATE NEWLINE global_sequence END_CODEX
    {
        auto* p   = g_arena.make<Program>();
        p->loc    = { @1.begin.line, @1.begin.column };
        p->items  = std::move($4);
        g_program = p;
        $$ = p;
    }
  | CODEX INITIATE NEWLINE global_sequence END_CODEX NEWLINE
    {
        auto* p   = g_arena.make<Program>();
        p->loc    = { @1.begin.line, @1.begin.column };
        p->items  = std::move($4);
        g_program = p;
        $$ = p;
    }
;

/* ================================================================
   Sequences  (left-recursive for LALR efficiency)
   ================================================================ */

global_sequence:
    /* empty */                              { $$ = {}; }
  | global_sequence NEWLINE                  { $$ = std::move($1); }
  | global_sequence statement NEWLINE        { $1.push_back($2); $$ = std::move($1); }
  | global_sequence function_declaration NEWLINE { $1.push_back($2); $$ = std::move($1); }
;

statement_sequence:
    /* empty */                              { $$ = {}; }
  | statement_sequence NEWLINE              { $$ = std::move($1); }
  | statement_sequence statement NEWLINE    { $1.push_back($2); $$ = std::move($1); }
;

/* ================================================================
   Statements
   ================================================================ */

statement:
    variable_declaration   { $$ = $1; }
  | assignment_statement   { $$ = $1; }
  | print_statement        { $$ = $1; }
  | function_call_stmt     { $$ = $1; }
  | return_statement       { $$ = $1; }
  | if_statement           { $$ = $1; }
  | while_statement        { $$ = $1; }
;

variable_declaration:
    value_type IDENTIFIER
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { @2.begin.line, @2.begin.column };
        n->declType = $1;  n->name = $2;
        $$ = n;
    }
  | value_type IDENTIFIER ASSIGN expression
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { @2.begin.line, @2.begin.column };
        n->declType = $1;  n->name = $2;  n->init = $4;
        $$ = n;
    }
  | value_type IDENTIFIER LBRACK INTEGER RBRACK
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { @2.begin.line, @2.begin.column };
        n->declType = $1;  n->name = $2;
        n->arraySize = std::stoi($4);
        n->declType.isArray   = true;
        n->declType.arraySize = n->arraySize;
        $$ = n;
    }
  | value_type IDENTIFIER LBRACK INTEGER RBRACK ASSIGN array_initializer
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { @2.begin.line, @2.begin.column };
        n->declType = $1;  n->name = $2;
        n->arraySize = std::stoi($4);
        n->declType.isArray   = true;
        n->declType.arraySize = n->arraySize;
        n->arrayInit = std::move($7);
        $$ = n;
    }
;

array_initializer:
    LBRACE RBRACE                   { $$ = {}; }
  | LBRACE expression_list RBRACE   { $$ = std::move($2); }
;

expression_list:
    expression                      { $$ = { $1 }; }
  | expression_list COMMA expression { $1.push_back($3); $$ = std::move($1); }
;

assignment_statement:
    IDENTIFIER ASSIGN expression
    {
        auto* n = g_arena.make<AssignStmt>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->name = $1;  n->rhs = $3;
        $$ = n;
    }
  | IDENTIFIER LBRACK expression RBRACK ASSIGN expression
    {
        auto* n = g_arena.make<AssignStmt>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->name = $1;  n->index = $3;  n->rhs = $6;
        $$ = n;
    }
;

print_statement:
    PRINT LPAR expression RPAR
    {
        auto* n = g_arena.make<PrintStmt>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->arg = $3;
        $$ = n;
    }
;

/* function call used as a statement */
function_call_stmt:
    IDENTIFIER LPAR RPAR
    {
        auto* c = g_arena.make<CallExpr>();
        c->loc  = { @1.begin.line, @1.begin.column };
        c->name = $1;
        auto* n = g_arena.make<CallStmt>();
        n->loc  = c->loc;  n->call = c;
        $$ = n;
    }
  | IDENTIFIER LPAR argument_list RPAR
    {
        auto* c = g_arena.make<CallExpr>();
        c->loc  = { @1.begin.line, @1.begin.column };
        c->name = $1;  c->args = std::move($3);
        auto* n = g_arena.make<CallStmt>();
        n->loc  = c->loc;  n->call = c;
        $$ = n;
    }
;

return_statement:
    RETURN
    {
        auto* n = g_arena.make<ReturnStmt>();
        n->loc = { @1.begin.line, @1.begin.column };
        $$ = n;
    }
  | RETURN expression
    {
        auto* n = g_arena.make<ReturnStmt>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = $2;
        $$ = n;
    }
;

if_statement:
    IF expression NEWLINE statement_sequence END_IF
    {
        auto* n = g_arena.make<IfStmt>();
        n->loc      = { @1.begin.line, @1.begin.column };
        n->cond     = $2;
        n->thenBody = std::move($4);
        $$ = n;
    }
  | IF expression NEWLINE statement_sequence else_clause END_IF
    {
        auto* n = g_arena.make<IfStmt>();
        n->loc      = { @1.begin.line, @1.begin.column };
        n->cond     = $2;
        n->thenBody = std::move($4);
        n->elseBody = std::move($5);
        $$ = n;
    }
;

else_clause:
    ELSE NEWLINE statement_sequence  { $$ = std::move($3); }
;

while_statement:
    CYCLE expression NEWLINE statement_sequence END_CYCLE
    {
        auto* n = g_arena.make<WhileStmt>();
        n->loc  = { @1.begin.line, @1.begin.column };
        n->cond = $2;
        n->body = std::move($4);
        $$ = n;
    }
;

/* ================================================================
   Functions
   ================================================================ */

function_declaration:
    RITUS return_type IDENTIFIER LPAR RPAR INITIATE NEWLINE statement_sequence END_RITUS
    {
        auto* f = g_arena.make<FuncDecl>();
        f->loc         = { @3.begin.line, @3.begin.column };
        f->returnType  = $2;
        f->name        = $3;
        f->body        = std::move($8);
        $$ = f;
    }
  | RITUS return_type IDENTIFIER LPAR parameter_list RPAR INITIATE NEWLINE statement_sequence END_RITUS
    {
        auto* f = g_arena.make<FuncDecl>();
        f->loc         = { @3.begin.line, @3.begin.column };
        f->returnType  = $2;
        f->name        = $3;
        f->params      = std::move($5);
        f->body        = std::move($9);
        $$ = f;
    }
;

parameter_list:
    parameter                        { $$ = { $1 }; }
  | parameter_list COMMA parameter   { $1.push_back($3); $$ = std::move($1); }
;

parameter:
    value_type IDENTIFIER
    {
        $$ = Param{ $1, $2, false };
    }
  | value_type IDENTIFIER LBRACK RBRACK
    {
        Type t = $1;  t.isArray = true;
        $$ = Param{ t, $2, true };
    }
;

/* ================================================================
   Types
   ================================================================ */

return_type:
    value_type             { $$ = $1; }
  | value_type LBRACK RBRACK
    {
        Type t = $1;  t.isArray = true;
        $$ = t;
    }
  | VOID                   { $$ = mkVoid(); }
;

value_type:
    TYPE_INT     { $$ = mkInt();    }
  | TYPE_FLOAT   { $$ = mkFloat();  }
  | TYPE_BOOLEAN { $$ = mkBool();   }
  | TYPE_STRING  { $$ = mkString(); }
;

/* ================================================================
   Arguments
   ================================================================ */

argument_list:
    expression                      { $$ = { $1 }; }
  | argument_list COMMA expression  { $1.push_back($3); $$ = std::move($1); }
;

/* ================================================================
   Expressions  (precedence encoded structurally, no %left/%right)
   ================================================================ */

expression: logical_or_expression { $$ = $1; };

logical_or_expression:
    logical_and_expression                              { $$ = $1; }
  | logical_or_expression OR logical_and_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op  = OpKind::Or;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

logical_and_expression:
    equality_expression                                 { $$ = $1; }
  | logical_and_expression AND equality_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op  = OpKind::And;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

equality_expression:
    relational_expression                               { $$ = $1; }
  | equality_expression EQ  relational_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op  = OpKind::Eq;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | equality_expression NEQ relational_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op  = OpKind::Neq;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

relational_expression:
    additive_expression                                 { $$ = $1; }
  | relational_expression GT  additive_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Gt;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | relational_expression LT  additive_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Lt;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | relational_expression GTE additive_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Gte;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | relational_expression LTE additive_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Lte;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

additive_expression:
    multiplicative_expression                           { $$ = $1; }
  | additive_expression PLUS  multiplicative_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Add;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | additive_expression MINUS multiplicative_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Sub;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

multiplicative_expression:
    unary_expression                                    { $$ = $1; }
  | multiplicative_expression MULT unary_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Mul;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
  | multiplicative_expression DIV  unary_expression
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { @1.begin.line, @1.begin.column };
        n->op = OpKind::Div;  n->lhs = $1;  n->rhs = $3;
        $$ = n;
    }
;

unary_expression:
    primary_expression                  { $$ = $1; }
  | MINUS unary_expression
    {
        auto* n = g_arena.make<UnaryExpr>();
        n->loc     = { @1.begin.line, @1.begin.column };
        n->op      = OpKind::Neg;  n->operand = $2;
        $$ = n;
    }
  | NOT unary_expression
    {
        auto* n = g_arena.make<UnaryExpr>();
        n->loc     = { @1.begin.line, @1.begin.column };
        n->op      = OpKind::Not;  n->operand = $2;
        $$ = n;
    }
;

primary_expression:
    INTEGER
    {
        auto* n = g_arena.make<IntLit>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = std::stol($1);
        $$ = n;
    }
  | FLOAT
    {
        auto* n = g_arena.make<FloatLit>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = std::stod($1);
        $$ = n;
    }
  | STRING
    {
        auto* n = g_arena.make<StringLit>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = $1;
        $$ = n;
    }
  | TRUE
    {
        auto* n = g_arena.make<BoolLit>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = true;
        $$ = n;
    }
  | FALSE
    {
        auto* n = g_arena.make<BoolLit>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->value = false;
        $$ = n;
    }
  | IDENTIFIER
    {
        auto* n = g_arena.make<VarRef>();
        n->loc  = { @1.begin.line, @1.begin.column };
        n->name = $1;
        $$ = n;
    }
  /* function call in expression */
  | IDENTIFIER LPAR RPAR
    {
        auto* n = g_arena.make<CallExpr>();
        n->loc  = { @1.begin.line, @1.begin.column };
        n->name = $1;
        $$ = n;
    }
  | IDENTIFIER LPAR argument_list RPAR
    {
        auto* n = g_arena.make<CallExpr>();
        n->loc  = { @1.begin.line, @1.begin.column };
        n->name = $1;  n->args = std::move($3);
        $$ = n;
    }
  /* array element access */
  | IDENTIFIER LBRACK expression RBRACK
    {
        auto* n = g_arena.make<IndexExpr>();
        n->loc   = { @1.begin.line, @1.begin.column };
        n->name  = $1;  n->index = $3;
        $$ = n;
    }
  | LPAR expression RPAR  { $$ = $2; }
;

%%

/* ---- error handler ---- */
void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.begin.line << ":" << loc.begin.column << ": error: " << msg << "\n";
}
