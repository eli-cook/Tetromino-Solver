//defines the class tilemanager that manipulates the board class

#include "Board.h"

class TileManager {
public:	
	TileManager();
	~TileManager();
	bool place(char currPiece, Board * board, int rotation);
	bool solve(Board * board);
	int numRotations(char piece);
};