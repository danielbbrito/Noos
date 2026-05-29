#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include "lexer.h"
#include "lexer_bridge.h"
#include "parser.hh"
#include "ast.h"
#include "sema/analyzer.h"
#include "codegen.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: noos <file.noo> [--dump-ast] [--dump-tokens] [--no-sema] [--emit-cpp]\n";
        return 1;
    }

    const std::string file = argv[1];
    bool dump_ast    = false;
    bool dump_tokens = false;
    bool no_sema     = false;
    bool emit_cpp    = false;
    for (int i = 2; i < argc; ++i) {
        std::string f = argv[i];
        if (f == "--dump-ast")    dump_ast    = true;
        if (f == "--dump-tokens") dump_tokens = true;
        if (f == "--no-sema")     no_sema     = true;
        if (f == "--emit-cpp")    emit_cpp    = true;
    }

    // Scanner
    std::vector<Token> tokens;
    try {
        tokens = scan_source(file, dump_tokens);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    // Parse
    // PT: A ponte é necessária, pois o parser espera um token por vez e o scanner gera todos de uma vez
    // EN: The bridge is necessary because the parser processes one token at a time and the scanner outputs them all at once
    bridge_set_tokens(tokens);
    yy::parser parser;
    int parse_result = parser.parse();
    if (parse_result != 0 || !g_program) {
        return 1;
    }

    // PT: Imprime a árvore sintática, se requisitado
    // EN: Prints the syntax tree, if requested
    if (dump_ast) {
        print_ast(g_program);
        if (!emit_cpp && no_sema) return 0;
    }

    // Semantic analysis
    if (!no_sema) {
        SemanticAnalyzer sema;
        bool ok = sema.analyze(g_program);
        for (const auto& err : sema.errors())
            std::cerr << "[ERROR::SEMA] :: MACHINE_SPIRIT_HERETICAL\n\n"
                      << "SIGNAL :: " << err.message
                      << " at line " << err.loc.line << " and column " << err.loc.col << "\n\n"
                      << "RECOVERY :: REVIEW YOUR RITES OF DECLARATION\n\n";
        if (!ok) return 1;
    }

    CppEmitter emitter;
    std::string cpp_code = emitter.emit(g_program);

    // PT: Se --emit-cpp, apenas imprime o C++ e sai
    // EN: If --emit-cpp, just print the C++ and exit
    if (emit_cpp) {
        std::cout << cpp_code;
        return 0;
    }

    // PT: Deriva o nome do executável a partir do nome do arquivo fonte
    // EN: Derive the executable name from the source file name
    std::string output = file;
    size_t slash = output.rfind('/');
    if (slash == std::string::npos) slash = output.rfind('\\');
    if (slash != std::string::npos) output = output.substr(slash + 1);
    if (output.size() > 5 && output.substr(output.size() - 5) == ".noos")
        output = output.substr(0, output.size() - 5);

    // PT: Escreve o C++ num arquivo temporário, compila e apaga
    // EN: Write the C++ to a temp file, compile it, then delete it
    std::string tmp = (std::filesystem::temp_directory_path() / ("noos_" + output + ".cpp")).string();
    std::ofstream tmp_file(tmp);
    tmp_file << cpp_code;
    tmp_file.close();

    std::string cmd = "g++ -std=c++17 " + tmp + " -o " + output;
    int compile_result = std::system(cmd.c_str());
    std::remove(tmp.c_str());

    if (compile_result != 0) {
        std::cerr << "[ERROR::CODEGEN] :: MACHINE_SPIRIT_BROKEN\n\n"
                  << "SIGNAL :: C++ compilation failed\n\n"
                  << "RECOVERY :: USE --emit-cpp TO INSPECT THE GENERATED CODE\n";
        return 1;
    }

    std::cout << "RITUAL OF COMPILATION COMPLETED SUCCESSFULLY. PRAISE THE OMNISSIAH.\n";
    return 0;
}
