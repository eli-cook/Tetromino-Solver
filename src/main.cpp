

#include "TileManager.h"
#include <stdio.h>
#include <vector>

int main(int argc, char* argv[]) {

	char row, column, ch;

	bool found = false;

	int numPieces = 0;

	std::vector<char> piecesList;

	row = getchar();
	getchar(); //gets rid of space;
	column = getchar();

	while(getchar() != '\n')
	getchar(); //gets rid of newline

	while((ch = getchar()) != EOF) {
		piecesList.push_back(ch);
		numPieces++;
	}

	Board * board = new Board(row, column, piecesList, numPieces);

	TileManager * tm = new TileManager();

	tm->solve(board);
	
	if(found)
		printf("Found a solution!\n");
	else
		printf("?\n");

	return 0;
}