#ifndef PLAYER // include guard
#define PLAYER
#include<iostream>
#include <vector>
#include"Board.hh"

#define INF 1000000
#define WIN_PT 100

class Player
{
public:
	Player(char _znak, Board* board);
	~Player();

	// spytac o to uzytkownika w main
	int ile_zeby_wygrac;
	//
	char znak;
	Board* board;

	void MakeMove(int x, int y);
	void UndoMove(int x, int y);

	bool VerticalWin(int number);
	bool HorizontalWin(int number);
	bool DiagonalWin(int number);
	bool IsWinner(int number_to_win);

	int check_score(Player opponent);

	int Min(Player opponent, int rec_depth);
	int Max(Player opponent, int rec_depth);
	int* BestDecision(Player opponent);

	int MinMax(Player opponent, int rec_depth, bool isMaxPlayer);
};




#endif