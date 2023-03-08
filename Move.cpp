//
// Created by Jeb Barker on 3/7/23.
//
#include "Move.h"

Move::Move(uint64_t abs, uint16_t mov, int p)
{
    absoluteMove = abs;
    move = mov;
    piece = p;
}

uint16_t Move::getFromSquare()
{
    return move >> 10;
}

uint16_t Move::getToSquare() {
    return (move >> 4) & 0b111111;
}

uint16_t Move::getFlags() {
    return (move) & 0b1111;
}

int Move::getPiece() {
    return piece;
}
