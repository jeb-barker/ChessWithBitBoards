//
// Created by Jeb Barker on 3/8/23.
//

#ifndef CHESSWITHBITBOARDS_BOARD_H
#define CHESSWITHBITBOARDS_BOARD_H


#include <cstdint>
#include <string>
#include "Move.h"

class Board {
public:
    uint64_t whitePieces;
    uint64_t blackPieces;
    uint64_t whiteKing;
    uint64_t blackKing;
    uint64_t whiteKnights;
    uint64_t blackKnights;
    uint64_t whitePawns;
    uint64_t blackPawns;
    bool color;

    void printBoard() const;

    Board();

    std::vector<Move> legalMoves();

    void makeMove(Move move);

private:
    uint64_t epFlags;
    uint16_t castlingFlags;
};


#endif //CHESSWITHBITBOARDS_BOARD_H
