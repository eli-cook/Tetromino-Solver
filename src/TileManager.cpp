//function implementations for class tilemanager

#include "TileManager.h"

TileManager::TileManager() {}

TileManager::~TileManager() {}

int TileManager::numRotations(char piece) {
	if(piece == 'O')
		return 1;
	else if(piece == 'I')
		return 2;
	else if(piece == '5' ||
	   		piece == '2' ||
	   		piece == 'T' ||
	   		piece == 'L' 	)
		return 4;
	else
		return 0;
}

bool TileManager::place(char currPiece, Board * board, int rotation) {
	if(currPiece == 'O') {

	}
	else if(currPiece == 'I') {

	}
	else if(currPiece == 'L') {

	}
	else if(currPiece == 'T') {

	}
	else if(currPiece == '5') {

	}
	else if(currPiece == '2') {

	}
	else 
		return false;

	return false;
}

bool TileManager::solve(Board * board) {
	if(board->isSolved())
		return true;

	for(int i = 0; i < board->numPieces - 1; i++) {
		char currPiece = board->pieces[0];
		board->pieces.erase(board->pieces.begin());

		for(int i = 1; i < numRotations(board->pieces.back()); i++) {
			if(place(currPiece, board, i)) {
				if(solve(board))
					return true;
			}
		}

		board->pieces.push_back(currPiece);
	}
}

/*
	given i and j of the corner to place
	if(piece == 'O')
		board.board[i][j] = ('a' + (board.numPieces - board.pieceList.size());

*/