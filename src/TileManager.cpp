//function implementations for class tilemanager

#include "TileManager.h"
#include <stdio.h>

TileManager::TileManager() {}

TileManager::~TileManager() {}

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

bool TileManager::place(char currPiece, Board * board, int rotation, int size) {

	std::pair<int,int> * offset = getOffset(currPiece, rotation);

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

	board->board[y][x] = ('a' + (board->numPieces - size - 1));
	for(int i = 0; i < 3; i++) {
		board->board[y + offset[i].second][x + offset[i].first] = ('a' + (board->numPieces - size - 1));
	}

	delete[] offset;

	placedPiece placed = {currPiece, rotation, x, y};
	board->placedPieces.push_back(placed);

	board->findUpperLeft();
	return true;
}

bool TileManager::solve(Board * board, std::vector<char> pieces) {
	printf("Pieces: ");
	for(auto p : pieces)
		printf("%c", p);
	printf("\n");
	if(board->solved)
		return true;

	int size = pieces.size();

	for(int i = 0; i < size; i++) {
		printf("Pieces: ");
		for(auto p : pieces)
			printf("%c", p);
		printf("\n");
		char currPiece = pieces[0];
		pieces.erase(pieces.begin());

		for(int j = 0; j < numRotations(currPiece); j++) {
			if(place(currPiece, board, j, pieces.size())) {
				printf("placed piece %c\n", currPiece);
				board->printBoard();
				if(solve(board, pieces))
					return true;
				printf("undoing last step\n");
				undo(board);
			}
			else {
				printf("failed to place piece %c\n", currPiece);
			}
		}

		pieces.push_back(currPiece);
	}

	return false;
}

std::pair<int,int> TileManager::createPair(int first, int second) {
	std::pair<int,int> p;
	p.first = first;
	p.second = second;

	return p;
}

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

void TileManager::undo(Board * board) {
	placedPiece undoPiece = board->placedPieces.back();
	board->placedPieces.pop_back();

	board->upperLeftY = undoPiece.upperLeftY;
	board->upperLeftX = undoPiece.upperLeftX;

	std::pair<int,int> * offset = getOffset(undoPiece.piece, undoPiece.rotation);

	board->board[undoPiece.upperLeftY][undoPiece.upperLeftX] = '-';
	for(int i = 0; i < 3; i++) {
		board->board[undoPiece.upperLeftY + offset[i].second][undoPiece.upperLeftX + offset[i].first] = '-';
	}
}

/*
	given i and j of the corner to place
	if(piece == 'O')
		board.board[i][j] = ('a' + (board.numPieces - board.pieceList.size());

*/