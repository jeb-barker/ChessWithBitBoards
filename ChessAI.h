//
// Created by Jeb Barker on 3/11/23.
//

#ifndef CHESSWITHBITBOARDS_CHESSAI_H
#define CHESSWITHBITBOARDS_CHESSAI_H


#include "Move.h"
#include "Board.h"

class MoveEval
{
public:
    int v = 0;
    Move m = Move(0, 0, 0, false);
};

class ChessAI {

private:
    static MoveEval minValue(Board board, int alpha, int beta, Move move, int depth, bool color);
    static MoveEval maxValue(Board board, int alpha, int beta, Move move, int depth, bool color);
    static int evaluate(Board& b, std::vector<Move>& lm, bool& color);
    static int gameStatus(Board& b, std::vector<Move>& lm);
public:
    static Move alphaBeta(Board board, int minDepth, int maxDepth, int maxTime, bool color);
};


#endif //CHESSWITHBITBOARDS_CHESSAI_H
