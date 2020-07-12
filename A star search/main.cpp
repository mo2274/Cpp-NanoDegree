
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <strstream>
#include  <sstream>
#include <algorithm>

using namespace std;

#define FILEPATH ("G:/embedded projects/eclipse workspace/firstc++code/text.txt")

enum class state {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

void printBoard(vector<vector<state>> board);
vector<vector<state>> readBoardFile(string filePath);
vector<state> parseLine(string line);
string cellString(state cell);
vector<vector<state>> search(vector<vector<state>> grid, int startingPoint[], int endPoint[]);
void addToOpen(int x, int y, int g, int h, vector<vector<int>>& openList, vector<vector<state>>& board);
int heuristic(int x1, int y1, int x2, int y2);
bool compare(vector<int> node1, vector<int> node2);
void cellsort(vector<vector<int>> *list);
bool checkValidCell(unsigned int x, unsigned int y, vector<vector<state>> board);
void printgrid(vector<vector<int>> grid);
void expandNeighbors(vector<int> currentNode, vector<vector<int>>& openList, vector<vector<state>>& board, int endPoint[]);

int main() {
	// read board from a file
	vector<vector<state>> board;
	board = readBoardFile(FILEPATH);
	// starting point
	int startingPoint[2] = {0,0};
	// end point
	int endPoint[2] = {5, 5};
	// search for the path
	board = search(board, startingPoint, endPoint);
	// print board
	printBoard(board);

    return 0;
}

void printBoard(vector<vector<state>> board) {
	for (unsigned int i = 0; i < board.size(); i++) {
		for (unsigned int j = 0; j < board[i].size(); j++) {
			cout << cellString(board[i][j]) << " ";
		}
		cout << "\n";
	}
}

vector<vector<state>> readBoardFile(string filePath) {
	string input;
	vector<vector<state>> board;
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
		output = parseLine(input);
		board.push_back(output);
	}
	return board;
}

vector<state> parseLine(string line) {
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

string cellString(state cell) {
  switch(cell) {
    case state::kObstacle:
    	return "1";
    case state::kStart:
    	return "2";
    case state::kFinish:
    	return "4";
    case state::kPath:
    	return "3";
    default:
    	return "0";
  }
}
// function to find the shortest path
vector<vector<state>> search(vector<vector<state>> board, int startingPoint[], int endPoint[]) {
	vector<vector<state>> solution;
	vector<vector<int>> openList;
	vector<int> currentNode ;
	int x, y, g, h;
	x = startingPoint[0];
	y = startingPoint[1];
	g = 0;
	h = heuristic(x, y, endPoint[0], endPoint[1]);
	// Add the new node to the list of open nodes.
	addToOpen(x, y, g, h, openList, board);
	// while open vector is non empty
	while (!openList.empty()) {
	    // Sort the open list using `CellSort`, and get the current node.
		cellsort(&openList);
		currentNode = openList.back();
		 openList.pop_back();
	    // Get the x and y values from the current node
		x = currentNode[0];
		y = currentNode[1];
		g = currentNode[3];
	    // set grid[x][y] to kPath.
		board[x][y] = state::kPath;
	    // Check if you've reached the goal. If so, return grid.
		if ((x == endPoint[0]) && (y == endPoint[1])) {
			board[startingPoint[0]][startingPoint[1]] = state::kStart;
			board[x][y] = state::kFinish;
			return board;
		}
	    // expand search to current node's neighbors
		expandNeighbors(currentNode, openList, board, endPoint);
	}
	// We've run out of new nodes to explore and haven't found a path.
	cout << "No path found!" << "\n";
	return solution;
}

// Heuristic function
int heuristic(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) + abs(y2 - y1);
}

// function to add nodes to open list
void addToOpen(int x, int y, int g, int h, vector<vector<int>>& openList, vector<vector<state>>& board) {
	vector<int> node = {x, y, g, h};
	openList.push_back(node);
	board[x][y] = state::kClosed;
}

// compare two nodes
bool compare(const vector<int> node1, const vector<int> node2) {
	if ((node1[2] + node1[3]) > (node2[2] + node2[3])) {
		return true;
	} else {
		return false;
	}
}

// function to sort vector of vector
void cellsort(vector<vector<int>> *list) {
	sort(list->begin(), list->end(), compare);
}

// function to check if the cell is valid or not
bool checkValidCell(unsigned int x, unsigned int y, vector<vector<state>> board) {
	if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size()) {
		return false;
	} else if (board[x][y] != state::kEmpty) {
		return false;
	} else {
		return true;
	}
}

void printgrid(vector<vector<int>> grid) {
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (auto j = grid[i].begin(); j != grid[i].end(); j++) {
			cout << *j << " ";
		}
		cout << "\n";
	}
}

void expandNeighbors(vector<int> currentNode, vector<vector<int>>& openList, vector<vector<state>>& board, int endPoint[]) {
	// Get current node's data.
	int x = currentNode[0];
	int y = currentNode[1];
	int g = currentNode[2];
	int h, x2, y2;
	const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    // loop over current node's potential neighbors.
	for (int i = 0; i < 4; i++) {
		x2 = x + delta[i][0];
		y2 = y + delta[i][1];
		if (checkValidCell(x2, y2, board)) {
			h = heuristic(x2, y2, endPoint[0], endPoint[1]);
			addToOpen(x2, y2, g + 1, h, openList, board);
		}
	}
}
















