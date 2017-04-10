//function implementations for class tilemanager

#include "TileManager.h"
#include <stdio.h>

TileManager::TileManager() {}

TileManager::~TileManager() {}

//return number of non redundant rotations for each tetromino
int TileManager::numRotations(char piece) {
	if(piece == 'O')
		return 1;
	else if(piece == 'I' ||
			piece == '5' ||
			piece == '2' )
		return 2;
	else if(piece == 'T' ||
	   		piece == 'L' ||
	   		piece == 'P' )
		return 4;
	else
		return 0;
}

bool TileManager::place(char currPiece, Board * board, int rotation) {

	std::pair<int,int> * offset = getOffset(currPiece, rotation);

	//copy information from board that will be repeatedly used.
	int x = board->upperLeftX;
	int y = board->upperLeftY;
	int maxRow = board->rows;
	int maxCol = board->columns;

	for(int i = 0; i < 3; i++) {
		//only place piece if offset is within range.
		if((maxCol <= (x + offset[i].first)) || (maxRow <= (y + offset[i].second)) || (y + offset[i].second < 0) || (x + offset[i].first < 0)) 
			return false;
		if(board->board[y + offset[i].second][x + offset[i].first] != '-')
			return false;	
	}

	//Places pieces using offset plus current upper left.
	board->board[y][x] = ('a' + (board->numPieces - board->pieces.size() - 1));
	for(int i = 0; i < 3; i++) {
		board->board[y + offset[i].second][x + offset[i].first] = ('a' + (board->numPieces - board->pieces.size() - 1));
	}

	//cleanup
	delete[] offset;

	//update placed pieces list for easy undo.
	placedPiece placed = {currPiece, rotation, x, y};
	board->placedPieces.push_back(placed);

	//set new upperleft or flip solved flag.
	board->findUpperLeft();
	return true;
}

bool TileManager::solve(Board * board) {
	if(board->solved)
		return true;

	int size = board->pieces.size();

	for(int i = 0; i < size; i++) {
		//grab current piece and remove from list
		char currPiece = board->pieces[0];
		board->pieces.erase(board->pieces.begin());

		//try each rotation of the piece and if placed, recursively call
		//solve on the smaller set of pieces with updated board.
		for(int j = 0; j < numRotations(currPiece); j++) {
			if(place(currPiece, board, j)) {
				if(solve(board))
					return true;
				//if recursive call failed, undo steps until a new configuration can be tried.
				undo(board);
			}
		}

		//put piece on back of list of pieces to be used in a different configuration.
		board->pieces.push_back(currPiece);
	}

	return false;
}

std::pair<int,int> TileManager::createPair(int first, int second) {
	std::pair<int,int> p;
	p.first = first;
	p.second = second;

	return p;
}
//returns a list of offsets for each piece and its given rotation where
//the rotation number represents the number of 90 degree turns.
//These offsets were calculated by hand.
std::pair<int,int>* TileManager::getOffset(char piece, int rotation) {
	std::pair<int,int> * offset = new std::pair<int,int> [3];	

	if(piece == 'O') {
		offset[0] = createPair(0, 1);
		offset[1] = createPair(1, 0);
		offset[2] = createPair(1, 1);
	}
	else if(piece == 'I') {
		if(rotation == 0) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(0, 3);
		}
		else if(rotation == 1) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(2, 0);
			offset[2] = createPair(3, 0);
		}
	}
	else if(piece == 'L') {
		if(rotation == 0) {

			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(1, 2);
		}
		else if(rotation == 1) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(2, 0);
			offset[2] = createPair(0, 1);
		}		
		else if(rotation == 2) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(1, 1);
			offset[2] = createPair(1, 2);
		}
		else if(rotation == 3) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(-1, 1);
			offset[2] = createPair(-2, 1);
		}
	}
	else if(piece == 'P') {
		if(rotation == 0) {

			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(1, 0);
		}
		else if(rotation == 1) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(2, 0);
			offset[2] = createPair(2, 1);
		}		
		else if(rotation == 2) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(-1, 2);
		}
		else if(rotation == 3) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(1, 1);
			offset[2] = createPair(2, 1);
		}
	}
	else if(piece == 'T') {
		if(rotation == 0) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(1, 1);
			offset[2] = createPair(2, 0);
		}
		else if(rotation == 1) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(-1, 1);
		}		
		else if(rotation == 2) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(-1, 1);
			offset[2] = createPair(1, 1);
		}
		else if(rotation == 3) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(0, 2);
			offset[2] = createPair(1, 1);
		}
	}
	else if(piece == '2') {
		if(rotation == 0) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(1, 1);
			offset[2] = createPair(2, 1);
		}
		else if(rotation == 1) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(-1, 1);
			offset[2] = createPair(-1, 2);
		}
	}
	else if(piece == '5') {
		if(rotation == 0) {
			offset[0] = createPair(1, 0);
			offset[1] = createPair(0, 1);
			offset[2] = createPair(-1, 1);
		}
		else if(rotation == 1) {
			offset[0] = createPair(0, 1);
			offset[1] = createPair(1, 1);
			offset[2] = createPair(1, 2);
		}
	}

	return offset;
}

//undoes state of board to previous step with the use of the placedPieces vector
void TileManager::undo(Board * board) {
	//copy previous step taken and remove it from the placedPieces
	placedPiece undoPiece = board->placedPieces.back();
	board->placedPieces.pop_back();

	//reset to previous upper left.
	board->upperLeftY = undoPiece.upperLeftY;
	board->upperLeftX = undoPiece.upperLeftX;

	//grab offset for clearing the board of the piece placed last.
	std::pair<int,int> * offset = getOffset(undoPiece.piece, undoPiece.rotation);

	board->board[undoPiece.upperLeftY][undoPiece.upperLeftX] = '-';
	for(int i = 0; i < 3; i++) {
		board->board[undoPiece.upperLeftY + offset[i].second][undoPiece.upperLeftX + offset[i].first] = '-';
	}
}