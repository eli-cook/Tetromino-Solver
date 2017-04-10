//defines the class tilemanager that manipulates the board class

#include "Board.h"
#include <utility>

class TileManager {
public:	
	TileManager();
	~TileManager();
	bool place(char currPiece, Board * board, int rotation);
	bool solve(Board * board);
	int numRotations(char piece);
	std::pair<int,int> createPair(int first, int second);
	std::pair<int,int>* getOffset(char piece, int rotation);
	void undo(Board * board);
};