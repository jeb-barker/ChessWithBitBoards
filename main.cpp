#include <iostream>
#include "MoveGeneration.h"
#include "Board.h"
#include "ChessAI.h"

int main() {
    //alternate board for testing purposes.
    uint64_t whitePieces =  0x0010000000000001;
    uint64_t whiteKing =    0x0000000000000001;
    uint64_t whitePawns =   0x0010000000000000;
    uint64_t whiteKnights = 0x0000000000000000;
    uint64_t whiteRooks =   0x0000000000000000;
    uint64_t whiteBishops = 0x0000000000000000;
    uint64_t whiteQueens =  0x0000000000000000;

    uint64_t blackPieces =  0x0000000000000004;
    uint64_t blackKing =    0x0000000000000004;
    uint64_t blackPawns =   0x0000000000000000;
    uint64_t blackKnights = 0x0000000000000000;
    uint64_t blackRooks =   0x0000000000000000;
    uint64_t blackBishops = 0x0000000000000000;
    uint64_t blackQueens =  0x0000000000000000;
    //initialize board.
    Board b2 = Board(false, whitePieces, blackPieces, whiteKing, blackKing, whiteKnights, blackKnights, whitePawns, blackPawns,
                    whiteRooks, blackRooks,whiteBishops, blackBishops, whiteQueens, blackQueens);
    Board b = Board();
    //initialize rays
    Rays::initializeRays();
    std::vector<Move> moves;
    int index;
    bool playerColor = false;
    bool player = false;
    while(!b.isGameOver())
    {
        b.printBoard();
        std::cout << std::endl;
        moves = b.legalMoves();
        if(player)
        {
            if (playerColor == b.color)
            {
                index = 0;
                for (Move m: moves) {
                    if (m.getFlags() == 0b0110)
                    {
                        std::cout << index << ": " << "Pawn " << squareNames[m.getFromSquare()]
                                  << " --> " << squareNames[m.getToSquare()] << "=Knight" << std::endl;
                    }
                        //bishop
                    else if (m.getFlags() == 0b0111)
                    {
                        std::cout << index << ": " << "Pawn " << squareNames[m.getFromSquare()]
                                  << " --> " << squareNames[m.getToSquare()] << "=Bishop" << std::endl;
                    }
                        //rook
                    else if (m.getFlags() == 0b1000)
                    {
                        std::cout << index << ": " << "Pawn " << squareNames[m.getFromSquare()]
                                  << " --> " << squareNames[m.getToSquare()] << "=Rook" << std::endl;
                    }
                        //queen
                    else if (m.getFlags() == 0b1001)
                    {
                        std::cout << index << ": " << "Pawn " << squareNames[m.getFromSquare()]
                                  << " --> " << squareNames[m.getToSquare()] << "=Queen" << std::endl;
                    }
                        //no promotion
                    else
                    {
                        std::cout << index << ": " << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()]
                                  << " --> " << squareNames[m.getToSquare()] << std::endl;
                    }
                    index++;
                }

                int move = -1;
                while (!(std::cin >> move) || ((move < 0) || (move >= moves.size())))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                b.makeMove(moves[move]);
            }
            else
            {
                Move m = ChessAI::alphaBeta(b, 3, 5, 0, b.color);
                std::cout << std::endl;
                std::cout << pieceNames[m.getPiece()] << " " << squareNames[m.getFromSquare()] << std::endl;
                b.makeMove(m);
            }
        }
        else
        {
            Move m = ChessAI::alphaBeta(b, 1, 4, 0, b.color);
            std::cout << std::endl;
            std::cout << pieceNames[m.getPiece()] << " " << squareNames[m.getToSquare()] << std::endl;
            moves = b.legalMoves();
            b.makeMove(m);
        }
    }
    for(auto & i : b.moveHistory)
    {
        std::cout << pieceNames[i.getPiece()] << " " << squareNames[i.getToSquare()] << std::endl;
    }
    return 0;
}
