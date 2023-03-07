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
    Move();
    explicit Move(uint16_t);

};


#endif //CHESSWITHBITBOARDS_MOVE_H
