#include "tic_tac_game.h"

int tic_tac_game::bad_move = 0;

tic_tac_game::tic_tac_game(int boardSize, int winCondition) :
    boardSize(boardSize), winCondition(winCondition), movesCount(0), errorCountX(0), errorCountO(0)
{
    board.resize(boardSize, std::vector<std::string>(boardSize));
    int counter = 1;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = std::to_string(counter++);
        }
    }
}

void tic_tac_game::printBoard() const
{
    std::cout << "\nCurrent Board:\n";
    for (const auto& row : board)
    {
        for (const auto& cell : row)
        {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
}

bool tic_tac_game::makeMove(int move, const std::string& player)
{
    int row = (move - 1) / boardSize;
    int col = (move - 1) % boardSize;

    if (move < 1 || move > boardSize * boardSize || board[row][col] == "X" || board[row][col] == "O")
    {
        std::cout << "Invalid move. Move should be between 1 and " << boardSize * boardSize << ". Try again.\n";
        bad_move++;
        return false;
    }

    if (player == "X") {
        errorCountX = 0;
    }
    else if (player == "O") {
        errorCountO = 0;
    }

    board[row][col] = player;
    movesCount++;
    return true;
}

bool tic_tac_game::isFull() const
{
    return movesCount == boardSize * boardSize;
}

bool tic_tac_game::checkWin(int row, int col, const std::string& player)
{
    int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

    for (auto& dir : directions)
    {
        int count = 1;
        for (int i = 1; i < winCondition; i++)
        {
            int newRow = row + i * dir[0];
            int newCol = col + i * dir[1];
            if (newRow >= 0 && newRow < boardSize && newCol >= 0 &&
                newCol < boardSize && board[newRow][newCol] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; i < winCondition; i++)
        {
            int newRow = row - i * dir[0];
            int newCol = col - i * dir[1];
            if (newRow >= 0 && newRow < boardSize && newCol >= 0 &&
                newCol < boardSize && board[newRow][newCol] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }

        if (count >= winCondition) return true;
    }
    return false;
}

bool tic_tac_game::checkForVictory(const std::string& player)
{
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == player && checkWin(i, j, player))
            {
                return true;
            }
        }
    }
    return false;
}

void tic_tac_game::playGame()
{
    std::string currentPlayer = "X";
    printBoard();

    while (!isFull())
    {
        int move;
        std::cout << "Player " << currentPlayer << ", enter your move (1 to " << boardSize * boardSize << "): ";
        std::cin >> move;

        if (!makeMove(move, currentPlayer))
        {
            if (bad_move >= 4) {
                std::cout << "Too many invalid attempts! The game is being stopped.\n";
                break;
            }
            continue;
        }

        printBoard();

        if (checkForVictory(currentPlayer))
        {
            std::cout << "Player " << currentPlayer << " wins!\n";
            return;
        }

        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }

    std::cout << "Game Over! No winner. The board is full.\n";
}
