//This file defines the board object
#include <vector>

class Board {
public:
	char ** board;	
	std::vector<char> pieces;
	int numPieces;
	int upperLeftX;
	int upperLeftY;

	Board();
	~Board();
	Board(int row, int column, std::vector<char> pieces, int numPieces);

	void printBoard();
	bool isSolved();
};
