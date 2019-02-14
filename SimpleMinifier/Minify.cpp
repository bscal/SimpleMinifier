#include "Minify.h"

#include <iostream>
#include <fstream>
#include <string>

bool minifyFiles(const std::string& inputFilePath, const std::string& outputFilePath) {
	std::ifstream inFile;
	int inSize;

	std::ofstream outFile;

	char* buffer;

	// Init of inFile
	inFile.open("index.js", std::ios::in | std::ios::binary);

	if (!inFile.is_open()) {
		std::cerr << "[ error ] Input file is not open!\n";
		return false;
	}

	// Get files size
	inFile.seekg(0, std::ios::end);
	inSize = inFile.tellg();
	inFile.seekg(0, std::ios::beg);

	// Creates buffer and writes input file to it
	// Size is + 1 to add in null terminator
	buffer = new char[inSize + 1];
	inFile.read(buffer, inSize);

	// In file closed here
	inFile.close();

	if (inFile.bad()) {
		std::cerr << "[ error ] Error reading input file\n";
		return false;
	}
	std::clog << "[ ok ] Input file was read to buffer\n";

	char* outBuffer = new char[inSize + 1];
	int outBufferCount = 0;
	bool quotes = false;

	for (int i = 0; i < inSize; i++) {
		char c = buffer[i];
		if (c == '\t' || c == '\n' || c == '\r') {
			continue;
		}

		//		*Since we check if c == \t instead of a space this is not needed	
		else if (c == '"') {
			(quotes) ? quotes = false : quotes = true;
		}

		else if (c == ' ' && !quotes && !isKeyword(c, outBuffer, outBufferCount)) {
			continue;
		}
		outBuffer[outBufferCount++] = c;

	}

	// Init of outFile
	outFile.open("index.min.js");

	if (!outFile.is_open()) {
		std::cerr << "[ error ] Output file is not open!\n";
		return false;
	}
	outFile.write(outBuffer, outBufferCount);
	outFile << '\0';

	// Out file closed here
	outFile.close();

	if (inFile.bad()) {
		std::cerr << "[ error ] Could not write to output file!\n";
		return false;
	}

	// Buffer deletion here
	delete[] buffer;
	delete[] outBuffer;

	std::clog << "[ ok ] Output file wrote to file.\n";

	// Info on size reduction
	std::clog << "Reduced from " << inSize << " characters down to " << outBufferCount << " characters!\n";
	std::clog << "Using 8-bit characters thats total of " << inSize - outBufferCount << " bytes\n";
	return true;
}

/**
 * Checks the current character if the past character was part of a keyword
 * It will compare if the last and first char of a keyword are equal and return true
 * This is used to preserve spaces after keywords!
 */
bool isKeyword(const char & c, const char buffer[], int counter)
{
	char lastChar = buffer[counter - 1];
	for (std::string str : keywords) {
		if (lastChar == str.back() && buffer[counter - str.length()] == str.front()) {
			return true;
		}
	}
	return false;
}
