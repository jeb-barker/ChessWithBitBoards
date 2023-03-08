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
    Move(uint64_t abs, uint16_t mov);
    uint16_t getFromSquare();
    uint16_t getToSquare();
    uint16_t getFlags();
};


#endif //CHESSWITHBITBOARDS_MOVE_H
