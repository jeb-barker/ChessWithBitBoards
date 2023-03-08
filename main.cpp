#include <iostream>
#include "MoveGeneration.h"
#include "Board.h"

int main() {

    Board b = Board();
    b.printBoard();
    std::cout << std::endl;
    std::vector<Move> moves = b.legalMoves();

    for(Move m : moves)
    {
        std::cout << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()] << " --> " << squareNames[m.getToSquare()] << std::endl;
    }
    return 0;
}
