/*
PT: token.h deve ser incluido antes de parser.hh para que o enum TokenType
seja compilado antes das macros T_* geradas pelo Bison
EN: token.h must be included before parser.hh so the TokenType enum is
compiled before Bison's T_* macros are defined
*/
#include "token.h"
#include "parser.hh"
#include "lexer_bridge.h"

// PT: Alias para encurtar o namespace do parser gerado pelo Bison
// EN: Alias to shorten the namespace of the Bison-generated parser
using P = yy::parser;

const std::vector<Token>* g_tokens = nullptr;
int g_pos = 0;

void bridge_set_tokens(const std::vector<Token>& tokens)
{
    // PT: Aponta para o vetor de tokens produzido pelo lexer e reinicia o cursor
    // EN: Points to the token vector produced by the lexer and resets the cursor
    g_tokens = &tokens;
    g_pos    = 0;
}

P::location_type make_loc(const Token& t)
{
    /*
        PT: Converte a posição do token (base 0 do lexer) para o formato de
        localização do Bison (base 1)
        EN: Converts the token position (0-based from the lexer) to Bison's
        location format (1-based)
    */
    P::location_type loc;
    loc.begin.line   = t.line + 1;
    loc.begin.column = t.column + 1;
    loc.end = loc.begin;
    return loc;
}

P::symbol_type yylex()
{
    if (g_pos >= (int)g_tokens->size())
        return P::make_YYEOF(P::location_type{});

    const Token& t = (*g_tokens)[g_pos++];
    P::location_type loc = make_loc(t);

    // PT: Mapeia cada tipo de token do lexer para o símbolo correspondente do parser
    // EN: Maps each lexer token type to the corresponding parser symbol
    switch (t.type)
    {
        case END_OF_FILE:  return P::make_YYEOF(loc);

        case IDENTIFIER:   return P::make_IDENTIFIER(t.lexeme, loc);
        case INTEGER:      return P::make_INTEGER(t.lexeme, loc);
        case FLOAT:        return P::make_FLOAT(t.lexeme, loc);
        case STRING:       return P::make_STRING(t.lexeme, loc);

        case CODEX:        return P::make_CODEX(loc);
        case RITUS:        return P::make_RITUS(loc);
        case CYCLE:        return P::make_CYCLE(loc);
        case IF:           return P::make_IF(loc);
        case ELSE:         return P::make_ELSE(loc);
        case INITIATE:     return P::make_INITIATE(loc);
        case END_CODEX:    return P::make_END_CODEX(loc);
        case END_RITUS:    return P::make_END_RITUS(loc);
        case END_IF:       return P::make_END_IF(loc);
        case END_CYCLE:    return P::make_END_CYCLE(loc);
        case RETURN:       return P::make_RETURN(loc);
        case TRUE:         return P::make_TRUE(loc);
        case FALSE:        return P::make_FALSE(loc);
        case TYPE_INT:     return P::make_TYPE_INT(loc);
        case TYPE_FLOAT:   return P::make_TYPE_FLOAT(loc);
        case TYPE_STRING:  return P::make_TYPE_STRING(loc);
        case TYPE_BOOLEAN: return P::make_TYPE_BOOLEAN(loc);
        case PRINT:        return P::make_PRINT(loc);
        case VOID:         return P::make_VOID(loc);

        case ASSIGN:       return P::make_ASSIGN(loc);
        case PLUS:         return P::make_PLUS(loc);
        case MINUS:        return P::make_MINUS(loc);
        case MULT:         return P::make_MULT(loc);
        case DIV:          return P::make_DIV(loc);
        case EQ:           return P::make_EQ(loc);
        case NEQ:          return P::make_NEQ(loc);
        case GT:           return P::make_GT(loc);
        case LT:           return P::make_LT(loc);
        case GTE:          return P::make_GTE(loc);
        case LTE:          return P::make_LTE(loc);
        case NOT:          return P::make_NOT(loc);
        case AND:          return P::make_AND(loc);
        case OR:           return P::make_OR(loc);

        case LPAR:         return P::make_LPAR(loc);
        case RPAR:         return P::make_RPAR(loc);
        case COMMA:        return P::make_COMMA(loc);
        case LBRACE:       return P::make_LBRACE(loc);
        case RBRACE:       return P::make_RBRACE(loc);
        case LBRACK:       return P::make_LBRACK(loc);
        case RBRACK:       return P::make_RBRACK(loc);
        case NEWLINE:      return P::make_NEWLINE(loc);
    }

    return P::make_YYEOF(P::location_type{});
}
