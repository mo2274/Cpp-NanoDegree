
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <strstream>
#include  <sstream>


using namespace std;

#define FILEPATH ("G:/embedded projects/eclipse workspace/firstc++code/text.txt")

void printBoard(vector<vector<int>> board);
void ReadBoardFile(string filePath);
vector<int> ParseLine(string line);

vector<vector<int>> board;

int main()
{
	ReadBoardFile(FILEPATH);
	printBoard(board);

    return 0;
}

void printBoard(vector<vector<int>> board) {
	for (unsigned int i = 0; i < board.size(); i++) {
		for (unsigned int j = 0; j < board[i].size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

void ReadBoardFile(string filePath) {
	string input;
	vector<int> output;
	// create an object for the input file
	ifstream inputFile{filePath, ios::in};
	// check for errors
	if (!inputFile) {
		cout << "file could not be opened";
		exit(EXIT_FAILURE);
	}
	// read data from the file
	while (getline(inputFile, input)) {
		output = ParseLine(input);
		board.push_back(output);
	}
}

vector<int> ParseLine(string line) {
	// vector to store the output
	vector<int> result;
	// convert the string into stream
	istringstream stream(line);
	// parse the stream
	string temp;
	while (stream.good()) {
		getline(stream, temp, ',');
		result.push_back(stoi(temp));
	}

	return result;
}















