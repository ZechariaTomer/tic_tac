#ifndef TIC_TAC_GAME_H
#define TIC_TAC_GAME_H

#include <iostream>
#include <vector>
#include <string>

class tic_tac_game
{
private:
    int boardSize;
    int winCondition;
    int movesCount;
    int errorCountX;
    int errorCountO;
    std::vector<std::vector<std::string>> board;

    bool checkWin(int row, int col, const std::string& player);

    static int bad_move;  

public:
    tic_tac_game(int boardSize, int winCondition);
    void printBoard() const;
    bool makeMove(int move, const std::string& player);
    bool isFull() const;
    bool checkForVictory(const std::string& player);
    void playGame();
};

#endif
