#include <iostream>
#include "Board.hh"
#include"Player.hh"

int setSize()
{
    int s;
    std::cout << "Podaj rozmiar planszy:" << std::endl;
    std::cin >> s;
    return s;
}
bool ask_isCorrectMove(int x, int y, int size) {
    if (x<0 || y<0)
    {
        return false;
    }
    if (x>size-1 || y>size-1)
    {
        return false;
    }
    return true;
}
bool ask_makeCorrectMove(int& x, int& y, Board* board) {
    bool is_ok = true;
    do 
    {
        std::cout << "Twoj ruch, podaj wspolzedna  x: ";
        std::cin >> x;
        std::cout << "Twoj ruch, podaj wspolzedna  y: ";
        std::cin >> y;
        std::cout << "\n";

        if (!ask_isCorrectMove(x, y, board->size))
        {
            is_ok = false;
            std::cout << "Chcesz wybrac pole poza plansza" << std::endl;
        }
        else
        {
            if (!board->isPossibleMove(x, y))
            {
                is_ok = false;
                std::cout << "Chcesz wybrac zajete pole" << std::endl;
            }
            else
            {
                is_ok = true;
            }
        }

    }     
    while (!is_ok);

    return true;
}
bool ask_end(Board* board, Player player_i, Player player_ai, int number_to_win) {
    if (player_ai.IsWinner(number_to_win))
    {
        std::cout << "Przegrales" << std::endl;
        return true;
    }
    if (player_i.IsWinner(number_to_win))
    {
        std::cout << "Wygrales" << std::endl;
        return true;
    }
    if (board->isBoardFull())
    {
        std::cout << "remis" << std::endl;
        return true;
    }
    return false;
}

int main()
{
    int x, y;
	int size = setSize();
    Board* board = new Board(size);
    Player player_i('O', board);
    Player player_ai('X', board);

    board->plotBoard();

    while (1)
    {
        ask_makeCorrectMove(x, y, board);

        player_i.MakeMove(x, y);
        board->plotBoard();
        if (ask_end(board, player_i, player_ai,player_i.ile_zeby_wygrac))
            return 0;

        int* move = player_ai.BestDecision(player_i);
        player_ai.MakeMove(move[0],move[1]);
        board->plotBoard();
        if (ask_end(board, player_i, player_ai, player_ai.ile_zeby_wygrac))
            return 0;

    }
    return 1;
}



