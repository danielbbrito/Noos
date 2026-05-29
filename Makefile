CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall -Wno-unused-function -I.

# PT: $(OS)=Windows_NT tanto no Windows nativo quanto no WSL2.
#     Usa uname só dentro desse bloco para distinguir os dois casos.
# EN: $(OS)=Windows_NT on both native Windows and WSL2.
#     Uses uname only inside that block to tell them apart.
ifeq ($(OS),Windows_NT)
    UNAME_S := $(shell uname -s 2>NUL)
    ifeq ($(UNAME_S),Linux)
        EXE     =
        BINDIR  = /usr/local/bin
        INSTALL = sudo cp noos $(BINDIR)/noos
        UNINST  = sudo rm -f $(BINDIR)/noos
        RM      = rm -f
    else
        EXE     = .exe
        BINDIR  = %LOCALAPPDATA%\bin
        INSTALL = (if not exist "%LOCALAPPDATA%\bin" mkdir "%LOCALAPPDATA%\bin") && copy /Y noos.exe "%LOCALAPPDATA%\bin\noos.exe"
        UNINST  = if exist "%LOCALAPPDATA%\bin\noos.exe" del /f "%LOCALAPPDATA%\bin\noos.exe"
        RM      = del /f
    endif
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

all: noos$(EXE)

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
