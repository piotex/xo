#ifndef BOARD // include guard
#define BOARD
#include<iostream>
#include <vector>

class Board
{
public:
	Board(int size);
	~Board();
	
	char** tab;
	int size;

	void plotBoard();
	bool isBoardFull();
	bool isPossibleMove(int x, int y);
	bool addElement(int x, int y, char element);
	void clearBoard();
private:

protected:
};




#endif