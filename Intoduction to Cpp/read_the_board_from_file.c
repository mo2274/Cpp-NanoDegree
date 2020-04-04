#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <strstream>
#include  <sstream>


using namespace std;

#define FILEPATH ("G:/embedded projects/eclipse workspace/firstc++code/text.txt")

void ReadBoardFile(string filePath);

int main()
{
	ReadBoardFile(FILEPATH);

    return 0;
}

void ReadBoardFile(string filePath) {
	string input;
	// create an object for the input file
	ifstream inputFile{filePath, ios::in};
	// check for errors
	if (!inputFile) {
		cout << "file could not be opened";
		exit(EXIT_FAILURE);
	}
	// read data from the file
	while (inputFile) {
		inputFile >> input;
		cout << input << "\n";
	}
}
