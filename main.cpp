#include <iostream>
#include "MoveGeneration.h"
#include "Board.h"

int main() {
    //initialize board.
    Board b = Board();
    std::vector<Move> moves;
    int index = 0;
    while(true)
    {
        b.printBoard();
        std::cout << std::endl;
        moves = b.legalMoves();

        index = 0;
        for(Move m : moves)
        {
            std::cout << index << ": " << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()] << " --> " << squareNames[m.getToSquare()] << std::endl;
            index++;
        }

        int move = -1;
        while(!(std::cin >> move) || ((move < 0) || (move >= moves.size())))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        b.makeMove(moves[move]);
    }
    return 0;
}
