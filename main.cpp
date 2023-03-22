#include <iostream>
#include "MoveGeneration.h"
#include "Board.h"
#include "ChessAI.h"

int main() {
//    uint64_t whitePieces =  0x000000100100a490;
//    uint64_t whiteKing =    0x0000000000000010;
//    uint64_t whitePawns =   0x000000100000a300;
//    uint64_t whiteKnights = 0x0000000000010000;
//    uint64_t whiteRooks =   0x0000000000000080;
//    uint64_t whiteBishops = 0x0000000000000000;
//    uint64_t whiteQueens =  0x0000000001000000;
//
//    uint64_t blackPieces =  0x81a7060060000000;
//    uint64_t blackKing =    0x0000020000000000;
//    uint64_t blackPawns =   0x00a7000020000000;
//    uint64_t blackKnights = 0x0000040000000000;
//    uint64_t blackRooks =   0x8100000000000000;
//    uint64_t blackBishops = 0x0000000000000000;
//    uint64_t blackQueens =  0x0000000040000000;
//    //initialize board.
//    Board b2 = Board(false, whitePieces, blackPieces, whiteKing, blackKing, whiteKnights, blackKnights, whitePawns, blackPawns,
//                    whiteRooks, blackRooks,whiteBishops, blackBishops, whiteQueens, blackQueens);
    Board b = Board();
    //initialize rays
    Rays::initializeRays();
    uint64_t a = E4;
    uint64_t aa = G2;
    uint64_t aaa = 0;
    Board::printMoveset(queenAttacks(a, aa, aaa));
    std::vector<Move> moves;
    int index;
    bool playerColor = false;
    while(!b.isGameOver())
    {
        b.printBoard();
        std::cout << std::endl;
        moves = b.legalMoves();

//        if(playerColor == b.color)
//        {
//            index = 0;
//            for (Move m: moves) {
//                std::cout << index << ": " << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()]
//                          << " --> " << squareNames[m.getToSquare()] << std::endl;
//                index++;
//            }
//
//            int move = -1;
//            while (!(std::cin >> move) || ((move < 0) || (move >= moves.size()))) {
//                std::cin.clear();
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            }
//            b.makeMove(moves[move]);
//        }
//        else
//        {
//            Move m = ChessAI::alphaBeta(b, 3, 5, 0, b.color);
//            std::cout << std::endl;
//            std::cout << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()] << std::endl;
//            b.makeMove(m);
//        }
        Move m = ChessAI::alphaBeta(b, 1, 4, 0, b.color);
        std::cout << std::endl;
        std::cout << pieceNames[m.getPiece()] << " " << squareNames[m.getToSquare()] << std::endl;
        b.makeMove(m);
    }
    for(auto & i : b.moveHistory)
    {
        std::cout << pieceNames[i.getPiece()] << " " << squareNames[i.getToSquare()] << std::endl;
    }
    return 0;
}
