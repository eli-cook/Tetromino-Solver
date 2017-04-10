//implementations of the Board class

#include "Board.h"
#include <stdio.h>


Board::Board() {}
Board::~Board() {}

void Board::printBoard() {
	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			printf("%c", board[y][x]);
		}
		printf("\n");
	}
}

Board::Board(int row, int column, std::vector<char> pieces, int numPieces) {
	//initialize new board to all dashes (-)
	board = new char *[row];
	for(int i = 0; i < row; i++) {
		board[i] = new char[column];
		for(int j = 0; j < column; j++) {
			board[i][j] = '-';
		}
	}
	this->numPieces = numPieces	;
	this->pieces = pieces;
	//default starting location
	upperLeftY = 0;
	upperLeftX = 0;
	rows = row;
	columns = column;
	solved = false;
}

void Board::findUpperLeft() {	
	int startX = upperLeftX;

	for(int y = upperLeftY; y < rows; y++) {
		for(int x = startX; x < columns; x++) {
			if(board[y][x] == '-') {
				upperLeftY = y;
				upperLeftX = x;
				return;
			}
		}
		startX = 0;
	}

	this->solved = true;
}