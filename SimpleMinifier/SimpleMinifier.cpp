#include "Minify.h"
#include "FileCombiner.h"

bool doMinify = false;
int minifyOffset = 0;

bool doCombine = false;
int combineOffset = 0;

void parseArgs(const int& argc, const char* argv[]) {
	for (int count = 0; count < argc; count++) {
		if (std::strcmp(argv[count], "-m") == 0) {
			doMinify = true;
			minifyOffset = count;
		}
		if (std::strcmp(argv[count], "-c") == 0) {
			doCombine = true;
			combineOffset = count;
		}
	}
}

int main(int argc, const char* argv[])
{
	parseArgs(argc, argv);

	if (doMinify) {
		if (!minifyFiles(argv[minifyOffset + 1], argv[minifyOffset + 2])) {
			std::cerr << "[ error ] Minify was unsuccessful!\n";
			return 1;
		}
		std::clog << "Minify was successful!\n";
	}

	if (doCombine) {
		CombineConfig cc = CombineConfig();
		cc.m_InputFiles.push_back(argv[combineOffset + 1]);
		cc.m_InputFiles.push_back(argv[combineOffset + 2]);
		if (!combineFiles(cc, argv[combineOffset + 3])) {
			std::cerr << "[ error ] File combine was unsuccessful!\n";
			return 1;
		}
		std::clog << "Files successfully combined!\n";
	}

	return 0;
}
