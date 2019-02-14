#include "FileCombiner.h"

#include <fstream>
#include <iostream>
#include <vector>

bool combineFiles(const CombineConfig& config, const std::string& outputFilePath)
{

	int currentLargestSize = 0;
	char* buffer = new char[0];

	std::ofstream outFile;
	outFile.open(outputFilePath, std::ios::out | std::ios::app | std::ios::binary);

	std::ifstream inFile;
	int inSize;

	for (std::string path : config.m_InputFiles) {
		inFile.open(path, std::ios::in | std::ios::binary);
		inFile.clear();

		if (!inFile.is_open()) {
			std::cerr << "[ error ] FileCombiner: inFile is not open!\n";
			return false;
		}

		
		inFile.seekg(0, std::ios::end);
		inSize = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		delete[] buffer;
		buffer = new char[inSize];
		
		inFile.read(buffer, inSize);
		inFile.close();

		if (inFile.bad()) {
			std::cerr << "[ error ] FileCombiner: Error writing to outfile from combined file\n";
			return false;
		}

		if (!outFile.is_open()) {
			std::cerr << "[ error ] FileCombiner: outFile is not open!\n";
			return false;
		}
		outFile << '\r';
		outFile << '\n';
		outFile.write(buffer, inSize);
	}
	outFile << '\0';
	outFile.close();

	delete[] buffer;

	if (outFile.bad()) {
		std::cerr << "[ error ] FileCombiner: Failed write failed\n";
		return false;
	}
	return true;
}
