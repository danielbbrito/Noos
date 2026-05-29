CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall -Wno-unused-function -I.

# PT: Detecta o sistema operacional
# EN: Detect the operating system
ifeq ($(OS),Windows_NT)
    EXE     = .exe
    BINDIR  = C:/Windows/System32
    INSTALL = copy noos.exe $(BINDIR)/noos.exe
    UNINST  = del /f $(BINDIR)/noos.exe
    RM      = del /f
else
    EXE     =
    BINDIR  = /usr/local/bin
    INSTALL = sudo cp noos $(BINDIR)/noos
    UNINST  = sudo rm -f $(BINDIR)/noos
    RM      = rm -f
endif

SRCS = parser.cpp \
       lexer.cpp \
       lexer_bridge.cpp \
       ast.cpp \
       sema/scope.cpp \
       sema/analyzer.cpp \
       codegen.cpp \
       main.cpp

.PHONY: all clean

all: noos

noos$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o noos$(EXE)

# PT: Constrói o lexer isolado (debug)
# EN: Build the standalone lexer (debug)
lexer_standalone$(EXE): lexer.cpp
	$(CXX) $(CXXFLAGS) -DLEXER_STANDALONE lexer.cpp -o lexer_standalone$(EXE)

install: noos$(EXE)
	$(INSTALL)

uninstall:
	$(UNINST)

clean:
	$(RM) noos$(EXE) lexer_standalone$(EXE) *.o
