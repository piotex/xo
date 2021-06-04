#include "Board.hh"

Board::Board(int _size)
{
	size = _size;
	tab = new char* [_size];
	for (int i = 0; i < size; i++)
	{
		for (int i = 0; i < _size; i++)
		{
			tab[i] = new char[_size];
		}
	}
	clearBoard();
}
Board::~Board()
{
	for (int i = 0; i < size; i++)
	{
		delete tab[i];
	}
	delete[] tab;
}


void Board::plotBoard()
{
	std::cout << "\x1B[2J\x1B[H";
	for (int i = 0; i < size; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < size; j++)
		{
			std::cout << tab[i][j] << " | ";
		}
		std::cout << std::endl;
	}
}
bool Board::isBoardFull()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tab[i][j] == ' ')
				return false;
		}
	}
	return true;
}
bool Board::isPossibleMove(int x, int y)
{
	return !(tab[x][y] == 'X' || tab[x][y] == 'O');
}
bool Board::addElement(int x, int y, char element)
{
	if (isPossibleMove(x, y))
	{
		tab[x][y] = element;
		return true;
	}
	std::cout << "Zajente, wybierz inne miejsce" << std::endl;
	return false;
}
void Board::clearBoard()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			tab[i][j] = ' ';
		}
	}
}
