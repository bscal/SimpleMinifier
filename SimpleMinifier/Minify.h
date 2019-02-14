#pragma once

#include <string>

const std::string keywords[] = { "function", "return", "var", "let", "const", "throws", "new" };

bool minifyFiles(const std::string& inputFilePath, const std::string& outputFilePath);

bool isKeyword(const char& c, const char buffer[], int counter);