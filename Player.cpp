#include "Player.hh"

Player::Player(char _znak, Board* _board)
{
	znak = _znak;
	board = _board;
	ile_zeby_wygrac = board->size;
}
Player::~Player()
{
	//delete board;
}
void Player::MakeMove(int x, int y)
{
	board->tab[x][y] = znak;
}
void Player::UndoMove(int x, int y)
{
	board->tab[x][y] = ' ';
}

bool Player::VerticalWin(int number_to_win)
{
	int counter = 0;
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			for (int k = 0; k < number_to_win; k++)
			{
				if ( (j + k) < board->size){
					if (board->tab[i][(j + k)] == znak)
						counter++;
					else
						break;
				}
				else {
					break;
				}
			}
			if (counter == number_to_win)
				return true;
			else
				counter = 0;
		}
	}
	return false;
}

bool Player::HorizontalWin(int number_to_win)
{
	int counter = 0;
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			for (int k = 0; k < number_to_win; k++)
			{
				if ((j + k) < board->size) {
					if (board->tab[(j + k)][i] == znak)
						counter++;
					else
						break;
				}
				else {
					break;
				}
			}
			if (counter == number_to_win)
				return true;
			else
				counter = 0;
		}
	}
	return false;
}

bool Player::DiagonalWin(int number_to_win)
{
	int counter = 0;
	// w prawo dol
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			for (int k = 0; k < number_to_win; k++)
			{
				if ((j + k) < board->size && (i + k) < board->size) {
					if (board->tab[(i + k)][(j + k)] == znak)
						counter++;
					else
						break;
				}
			}
			if (counter == number_to_win)
				return true;
			else
				counter = 0;
		}
	}
	// w lewo dol
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			for (int k = 0; k < number_to_win; k++)
			{
				if ((j - k) >= 0 && (i + k) < board->size) {
					if (board->tab[(i + k)][(j - k)] == znak)
						counter++;
					else
						break;
				}
			}
			if (counter == number_to_win)
				return true;
			else
				counter = 0;
		}
	}
	return false;
}

bool Player::IsWinner(int number_to_win)
{
	if (HorizontalWin(number_to_win) || VerticalWin(number_to_win) || DiagonalWin(number_to_win))
		return true;
	else
		return false;

}

int Player::check_score(Player opponent)
{
	if (IsWinner(ile_zeby_wygrac))
		return WIN_PT;
	if (opponent.IsWinner(ile_zeby_wygrac))
		return -WIN_PT;
	
	return 0;
}


int Player::MinMax(Player opponent, int rec_depth, bool isMaxPlayer){
	int best_val = 0;
	int val = 0;
	int score = check_score(opponent);

	if (board->isBoardFull() || rec_depth == 0)	
		return score;
	if (score == WIN_PT || score == -WIN_PT)
		return score;


	if (isMaxPlayer)
	{
		best_val = -INF;
		for (int i = 0; i < board->size; i++)
		{
			for (int j = 0; j < board->size; j++)
			{
				if (board->isPossibleMove(i, j))					
				{
					MakeMove(i, j);								
					val = MinMax(opponent, rec_depth - 1,  false); 
					val = val - rec_depth;				
					UndoMove(i, j);								
					best_val = std::max(best_val, val);		
				}
			}
		}
		return best_val;
	}
	else
	{
		best_val = INF;
		for (int i = 0; i < board->size; i++)
		{
			for (int j = 0; j < board->size; j++)
			{
				if (board->isPossibleMove(i, j))			
				{
					opponent.MakeMove(i, j);						
					val = MinMax(opponent, rec_depth - 1, true);	
					val = val + rec_depth;				
					opponent.UndoMove(i, j);						
					best_val = std::min(best_val, val);	
				}
			}
		}
		return best_val;
	}
	return 0;
}


int Player::Min(Player opponent, int rec_depth) {
	int best_val = 0;
	int val = 0;
	int score = check_score(opponent);

	if (board->isBoardFull() || rec_depth == 0)
		return score;
	if (score == 100 || score == -100)
		return score;

	best_val = INF;
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->isPossibleMove(i, j))
			{
				opponent.MakeMove(i, j);
				val = Max(opponent, rec_depth - 1);
				val = val + rec_depth;
				opponent.UndoMove(i, j);
				best_val = std::min(best_val, val);
			}
		}
	}
	return best_val;
}

int Player::Max(Player opponent, int rec_depth) {
	int best_val = 0;
	int val = 0;
	int score = check_score(opponent);

	if (board->isBoardFull() || rec_depth == 0)
		return score;
	if (score == 100 || score == -100)
		return score;

	best_val = -INF;
	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->isPossibleMove(i, j))
			{
				MakeMove(i, j);
				val = Min(opponent, rec_depth - 1);
				val = val - rec_depth;
				UndoMove(i, j);
				best_val = std::max(best_val, val);
			}
		}
	}
	return best_val;
}



int* Player::BestDecision(Player opponent)
{
	int rec_depth = 4;	//jak gleboko schodzimy

	int* ret = new int[2];
	ret[0] = ret[1] = -11;	//przyda sie przy debugowaniu, bo nie ma opcji zeby wartosci byly ujemne
	int val = 0;
	int best_val = -INF;

	for (int i = 0; i < board->size; i++)
	{
		for (int j = 0; j < board->size; j++)
		{
			if (board->isPossibleMove(i, j))
			{
				MakeMove(i, j);
				val = Min(opponent, rec_depth);
				//val = MiniMax(opponent, rec_depth,false);
				UndoMove(i, j);

				if (val > best_val)
				{
					ret[0] = i;
					ret[1] = j;
					best_val = val;
					/*if (val == WIN_PT)
						return ret;*/
				}
			}
		}
	}
	return ret;
}
