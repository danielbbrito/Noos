#pragma once
#include <vector>
#include <string>
#include "token.h"

std::vector<Token> scan_source(std::string file_path, bool debug);
