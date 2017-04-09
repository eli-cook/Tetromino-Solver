//implementations of the Board class

#include "Board.h"


Board::Board() {}
Board::~Board() {}

Board::Board(int row, int column, std::vector<char> pieces, int numPieces) {
	board = new char*[row];
	for (int i = 0; i < row; i++) {
		board[i] = new char[column];
	}
	board[0][0] = 0;
	this->numPieces = numPieces	;
	this->pieces = pieces;
}

bool Board::isSolved() {
	if(upperLeftX == -1)
		return true;
	else
		return false;
}