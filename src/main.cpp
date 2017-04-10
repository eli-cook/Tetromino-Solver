

#include "TileManager.h"
#include <stdio.h>
#include <vector>

int main(int argc, char* argv[]) {

	int row, column; 
	char ch;

	bool found = false;

	std::vector<char> piecesList;

	//grab row and column size from stdin
	scanf("%d %d\n", &row, &column);

	//grab pieces from stdin
	while((ch = getchar()) != EOF) {
		piecesList.push_back(ch);
	}
	//Can't have more than 9 tetrominos. Given constraint.
	if(piecesList.size() > 9) {
		printf("?\n");
		return 0;
	}
	//Can't have a board size greater than 36 squares total. Given constraint.
	if(row * column > 36) {
		printf("?\n");
		return 0;
	}
	//Must have the correct number of pieces given a specific board size.
	if(row * column != (int)piecesList.size() * 4) {
		printf("?\n");
		return 0;
	}
	//initialize board
	Board * board = new Board(row, column, piecesList, piecesList.size());

	//initialize tilemanager
	TileManager * tm = new TileManager();

	//run solver
	found = tm->solve(board);
	
	if(found)
		board->printBoard();
	else
		printf("?\n");

	//cleanup
	delete board;
	delete tm;
	return 0;
}