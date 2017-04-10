

#include "TileManager.h"
#include <stdio.h>
#include <vector>

int main(int argc, char* argv[]) {

	int row, column; 
	char ch;

	bool found = false;

	int numPieces = 0;

	std::vector<char> piecesList;

	row = getchar() - '0';
	getchar(); //gets rid of space;
	column = getchar() - '0';

	while(getchar() != '\n')
	getchar(); //gets rid of newline

	while((ch = getchar()) != EOF) {
		piecesList.push_back(ch);
		numPieces++;
	}

	Board * board = new Board(row, column, piecesList, numPieces);

	TileManager * tm = new TileManager();

	board->printBoard();

	found = tm->solve(board, board->pieces);
	
	if(found)
		board->printBoard();
	else
		printf("?\n");

	delete board;
	delete tm;
	return 0;
}