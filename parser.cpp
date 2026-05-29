// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 22 "parser.y"

    #include "lexer_bridge.h"
    extern Arena    g_arena;
    extern Program* g_program;
    // Forward-declare the yylex function implemented in lexer_bridge.cpp
    yy::parser::symbol_type yylex();

#line 54 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 146 "parser.cpp"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_or_expression: // logical_or_expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.YY_MOVE_OR_COPY< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_declaration: // function_declaration
        value.YY_MOVE_OR_COPY< FuncDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter: // parameter
        value.YY_MOVE_OR_COPY< Param > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_variable_declaration: // variable_declaration
      case symbol_kind::S_assignment_statement: // assignment_statement
      case symbol_kind::S_print_statement: // print_statement
      case symbol_kind::S_function_call_stmt: // function_call_stmt
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
        value.YY_MOVE_OR_COPY< Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return_type: // return_type
      case symbol_kind::S_value_type: // value_type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_STRING: // "string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_initializer: // array_initializer
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_argument_list: // argument_list
        value.YY_MOVE_OR_COPY< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_global_sequence: // global_sequence
        value.YY_MOVE_OR_COPY< std::vector<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.YY_MOVE_OR_COPY< std::vector<Param> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_sequence: // statement_sequence
      case symbol_kind::S_else_clause: // else_clause
        value.YY_MOVE_OR_COPY< std::vector<Stmt*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_or_expression: // logical_or_expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.move< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_declaration: // function_declaration
        value.move< FuncDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter: // parameter
        value.move< Param > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_variable_declaration: // variable_declaration
      case symbol_kind::S_assignment_statement: // assignment_statement
      case symbol_kind::S_print_statement: // print_statement
      case symbol_kind::S_function_call_stmt: // function_call_stmt
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
        value.move< Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return_type: // return_type
      case symbol_kind::S_value_type: // value_type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_STRING: // "string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_initializer: // array_initializer
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_argument_list: // argument_list
        value.move< std::vector<Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_global_sequence: // global_sequence
        value.move< std::vector<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<Param> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_sequence: // statement_sequence
      case symbol_kind::S_else_clause: // else_clause
        value.move< std::vector<Stmt*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_or_expression: // logical_or_expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.copy< Expr* > (that.value);
        break;

      case symbol_kind::S_function_declaration: // function_declaration
        value.copy< FuncDecl* > (that.value);
        break;

      case symbol_kind::S_parameter: // parameter
        value.copy< Param > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Program* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_variable_declaration: // variable_declaration
      case symbol_kind::S_assignment_statement: // assignment_statement
      case symbol_kind::S_print_statement: // print_statement
      case symbol_kind::S_function_call_stmt: // function_call_stmt
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
        value.copy< Stmt* > (that.value);
        break;

      case symbol_kind::S_return_type: // return_type
      case symbol_kind::S_value_type: // value_type
        value.copy< Type > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_STRING: // "string"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_array_initializer: // array_initializer
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_argument_list: // argument_list
        value.copy< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_global_sequence: // global_sequence
        value.copy< std::vector<Node*> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< std::vector<Param> > (that.value);
        break;

      case symbol_kind::S_statement_sequence: // statement_sequence
      case symbol_kind::S_else_clause: // else_clause
        value.copy< std::vector<Stmt*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_or_expression: // logical_or_expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_primary_expression: // primary_expression
        value.move< Expr* > (that.value);
        break;

      case symbol_kind::S_function_declaration: // function_declaration
        value.move< FuncDecl* > (that.value);
        break;

      case symbol_kind::S_parameter: // parameter
        value.move< Param > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_variable_declaration: // variable_declaration
      case symbol_kind::S_assignment_statement: // assignment_statement
      case symbol_kind::S_print_statement: // print_statement
      case symbol_kind::S_function_call_stmt: // function_call_stmt
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
        value.move< Stmt* > (that.value);
        break;

      case symbol_kind::S_return_type: // return_type
      case symbol_kind::S_value_type: // value_type
        value.move< Type > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_STRING: // "string"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_array_initializer: // array_initializer
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_argument_list: // argument_list
        value.move< std::vector<Expr*> > (that.value);
        break;

      case symbol_kind::S_global_sequence: // global_sequence
        value.move< std::vector<Node*> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::vector<Param> > (that.value);
        break;

      case symbol_kind::S_statement_sequence: // statement_sequence
      case symbol_kind::S_else_clause: // else_clause
        value.move< std::vector<Stmt*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_logical_or_expression: // logical_or_expression
      case symbol_kind::S_logical_and_expression: // logical_and_expression
      case symbol_kind::S_equality_expression: // equality_expression
      case symbol_kind::S_relational_expression: // relational_expression
      case symbol_kind::S_additive_expression: // additive_expression
      case symbol_kind::S_multiplicative_expression: // multiplicative_expression
      case symbol_kind::S_unary_expression: // unary_expression
      case symbol_kind::S_primary_expression: // primary_expression
        yylhs.value.emplace< Expr* > ();
        break;

      case symbol_kind::S_function_declaration: // function_declaration
        yylhs.value.emplace< FuncDecl* > ();
        break;

      case symbol_kind::S_parameter: // parameter
        yylhs.value.emplace< Param > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Program* > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_variable_declaration: // variable_declaration
      case symbol_kind::S_assignment_statement: // assignment_statement
      case symbol_kind::S_print_statement: // print_statement
      case symbol_kind::S_function_call_stmt: // function_call_stmt
      case symbol_kind::S_return_statement: // return_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_while_statement: // while_statement
        yylhs.value.emplace< Stmt* > ();
        break;

      case symbol_kind::S_return_type: // return_type
      case symbol_kind::S_value_type: // value_type
        yylhs.value.emplace< Type > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_STRING: // "string"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_array_initializer: // array_initializer
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_argument_list: // argument_list
        yylhs.value.emplace< std::vector<Expr*> > ();
        break;

      case symbol_kind::S_global_sequence: // global_sequence
        yylhs.value.emplace< std::vector<Node*> > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        yylhs.value.emplace< std::vector<Param> > ();
        break;

      case symbol_kind::S_statement_sequence: // statement_sequence
      case symbol_kind::S_else_clause: // else_clause
        yylhs.value.emplace< std::vector<Stmt*> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: "codex" "initiate" "newline" global_sequence "codexterminate"
#line 118 "parser.y"
    {
        auto* p   = g_arena.make<Program>();
        p->loc    = { yystack_[4].location.begin.line, yystack_[4].location.begin.column };
        p->items  = std::move(yystack_[1].value.as < std::vector<Node*> > ());
        g_program = p;
        yylhs.value.as < Program* > () = p;
    }
#line 886 "parser.cpp"
    break;

  case 3: // program: "codex" "initiate" "newline" global_sequence "codexterminate" "newline"
#line 126 "parser.y"
    {
        auto* p   = g_arena.make<Program>();
        p->loc    = { yystack_[5].location.begin.line, yystack_[5].location.begin.column };
        p->items  = std::move(yystack_[2].value.as < std::vector<Node*> > ());
        g_program = p;
        yylhs.value.as < Program* > () = p;
    }
#line 898 "parser.cpp"
    break;

  case 4: // global_sequence: %empty
#line 140 "parser.y"
                                             { yylhs.value.as < std::vector<Node*> > () = {}; }
#line 904 "parser.cpp"
    break;

  case 5: // global_sequence: global_sequence "newline"
#line 141 "parser.y"
                                             { yylhs.value.as < std::vector<Node*> > () = std::move(yystack_[1].value.as < std::vector<Node*> > ()); }
#line 910 "parser.cpp"
    break;

  case 6: // global_sequence: global_sequence statement "newline"
#line 142 "parser.y"
                                             { yystack_[2].value.as < std::vector<Node*> > ().push_back(yystack_[1].value.as < Stmt* > ()); yylhs.value.as < std::vector<Node*> > () = std::move(yystack_[2].value.as < std::vector<Node*> > ()); }
#line 916 "parser.cpp"
    break;

  case 7: // global_sequence: global_sequence function_declaration "newline"
#line 143 "parser.y"
                                                 { yystack_[2].value.as < std::vector<Node*> > ().push_back(yystack_[1].value.as < FuncDecl* > ()); yylhs.value.as < std::vector<Node*> > () = std::move(yystack_[2].value.as < std::vector<Node*> > ()); }
#line 922 "parser.cpp"
    break;

  case 8: // statement_sequence: %empty
#line 147 "parser.y"
                                             { yylhs.value.as < std::vector<Stmt*> > () = {}; }
#line 928 "parser.cpp"
    break;

  case 9: // statement_sequence: statement_sequence "newline"
#line 148 "parser.y"
                                            { yylhs.value.as < std::vector<Stmt*> > () = std::move(yystack_[1].value.as < std::vector<Stmt*> > ()); }
#line 934 "parser.cpp"
    break;

  case 10: // statement_sequence: statement_sequence statement "newline"
#line 149 "parser.y"
                                            { yystack_[2].value.as < std::vector<Stmt*> > ().push_back(yystack_[1].value.as < Stmt* > ()); yylhs.value.as < std::vector<Stmt*> > () = std::move(yystack_[2].value.as < std::vector<Stmt*> > ()); }
#line 940 "parser.cpp"
    break;

  case 11: // statement: variable_declaration
#line 157 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 946 "parser.cpp"
    break;

  case 12: // statement: assignment_statement
#line 158 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 952 "parser.cpp"
    break;

  case 13: // statement: print_statement
#line 159 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 958 "parser.cpp"
    break;

  case 14: // statement: function_call_stmt
#line 160 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 964 "parser.cpp"
    break;

  case 15: // statement: return_statement
#line 161 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 970 "parser.cpp"
    break;

  case 16: // statement: if_statement
#line 162 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 976 "parser.cpp"
    break;

  case 17: // statement: while_statement
#line 163 "parser.y"
                           { yylhs.value.as < Stmt* > () = yystack_[0].value.as < Stmt* > (); }
#line 982 "parser.cpp"
    break;

  case 18: // variable_declaration: value_type "identifier"
#line 168 "parser.y"
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->decl_type = yystack_[1].value.as < Type > ();  n->name = yystack_[0].value.as < std::string > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 993 "parser.cpp"
    break;

  case 19: // variable_declaration: value_type "identifier" "=" expression
#line 175 "parser.y"
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->decl_type = yystack_[3].value.as < Type > ();  n->name = yystack_[2].value.as < std::string > ();  n->init = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 1004 "parser.cpp"
    break;

  case 20: // variable_declaration: value_type "identifier" "[" "integer" "]"
#line 182 "parser.y"
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { yystack_[3].location.begin.line, yystack_[3].location.begin.column };
        n->decl_type = yystack_[4].value.as < Type > ();  n->name = yystack_[3].value.as < std::string > ();
        n->array_size = std::stoi(yystack_[1].value.as < std::string > ());
        n->decl_type.is_array   = true;
        n->decl_type.array_size = n->array_size;
        yylhs.value.as < Stmt* > () = n;
    }
#line 1018 "parser.cpp"
    break;

  case 21: // variable_declaration: value_type "identifier" "[" "integer" "]" "=" array_initializer
#line 192 "parser.y"
    {
        auto* n = g_arena.make<VarDecl>();
        n->loc = { yystack_[5].location.begin.line, yystack_[5].location.begin.column };
        n->decl_type = yystack_[6].value.as < Type > ();  n->name = yystack_[5].value.as < std::string > ();
        n->array_size = std::stoi(yystack_[3].value.as < std::string > ());
        n->decl_type.is_array   = true;
        n->decl_type.array_size = n->array_size;
        n->array_init = std::move(yystack_[0].value.as < std::vector<Expr*> > ());
        yylhs.value.as < Stmt* > () = n;
    }
#line 1033 "parser.cpp"
    break;

  case 22: // array_initializer: "{" "}"
#line 205 "parser.y"
                                    { yylhs.value.as < std::vector<Expr*> > () = {}; }
#line 1039 "parser.cpp"
    break;

  case 23: // array_initializer: "{" expression_list "}"
#line 206 "parser.y"
                                    { yylhs.value.as < std::vector<Expr*> > () = std::move(yystack_[1].value.as < std::vector<Expr*> > ()); }
#line 1045 "parser.cpp"
    break;

  case 24: // expression_list: expression
#line 210 "parser.y"
                                    { yylhs.value.as < std::vector<Expr*> > () = { yystack_[0].value.as < Expr* > () }; }
#line 1051 "parser.cpp"
    break;

  case 25: // expression_list: expression_list "," expression
#line 211 "parser.y"
                                     { yystack_[2].value.as < std::vector<Expr*> > ().push_back(yystack_[0].value.as < Expr* > ()); yylhs.value.as < std::vector<Expr*> > () = std::move(yystack_[2].value.as < std::vector<Expr*> > ()); }
#line 1057 "parser.cpp"
    break;

  case 26: // assignment_statement: "identifier" "=" expression
#line 216 "parser.y"
    {
        auto* n = g_arena.make<AssignStmt>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->name = yystack_[2].value.as < std::string > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 1068 "parser.cpp"
    break;

  case 27: // assignment_statement: "identifier" "[" expression "]" "=" expression
#line 223 "parser.y"
    {
        auto* n = g_arena.make<AssignStmt>();
        n->loc = { yystack_[5].location.begin.line, yystack_[5].location.begin.column };
        n->name = yystack_[5].value.as < std::string > ();  n->index = yystack_[3].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 1079 "parser.cpp"
    break;

  case 28: // print_statement: "vox" "(" expression ")"
#line 233 "parser.y"
    {
        auto* n = g_arena.make<PrintStmt>();
        n->loc = { yystack_[3].location.begin.line, yystack_[3].location.begin.column };
        n->arg = yystack_[1].value.as < Expr* > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 1090 "parser.cpp"
    break;

  case 29: // function_call_stmt: "identifier" "(" ")"
#line 244 "parser.y"
    {
        auto* c = g_arena.make<CallExpr>();
        c->loc  = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        c->name = yystack_[2].value.as < std::string > ();
        auto* n = g_arena.make<CallStmt>();
        n->loc  = c->loc;  n->call = c;
        yylhs.value.as < Stmt* > () = n;
    }
#line 1103 "parser.cpp"
    break;

  case 30: // function_call_stmt: "identifier" "(" argument_list ")"
#line 253 "parser.y"
    {
        auto* c = g_arena.make<CallExpr>();
        c->loc  = { yystack_[3].location.begin.line, yystack_[3].location.begin.column };
        c->name = yystack_[3].value.as < std::string > ();  c->args = std::move(yystack_[1].value.as < std::vector<Expr*> > ());
        auto* n = g_arena.make<CallStmt>();
        n->loc  = c->loc;  n->call = c;
        yylhs.value.as < Stmt* > () = n;
    }
#line 1116 "parser.cpp"
    break;

  case 31: // return_statement: "transmit"
#line 265 "parser.y"
    {
        auto* n = g_arena.make<ReturnStmt>();
        n->loc = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        yylhs.value.as < Stmt* > () = n;
    }
#line 1126 "parser.cpp"
    break;

  case 32: // return_statement: "transmit" expression
#line 271 "parser.y"
    {
        auto* n = g_arena.make<ReturnStmt>();
        n->loc   = { yystack_[1].location.begin.line, yystack_[1].location.begin.column };
        n->value = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Stmt* > () = n;
    }
#line 1137 "parser.cpp"
    break;

  case 33: // if_statement: "verify" expression "newline" statement_sequence "verifyterminate"
#line 281 "parser.y"
    {
        auto* n = g_arena.make<IfStmt>();
        n->loc      = { yystack_[4].location.begin.line, yystack_[4].location.begin.column };
        n->cond     = yystack_[3].value.as < Expr* > ();
        n->then_body = std::move(yystack_[1].value.as < std::vector<Stmt*> > ());
        yylhs.value.as < Stmt* > () = n;
    }
#line 1149 "parser.cpp"
    break;

  case 34: // if_statement: "verify" expression "newline" statement_sequence else_clause "verifyterminate"
#line 289 "parser.y"
    {
        auto* n = g_arena.make<IfStmt>();
        n->loc      = { yystack_[5].location.begin.line, yystack_[5].location.begin.column };
        n->cond     = yystack_[4].value.as < Expr* > ();
        n->then_body = std::move(yystack_[2].value.as < std::vector<Stmt*> > ());
        n->else_body = std::move(yystack_[1].value.as < std::vector<Stmt*> > ());
        yylhs.value.as < Stmt* > () = n;
    }
#line 1162 "parser.cpp"
    break;

  case 35: // else_clause: "fallback" "newline" statement_sequence
#line 300 "parser.y"
                                     { yylhs.value.as < std::vector<Stmt*> > () = std::move(yystack_[0].value.as < std::vector<Stmt*> > ()); }
#line 1168 "parser.cpp"
    break;

  case 36: // while_statement: "cycle" expression "newline" statement_sequence "cycleterminate"
#line 305 "parser.y"
    {
        auto* n = g_arena.make<WhileStmt>();
        n->loc  = { yystack_[4].location.begin.line, yystack_[4].location.begin.column };
        n->cond = yystack_[3].value.as < Expr* > ();
        n->body = std::move(yystack_[1].value.as < std::vector<Stmt*> > ());
        yylhs.value.as < Stmt* > () = n;
    }
#line 1180 "parser.cpp"
    break;

  case 37: // function_declaration: "ritus" return_type "identifier" "(" ")" "initiate" "newline" statement_sequence "ritusterminate"
#line 320 "parser.y"
    {
        auto* f = g_arena.make<FuncDecl>();
        f->loc         = { yystack_[6].location.begin.line, yystack_[6].location.begin.column };
        f->return_type  = yystack_[7].value.as < Type > ();
        f->name        = yystack_[6].value.as < std::string > ();
        f->body        = std::move(yystack_[1].value.as < std::vector<Stmt*> > ());
        yylhs.value.as < FuncDecl* > () = f;
    }
#line 1193 "parser.cpp"
    break;

  case 38: // function_declaration: "ritus" return_type "identifier" "(" parameter_list ")" "initiate" "newline" statement_sequence "ritusterminate"
#line 329 "parser.y"
    {
        auto* f = g_arena.make<FuncDecl>();
        f->loc         = { yystack_[7].location.begin.line, yystack_[7].location.begin.column };
        f->return_type  = yystack_[8].value.as < Type > ();
        f->name        = yystack_[7].value.as < std::string > ();
        f->params      = std::move(yystack_[5].value.as < std::vector<Param> > ());
        f->body        = std::move(yystack_[1].value.as < std::vector<Stmt*> > ());
        yylhs.value.as < FuncDecl* > () = f;
    }
#line 1207 "parser.cpp"
    break;

  case 39: // parameter_list: parameter
#line 341 "parser.y"
                                     { yylhs.value.as < std::vector<Param> > () = { yystack_[0].value.as < Param > () }; }
#line 1213 "parser.cpp"
    break;

  case 40: // parameter_list: parameter_list "," parameter
#line 342 "parser.y"
                                     { yystack_[2].value.as < std::vector<Param> > ().push_back(yystack_[0].value.as < Param > ()); yylhs.value.as < std::vector<Param> > () = std::move(yystack_[2].value.as < std::vector<Param> > ()); }
#line 1219 "parser.cpp"
    break;

  case 41: // parameter: value_type "identifier"
#line 347 "parser.y"
    {
        yylhs.value.as < Param > () = Param{ yystack_[1].value.as < Type > (), yystack_[0].value.as < std::string > (), false };
    }
#line 1227 "parser.cpp"
    break;

  case 42: // parameter: value_type "identifier" "[" "]"
#line 351 "parser.y"
    {
        Type t = yystack_[3].value.as < Type > ();  t.is_array = true;
        yylhs.value.as < Param > () = Param{ t, yystack_[2].value.as < std::string > (), true };
    }
#line 1236 "parser.cpp"
    break;

  case 43: // return_type: value_type
#line 362 "parser.y"
                           { yylhs.value.as < Type > () = yystack_[0].value.as < Type > (); }
#line 1242 "parser.cpp"
    break;

  case 44: // return_type: value_type "[" "]"
#line 364 "parser.y"
    {
        Type t = yystack_[2].value.as < Type > ();  t.is_array = true;
        yylhs.value.as < Type > () = t;
    }
#line 1251 "parser.cpp"
    break;

  case 45: // return_type: "nullrite"
#line 368 "parser.y"
                           { yylhs.value.as < Type > () = mk_void(); }
#line 1257 "parser.cpp"
    break;

  case 46: // value_type: "numerus"
#line 372 "parser.y"
                 { yylhs.value.as < Type > () = mk_int();    }
#line 1263 "parser.cpp"
    break;

  case 47: // value_type: "flux"
#line 373 "parser.y"
                 { yylhs.value.as < Type > () = mk_float();  }
#line 1269 "parser.cpp"
    break;

  case 48: // value_type: "veritas"
#line 374 "parser.y"
                 { yylhs.value.as < Type > () = mk_bool();   }
#line 1275 "parser.cpp"
    break;

  case 49: // value_type: "scriptum"
#line 375 "parser.y"
                 { yylhs.value.as < Type > () = mk_string(); }
#line 1281 "parser.cpp"
    break;

  case 50: // argument_list: expression
#line 383 "parser.y"
                                    { yylhs.value.as < std::vector<Expr*> > () = { yystack_[0].value.as < Expr* > () }; }
#line 1287 "parser.cpp"
    break;

  case 51: // argument_list: argument_list "," expression
#line 384 "parser.y"
                                    { yystack_[2].value.as < std::vector<Expr*> > ().push_back(yystack_[0].value.as < Expr* > ()); yylhs.value.as < std::vector<Expr*> > () = std::move(yystack_[2].value.as < std::vector<Expr*> > ()); }
#line 1293 "parser.cpp"
    break;

  case 52: // expression: logical_or_expression
#line 391 "parser.y"
                                  { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1299 "parser.cpp"
    break;

  case 53: // logical_or_expression: logical_and_expression
#line 394 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1305 "parser.cpp"
    break;

  case 54: // logical_or_expression: logical_or_expression "divergence" logical_and_expression
#line 396 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op  = OpKind::Or;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1316 "parser.cpp"
    break;

  case 55: // logical_and_expression: equality_expression
#line 405 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1322 "parser.cpp"
    break;

  case 56: // logical_and_expression: logical_and_expression "conjunction" equality_expression
#line 407 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op  = OpKind::And;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1333 "parser.cpp"
    break;

  case 57: // equality_expression: relational_expression
#line 416 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1339 "parser.cpp"
    break;

  case 58: // equality_expression: equality_expression "==" relational_expression
#line 418 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op  = OpKind::Eq;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1350 "parser.cpp"
    break;

  case 59: // equality_expression: equality_expression "!=" relational_expression
#line 425 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op  = OpKind::Neq;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1361 "parser.cpp"
    break;

  case 60: // relational_expression: additive_expression
#line 434 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1367 "parser.cpp"
    break;

  case 61: // relational_expression: relational_expression ">" additive_expression
#line 436 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Gt;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1378 "parser.cpp"
    break;

  case 62: // relational_expression: relational_expression "<" additive_expression
#line 443 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Lt;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1389 "parser.cpp"
    break;

  case 63: // relational_expression: relational_expression ">=" additive_expression
#line 450 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Gte;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1400 "parser.cpp"
    break;

  case 64: // relational_expression: relational_expression "<=" additive_expression
#line 457 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Lte;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1411 "parser.cpp"
    break;

  case 65: // additive_expression: multiplicative_expression
#line 466 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1417 "parser.cpp"
    break;

  case 66: // additive_expression: additive_expression "+" multiplicative_expression
#line 468 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Add;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1428 "parser.cpp"
    break;

  case 67: // additive_expression: additive_expression "-" multiplicative_expression
#line 475 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Sub;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1439 "parser.cpp"
    break;

  case 68: // multiplicative_expression: unary_expression
#line 484 "parser.y"
                                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1445 "parser.cpp"
    break;

  case 69: // multiplicative_expression: multiplicative_expression "*" unary_expression
#line 486 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Mul;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1456 "parser.cpp"
    break;

  case 70: // multiplicative_expression: multiplicative_expression "/" unary_expression
#line 493 "parser.y"
    {
        auto* n = g_arena.make<BinaryExpr>();
        n->loc = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->op = OpKind::Div;  n->lhs = yystack_[2].value.as < Expr* > ();  n->rhs = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1467 "parser.cpp"
    break;

  case 71: // unary_expression: primary_expression
#line 502 "parser.y"
                                        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1473 "parser.cpp"
    break;

  case 72: // unary_expression: "-" unary_expression
#line 504 "parser.y"
    {
        auto* n = g_arena.make<UnaryExpr>();
        n->loc     = { yystack_[1].location.begin.line, yystack_[1].location.begin.column };
        n->op      = OpKind::Neg;  n->operand = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1484 "parser.cpp"
    break;

  case 73: // unary_expression: "!" unary_expression
#line 511 "parser.y"
    {
        auto* n = g_arena.make<UnaryExpr>();
        n->loc     = { yystack_[1].location.begin.line, yystack_[1].location.begin.column };
        n->op      = OpKind::Not;  n->operand = yystack_[0].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1495 "parser.cpp"
    break;

  case 74: // primary_expression: "integer"
#line 521 "parser.y"
    {
        auto* n = g_arena.make<IntLit>();
        n->loc   = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->value = std::stol(yystack_[0].value.as < std::string > ());
        yylhs.value.as < Expr* > () = n;
    }
#line 1506 "parser.cpp"
    break;

  case 75: // primary_expression: "float"
#line 528 "parser.y"
    {
        auto* n = g_arena.make<FloatLit>();
        n->loc   = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->value = std::stod(yystack_[0].value.as < std::string > ());
        yylhs.value.as < Expr* > () = n;
    }
#line 1517 "parser.cpp"
    break;

  case 76: // primary_expression: "string"
#line 535 "parser.y"
    {
        auto* n = g_arena.make<StringLit>();
        n->loc   = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->value = yystack_[0].value.as < std::string > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1528 "parser.cpp"
    break;

  case 77: // primary_expression: "verum"
#line 542 "parser.y"
    {
        auto* n = g_arena.make<BoolLit>();
        n->loc   = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->value = true;
        yylhs.value.as < Expr* > () = n;
    }
#line 1539 "parser.cpp"
    break;

  case 78: // primary_expression: "falsum"
#line 549 "parser.y"
    {
        auto* n = g_arena.make<BoolLit>();
        n->loc   = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->value = false;
        yylhs.value.as < Expr* > () = n;
    }
#line 1550 "parser.cpp"
    break;

  case 79: // primary_expression: "identifier"
#line 556 "parser.y"
    {
        auto* n = g_arena.make<VarRef>();
        n->loc  = { yystack_[0].location.begin.line, yystack_[0].location.begin.column };
        n->name = yystack_[0].value.as < std::string > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1561 "parser.cpp"
    break;

  case 80: // primary_expression: "identifier" "(" ")"
#line 564 "parser.y"
    {
        auto* n = g_arena.make<CallExpr>();
        n->loc  = { yystack_[2].location.begin.line, yystack_[2].location.begin.column };
        n->name = yystack_[2].value.as < std::string > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1572 "parser.cpp"
    break;

  case 81: // primary_expression: "identifier" "(" argument_list ")"
#line 571 "parser.y"
    {
        auto* n = g_arena.make<CallExpr>();
        n->loc  = { yystack_[3].location.begin.line, yystack_[3].location.begin.column };
        n->name = yystack_[3].value.as < std::string > ();  n->args = std::move(yystack_[1].value.as < std::vector<Expr*> > ());
        yylhs.value.as < Expr* > () = n;
    }
#line 1583 "parser.cpp"
    break;

  case 82: // primary_expression: "identifier" "[" expression "]"
#line 579 "parser.y"
    {
        auto* n = g_arena.make<IndexExpr>();
        n->loc   = { yystack_[3].location.begin.line, yystack_[3].location.begin.column };
        n->name  = yystack_[3].value.as < std::string > ();  n->index = yystack_[1].value.as < Expr* > ();
        yylhs.value.as < Expr* > () = n;
    }
#line 1594 "parser.cpp"
    break;

  case 83: // primary_expression: "(" expression ")"
#line 585 "parser.y"
                          { yylhs.value.as < Expr* > () = yystack_[1].value.as < Expr* > (); }
#line 1600 "parser.cpp"
    break;


#line 1604 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "identifier", "integer",
  "float", "string", "codex", "ritus", "cycle", "verify", "fallback",
  "initiate", "codexterminate", "ritusterminate", "verifyterminate",
  "cycleterminate", "transmit", "verum", "falsum", "numerus", "flux",
  "scriptum", "veritas", "vox", "nullrite", "=", "+", "-", "*", "/", "==",
  "!=", ">", "<", ">=", "<=", "!", "conjunction", "divergence", "(", ")",
  ",", "{", "}", "[", "]", "newline", "$accept", "program",
  "global_sequence", "statement_sequence", "statement",
  "variable_declaration", "array_initializer", "expression_list",
  "assignment_statement", "print_statement", "function_call_stmt",
  "return_statement", "if_statement", "else_clause", "while_statement",
  "function_declaration", "parameter_list", "parameter", "return_type",
  "value_type", "argument_list", "expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -82;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      -2,    -3,    18,   -15,   -82,   -82,     4,    -7,    88,   202,
     202,   -11,   202,   -82,   -82,   -82,   -82,    -1,   -82,     1,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,     3,    43,   202,
     162,   202,   -82,    54,    23,     9,   -82,   -82,   -82,   -82,
     -82,   202,   202,   202,    47,    26,    51,   -16,   103,    33,
      42,   -82,   -82,    52,   -82,   -82,   202,   -82,   -82,    19,
     -82,   -82,    38,   -82,    39,    66,    74,   182,   202,   -82,
     -82,    80,   -82,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   -82,    83,   202,   118,   -82,
     202,    99,   191,   -82,   -82,    41,    96,   -82,    53,    51,
     -16,   103,   103,    33,    33,    33,    33,    42,    42,   -82,
     -82,    20,   -82,   -82,    97,   -82,   202,   132,    46,   -82,
     143,   -82,   -82,   -82,   -82,   100,   102,   -82,   135,   144,
     -82,   122,   159,    94,   129,   -82,   -82,   -82,   133,   -82,
     128,   -82,   137,   131,   154,   -82,    81,   -82,   -82,   -82,
     -36,   -82,   -82,   109,   202,   -82,   -82,   -82
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     1,     4,     0,     0,     0,     0,
       0,     2,    31,    46,    47,    49,    48,     0,     5,     0,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,     0,    45,     0,    43,    79,    74,    75,    76,    77,
      78,     0,     0,     0,     0,    52,    53,    55,    57,    60,
      65,    68,    71,     0,     3,    32,     0,     6,     7,    18,
      26,    29,     0,    50,     0,     0,     0,     0,     0,    72,
      73,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     0,    30,
       0,     0,     0,    44,    80,     0,     0,    83,     0,    54,
      56,    58,    59,    61,    62,    63,    64,    66,    67,    69,
      70,     0,    28,    19,     0,    51,     0,     0,     0,    39,
       0,    81,    82,    36,     9,     0,     0,    33,     0,    20,
      27,     0,     0,     0,    41,    10,     8,    34,     0,     8,
       0,    40,     0,    35,     0,    21,     0,     8,    42,    22,
       0,    24,    37,     0,     0,    23,    38,    25
  };

  const short
  parser::yypgoto_[] =
  {
     -82,   -82,   -82,   -81,   171,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,    56,   -82,    -6,
     112,    -9,   -82,   111,   119,    17,    84,    15,   -31,   -82
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     6,    98,   125,    20,   145,   150,    21,    22,
      23,    24,    25,   128,    26,    27,   118,   119,    33,    28,
      62,    63,    45,    46,    47,    48,    49,    50,    51,    52
  };

  const unsigned char
  parser::yytable_[] =
  {
      44,    53,    34,    55,   111,     1,   154,     7,   155,     3,
      69,    70,     8,     9,    10,    75,    76,    11,     4,    29,
      60,    12,    64,     7,    13,    14,    15,    16,    17,     9,
      10,   126,     5,    30,    71,   127,    54,    12,    31,    56,
      13,    14,    15,    16,    17,    87,    59,    86,    57,    67,
      58,    18,   109,   110,    68,   143,     7,    65,   146,    96,
      81,    82,     9,    10,    88,    73,   153,   124,    66,   123,
      12,    83,    84,    13,    14,    15,    16,    17,   113,    89,
      90,   115,   121,    90,     7,    91,   120,   132,   133,    74,
       9,    10,   101,   102,    72,   152,   107,   108,    12,    85,
     124,    13,    14,    15,    16,    17,    92,   130,    13,    14,
      15,    16,     7,    32,    13,    14,    15,    16,     9,    10,
      93,    97,   114,   156,   112,   116,    12,   120,   124,    13,
      14,    15,    16,    17,     7,   151,    77,    78,    79,    80,
       9,    10,   122,   129,   131,   157,   134,   135,    12,   136,
     137,    13,    14,    15,    16,    17,   124,    35,    36,    37,
      38,   103,   104,   105,   106,    35,    36,    37,    38,   139,
     138,   140,    39,    40,   142,   147,   144,    19,   124,    95,
      39,    40,    41,   148,    99,    35,    36,    37,    38,   141,
      41,    42,     0,   100,    43,     0,     0,     0,   149,    42,
      39,    40,    43,    61,     0,    35,    36,    37,    38,     0,
      41,    13,    14,    15,    16,     0,     0,     0,     0,    42,
      39,    40,    43,    94,     0,     0,     0,     0,     0,     0,
      41,     0,   117,     0,     0,     0,     0,     0,     0,    42,
       0,     0,    43
  };

  const short
  parser::yycheck_[] =
  {
       9,    10,     8,    12,    85,     7,    42,     3,    44,    12,
      41,    42,     8,     9,    10,    31,    32,    13,     0,    26,
      29,    17,    31,     3,    20,    21,    22,    23,    24,     9,
      10,    11,    47,    40,    43,    15,    47,    17,    45,    40,
      20,    21,    22,    23,    24,    26,     3,    56,    47,    40,
      47,    47,    83,    84,    45,   136,     3,     3,   139,    68,
      27,    28,     9,    10,    45,    39,   147,    47,    45,    16,
      17,    29,    30,    20,    21,    22,    23,    24,    87,    41,
      42,    90,    41,    42,     3,    46,    92,    41,    42,    38,
       9,    10,    75,    76,    47,    14,    81,    82,    17,    47,
      47,    20,    21,    22,    23,    24,    40,   116,    20,    21,
      22,    23,     3,    25,    20,    21,    22,    23,     9,    10,
      46,    41,     4,    14,    41,    26,    17,   133,    47,    20,
      21,    22,    23,    24,     3,   144,    33,    34,    35,    36,
       9,    10,    46,    46,    12,   154,     3,    47,    17,    47,
      15,    20,    21,    22,    23,    24,    47,     3,     4,     5,
       6,    77,    78,    79,    80,     3,     4,     5,     6,    47,
      26,    12,    18,    19,    45,    47,    43,     6,    47,    67,
      18,    19,    28,    46,    73,     3,     4,     5,     6,   133,
      28,    37,    -1,    74,    40,    -1,    -1,    -1,    44,    37,
      18,    19,    40,    41,    -1,     3,     4,     5,     6,    -1,
      28,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    37,
      18,    19,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    40
  };

  const signed char
  parser::yystos_[] =
  {
       0,     7,    49,    12,     0,    47,    50,     3,     8,     9,
      10,    13,    17,    20,    21,    22,    23,    24,    47,    52,
      53,    56,    57,    58,    59,    60,    62,    63,    67,    26,
      40,    45,    25,    66,    67,     3,     4,     5,     6,    18,
      19,    28,    37,    40,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    69,    47,    69,    40,    47,    47,     3,
      69,    41,    68,    69,    69,     3,    45,    40,    45,    76,
      76,    69,    47,    39,    38,    31,    32,    33,    34,    35,
      36,    27,    28,    29,    30,    47,    69,    26,    45,    41,
      42,    46,    40,    46,    41,    68,    69,    41,    51,    71,
      72,    73,    73,    74,    74,    74,    74,    75,    75,    76,
      76,    51,    41,    69,     4,    69,    26,    41,    64,    65,
      67,    41,    46,    16,    47,    52,    11,    15,    61,    46,
      69,    12,    41,    42,     3,    47,    47,    15,    26,    47,
      12,    65,    45,    51,    43,    54,    51,    47,    46,    44,
      55,    69,    14,    51,    42,    44,    14,    69
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    48,    49,    49,    50,    50,    50,    50,    51,    51,
      51,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53,    53,    54,    54,    55,    55,    56,    56,    57,    58,
      58,    59,    59,    60,    60,    61,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    67,    67,
      68,    68,    69,    70,    70,    71,    71,    72,    72,    72,
      73,    73,    73,    73,    73,    74,    74,    74,    75,    75,
      75,    76,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     6,     0,     2,     3,     3,     0,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       5,     7,     2,     3,     1,     3,     3,     6,     4,     3,
       4,     1,     2,     5,     6,     3,     5,     9,    10,     1,
       3,     2,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       3,     4,     4,     3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   117,   117,   125,   140,   141,   142,   143,   147,   148,
     149,   157,   158,   159,   160,   161,   162,   163,   167,   174,
     181,   191,   205,   206,   210,   211,   215,   222,   232,   243,
     252,   264,   270,   280,   288,   300,   304,   319,   328,   341,
     342,   346,   350,   362,   363,   368,   372,   373,   374,   375,
     383,   384,   391,   394,   395,   405,   406,   416,   417,   424,
     434,   435,   442,   449,   456,   466,   467,   474,   484,   485,
     492,   502,   503,   510,   520,   527,   534,   541,   548,   555,
     563,   570,   578,   585
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2290 "parser.cpp"

#line 588 "parser.y"


/* ---- error handler ---- */
void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << "[ERROR::PARSE] :: MACHINE_SPIRIT_CONFUSED\n\n"
              << "SIGNAL :: " << msg
              << " at line " << loc.begin.line << " and column " << loc.begin.column << "\n\n"
              << "RECOVERY :: ENSURE CORRECT SYNTAX RITUALS\n";
}
