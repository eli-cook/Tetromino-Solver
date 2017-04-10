//This file defines the board object
#include <vector>

struct placedPiece {
	char piece;
	int rotation;
	int upperLeftX;
	int upperLeftY;
};

class Board {
public:
	char ** board;	
	std::vector<char> pieces;
	std::vector<placedPiece> placedPieces;
	int numPieces;
	int upperLeftX;
	int upperLeftY;
	int rows;
	int columns;
	bool solved;

	Board();
	~Board();
	Board(int row, int column, std::vector<char> pieces, int numPieces);

	void printBoard();
	void findUpperLeft();
};
