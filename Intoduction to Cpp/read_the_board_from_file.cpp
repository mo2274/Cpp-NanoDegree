
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <strstream>
#include  <sstream>



using namespace std;

#define FILEPATH ("G:/embedded projects/eclipse workspace/firstc++code/text.txt")

enum class state {kEmpty, kObstacle};
enum class mohamd {a, b, c, d};

void printBoard(vector<vector<state>> board);
void ReadBoardFile(string filePath);
vector<state> ParseLine(string line);
string CellString(state cell);




vector<vector<state>> board;

int main()
{

	ReadBoardFile(FILEPATH);
	printBoard(board);

    return 0;
}

void printBoard(vector<vector<state>> board) {
	for (unsigned int i = 0; i < board.size(); i++) {
		for (unsigned int j = 0; j < board[i].size(); j++) {
			cout << CellString(board[i][j]) << " ";
		}
		cout << "\n";
	}
}

void ReadBoardFile(string filePath) {
	string input;
	vector<state> output;
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




vector<state> ParseLine(string line) {
	// vector to store the output
	vector<state> result;
	// convert the string into stream
	istringstream stream_1(line);
	// parse the stream
	int n;
	char c;
	while (stream_1 >> n >> c && c == ',') {
		switch (n) {
		case 0:
			result.push_back(state::kEmpty);
			break;
		case 1:
			result.push_back(state::kObstacle);
		}
	}

	return result;
}




string CellString(state cell) {
  switch(cell) {
    case state::kObstacle: return "⛰  ";
    default: return "0 ";
  }
}










