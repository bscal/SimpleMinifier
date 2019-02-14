#pragma once

#include <iostream>
#include <vector>

struct CombineConfig {
	std::vector<std::string> m_InputFiles;
};

bool combineFiles(const CombineConfig& config, const std::string& outputFile);
