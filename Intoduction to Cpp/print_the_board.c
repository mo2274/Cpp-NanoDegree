#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <strstream>
#include  <sstream>


using namespace std;

void printBoard(vector<vector<int>> board);

int main()
{
	vector<vector<int>> board{{0, 1, 0, 0, 0, 0},
							  {0, 1, 0, 0, 0, 0},
							  {0, 1, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 1, 0}};
	printBoard(board)

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