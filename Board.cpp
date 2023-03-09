//
// Created by Jeb Barker on 3/8/23.
//

#include <iostream>
#include "Board.h"
#include "MoveGeneration.h"

void Board::printBoard()
{
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 7; j >= 0; j--)
        {
            if((whiteKing >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "K ";
            else if((blackKing >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "k ";
            else if((whitePawns >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "P ";
            else if((blackPawns >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "p ";
            else if((whiteKnights >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "N ";
            else if((blackKnights >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "n ";
            else
                std::cout << "· ";
        }
        std::cout << std::endl;
    }
}

Board::Board()
{
    whitePieces = 0x000000000000ff08;
    whiteKing = 0x0000000000000008;
    whitePawns = 0x000000000000ff00;
    whiteKnights = 0x0000000000000042;

    blackPieces = 0x08ff000000000000;
    blackKing = 0x0800000000000000;
    blackPawns = 0x00ff000000000000;
    blackKnights = 0x4200000000000000;

    color = false;
}

std::vector<Move> Board::legalMoves()
{
    if(color)
    {
        std::vector<Move> moves = pseudoLegalMoves(color, whitePieces, blackPieces, blackKing, blackKnights, blackPawns, 0);
        filterLegalMoves(moves, color, blackPieces, whitePieces, blackKing, whiteKing, whiteKnights, whitePawns);
        return moves;
    }
    else
    {
        std::vector<Move> moves = pseudoLegalMoves(color, whitePieces, blackPieces, whiteKing, whiteKnights, whitePawns, 0);
        filterLegalMoves(moves, color, whitePieces, blackPieces, whiteKing, blackKing, blackKnights, blackPawns);
        return moves;
    }
}

void Board::makeMove(Move move)
{
    uint64_t fromSquare = sixBitToSquare[move.getFromSquare()];
    uint64_t toSquare = sixBitToSquare[move.getToSquare()];
    if(color)
    {
        if(move.piece == 0)
        {
            //king
            blackKing = move.absoluteMove;
        }
        else if(move.piece == 4)
        {
            //knights
            blackKnights ^= fromSquare;
            blackKnights += toSquare;
        }
        else if(move.piece == 5)
        {
            //pawns
            //en-passant and promotion should be handled here.
            blackPawns ^= fromSquare;
            blackPawns += toSquare;
        }
        //all pieces
        blackPieces ^= fromSquare;
        blackPieces += toSquare;

        //captures
        if((whiteKing & toSquare) != 0)
            whiteKing ^= toSquare;
        if((whiteKnights & toSquare) != 0)
            whiteKnights ^= toSquare;
        if((whitePawns & toSquare) != 0)
            whitePawns ^= toSquare;
        if((whitePieces & toSquare) != 0)
            whitePieces ^= toSquare;

    }
    else
    {
        if(move.piece == 0)
        {
            //king
            whiteKing = move.absoluteMove;
        }
        else if(move.piece == 4)
        {
            //knights
            whiteKnights ^= fromSquare;
            whiteKnights += toSquare;
        }
        else if(move.piece == 5)
        {
            //pawns
            whitePawns ^= fromSquare;
            whitePawns += toSquare;
        }
        //all pieces
        whitePieces ^= fromSquare;
        whitePieces += toSquare;

        if((blackKing & toSquare) != 0)
            blackKing ^= toSquare;
        if((blackKnights & toSquare) != 0)
            blackKnights ^= toSquare;
        if((blackPawns & toSquare) != 0)
            blackPawns ^= toSquare;
        if((blackPieces & toSquare) != 0)
            blackPieces ^= toSquare;
    }
    color = !color;
}


#include "Board.h"
