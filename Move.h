//
// Created by Jeb Barker on 3/7/23.
//

#ifndef CHESSWITHBITBOARDS_MOVE_H
#define CHESSWITHBITBOARDS_MOVE_H


#include <cstdint>
#include <string>

class Move {
public:
    uint64_t absoluteMove;
    uint16_t move;
    int piece;
    Move(uint64_t abs, uint16_t mov, int piece);
    uint16_t getFromSquare();
    uint16_t getToSquare();
    uint16_t getFlags();
    int getPiece();
};


#endif //CHESSWITHBITBOARDS_MOVE_H
