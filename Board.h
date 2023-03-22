//
// Created by Jeb Barker on 3/8/23.
//

#ifndef CHESSWITHBITBOARDS_BOARD_H
#define CHESSWITHBITBOARDS_BOARD_H


#include <cstdint>
#include <string>
#include <vector>
#include "Move.h"

class Board {
public:
    std::vector<Move> moveHistory;
    uint64_t whitePieces;
    uint64_t blackPieces;
    uint64_t whiteKing;
    uint64_t blackKing;
    uint64_t whiteKnights;
    uint64_t blackKnights;
    uint64_t whitePawns;
    uint64_t blackPawns;
    uint64_t whiteRooks;
    uint64_t blackRooks;
    uint64_t whiteBishops;
    uint64_t blackBishops;
    uint64_t whiteQueens;
    uint64_t blackQueens;
    bool color;

    void printBoard() const;
    static void printMoveset(uint64_t moveSet);

    Board();
    Board(bool color, uint64_t whitePieces,
    uint64_t blackPieces,
    uint64_t whiteKing,
    uint64_t blackKing,
    uint64_t whiteKnights,
    uint64_t blackKnights,
    uint64_t whitePawns,
    uint64_t blackPawns,
    uint64_t whiteRooks,
    uint64_t blackRooks,
    uint64_t whiteBishops,
    uint64_t blackBishops,
    uint64_t whiteQueens,
    uint64_t blackQueens);

    std::vector<Move> legalMoves();
    void filterLegalMoves(std::vector<Move>& pseudoLegalMoves);

    void makeMove(Move move);

    bool isGameOver();
    bool isThreefoldRepetition();
    bool isCheck();
    bool equals(Board other);

private:
    uint64_t epFlags;
    uint16_t castlingFlags;

};


#endif //CHESSWITHBITBOARDS_BOARD_H
