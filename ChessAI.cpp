//
// Created by Jeb Barker on 3/11/23.
//

#include <iostream>
#include "ChessAI.h"
#include "MoveGeneration.h"

const int CHESS_MIN = -1000000;
const int CHESS_MAX =  1000000;

MoveEval ChessAI::minValue(Board board, int alpha, int beta, Move move, int depth, bool color) {
    board.makeMove(move);
    std::vector<Move> lm = board.legalMoves();
    int eval = gameStatus(board, lm);
    if(eval != 0)
    {
        MoveEval e = MoveEval();

        e.v = eval;
        e.m = move;
        return e;
    }
    if(depth == 0)
    {
        MoveEval e = MoveEval();

        e.v = evaluate(board, lm, color);
        e.m = move;
        return e;
    }
    MoveEval e = MoveEval();
    e.v = CHESS_MAX;
    e.m = move;

    for(Move m : lm)
    {
        MoveEval max = maxValue(board, alpha, beta, m, depth - 1, color);
        if(max.v < e.v)
        {
            e.v = max.v;
            e.m = m;
        }
        if(e.v < alpha)
        {
            return e;
        }
        beta = std::min(e.v, beta);
    }
    return e;
}

MoveEval ChessAI::maxValue(Board board, int alpha, int beta, Move move, int depth, bool color) {
    board.makeMove(move);
    std::vector<Move> lm = board.legalMoves();
    int eval = gameStatus(board, lm);
    if(eval != 0)
    {
        MoveEval e = MoveEval();

        e.v = eval;
        e.m = move;
        return e;
    }
    if(depth == 0)
    {
        MoveEval e = MoveEval();

        e.v = evaluate(board, lm, color);
        e.m = move;
        return e;
    }
    MoveEval e = MoveEval();
    e.v = CHESS_MIN;
    e.m = move;

    for(Move m : lm)
    {
        MoveEval min = minValue(board, alpha, beta, m, depth - 1, color);
        if(min.v > e.v)
        {
            e.v = min.v;
            e.m = m;
        }
        if(e.v > beta)
        {
            //early exit
            return e;
        }
        alpha = std::max(e.v, alpha);
    }
    return e;
}

Move ChessAI::alphaBeta(Board board, int minDepth, int maxDepth, int maxTime, bool color) {
    MoveEval currentMove = MoveEval();
    for(int d = minDepth; d <= maxDepth; d++)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        if (color)
        {
            currentMove = minValue(board, CHESS_MIN, CHESS_MAX, Move(0,0,0,false), d, true);
        }
        else
        {
            currentMove = maxValue(board, CHESS_MIN, CHESS_MAX, Move(0,0,0,false), d, false);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "Depth " << d << " completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << std::endl;
        std::cout << "Depth Eval: " << currentMove.v << std::endl;
    }
    //TODO: intercept timout error.
    return currentMove.m;
}

int ChessAI::evaluate(Board& b, std::vector<Move>& lm, bool& color) {
    int pieceVal = 0;
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 7; j >= 0; j--)
        {
            if((b.whitePawns >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal += 1;
            else if((b.blackPawns >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal -= 1;
            else if((b.whiteKnights >> ((i*8) + j) & 0b1) == 0b1)
            {
                pieceVal += 3;
            }
            else if((b.blackKnights >> ((i*8) + j) & 0b1) == 0b1)
            {
                pieceVal -= 3;
            }
            else if((b.whiteRooks >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal += 5;
            else if((b.blackRooks >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal -= 5;
            else if((b.whiteBishops >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal += 3;
            else if((b.blackBishops >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal -= 3;
            else if((b.whiteQueens >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal += 9;
            else if((b.blackQueens >> ((i*8) + j) & 0b1) == 0b1)
                pieceVal -= 3;
        }
    }


    int centerAttacks = 0;
    if((b.whitePieces & E4) != 0  || (b.whitePieces & D4) != 0)
    {
        centerAttacks++;
    }
    if((b.blackPieces & E5) != 0  || (b.blackPieces & D5) != 0)
    {
        centerAttacks--;
    }


    return pieceVal + centerAttacks;
}

int ChessAI::gameStatus(Board &b, std::vector<Move>& lm) {
    if(b.isGameOver())
    {
        if(b.isCheck())
        {
            if(b.color)
            {
                return CHESS_MAX - 1;
            }
            else
            {
                return CHESS_MIN + 1;
            }
        }
        else
        {
            return -1;
        }
        //no legal moves check for stalemate or checkmate.
        //Uncomment to print checkmates and stalemates.
        //b.printBoard();
        if(b.color)
        {
            //if in check return max - 1
            if(b.isCheck())
            {
                return CHESS_MAX - 1;
            }
            else
            {
                return -20;
            }
            //else stalemate return min+2
        }
        else
        {
            //if in check return min + 1
            if(b.isCheck())
            {
                return CHESS_MIN + 1;
            }
            else
            {
                return 20;
            }
            //else stalemate return max - 2
        }
        //return -1;
        //return -Max or Max based on who got checkmated.
    }
    return 0;
}
