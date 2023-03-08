#include <iostream>
#include "MoveGeneration.h"

void printBoard(uint64_t wKing=0, uint64_t bKing=0, uint64_t wPawns=0, uint64_t bPawns=0, uint64_t wKnights=0, uint64_t bKnights=0)
{
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 7; j >= 0; j--)
        {
            if((wKing >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "K ";
            else if((bKing >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "k ";
            else if((wPawns >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "P ";
            else if((bPawns >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "p ";
            else if((wKnights >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "N ";
            else if((bKnights >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "n ";
            else
                std::cout << "· ";
        }
        std::cout << std::endl;
    }
}

int main() {
    uint64_t whitePieces = 0x000000000000ff08;
    uint64_t blackPieces = 0x08ff000000000000;
    uint64_t whiteKingPos = 0x0000000000000008;
    uint64_t blackKingPos = 0x0800000000000000;
    uint64_t whiteKnights = 0x0000000000000042;
    uint64_t blackKnights = 0x4200000000000000;
    uint64_t whitePawns = 0x000000000000ff00;
    uint64_t blackPawns = 0x00ff000000000000;

    printBoard(0,blackKingMoves(blackKingPos, whitePieces, blackPieces));
    std::cout << std::endl;
    printBoard(whiteKingPos, blackKingPos, whitePieces, blackPieces, whiteKnights, blackKnights);
    std::vector<uint64_t> moves = pseudoLegalMoves(true, whitePieces, blackPieces, blackKingPos, blackKnights, blackPawns, 0);
    return 0;
}
