//
// Created by Jeb Barker on 3/8/23.
//

#include <iostream>
#include "Board.h"
#include "MoveGeneration.h"

void Board::printBoard() const
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
            else if((whiteRooks >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "R ";
            else if((blackRooks >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "r ";
            else
                std::cout << "· ";
        }
        std::cout << std::endl;
    }
}

Board::Board()
{
    whitePieces =  0x000000000000ffCB;
    whiteKing =    0x0000000000000008;
    whitePawns =   0x000000000000ff00;
    whiteKnights = 0x0000000000000042;
    whiteRooks =   0x0000000000000081;

    blackPieces =  0xCBff000000000000;
    blackKing =    0x0800000000000000;
    blackPawns =   0x00ff000000000000;
    blackKnights = 0x4200000000000000;
    blackRooks =   0x8100000000000000;

    color = false;

    epFlags = 0;
    castlingFlags = 0b1111;

    moveHistory = std::vector<Move>();
}

std::vector<Move> Board::legalMoves()
{
    if(color)
    {
        std::vector<Move> moves = pseudoLegalMoves(color, whitePieces, blackPieces, blackKing, blackKnights, blackPawns, blackRooks, epFlags, castlingFlags);
        filterLegalMoves(moves, color, blackPieces, whitePieces, blackKing, whiteKing, whiteKnights, whitePawns);
        return moves;
    }
    else
    {
        std::vector<Move> moves = pseudoLegalMoves(color, whitePieces, blackPieces, whiteKing, whiteKnights, whitePawns, whiteRooks, epFlags, castlingFlags);
        filterLegalMoves(moves, color, whitePieces, blackPieces, whiteKing, blackKing, blackKnights, blackPawns);
        return moves;
    }
}

void Board::makeMove(Move move)
{
    uint64_t fromSquare = sixBitToSquare[move.getFromSquare()];
    uint64_t toSquare = sixBitToSquare[move.getToSquare()];
    if(epFlags != 0)
    {
        epFlags = 0;
    }
    if(color)
    {
        //all pieces
        blackPieces ^= fromSquare;
        blackPieces += toSquare;
        if(move.piece == 0)
        {
            //king
            blackKing = move.absoluteMove;
            if(move.getFlags() == 0b0010)
            {
                //kingside castling: update rook and pieces.
                blackRooks ^= H8;
                blackRooks ^= F8;
                blackPieces ^= H8;
                blackPieces ^= F8;
            }
            if(move.getFlags() == 0b0011)
            {
                //queenside castling: update rook and pieces.
                blackRooks ^= A8;
                blackRooks ^= D8;
                blackPieces ^= A8;
                blackPieces ^= D8;
            }
            castlingFlags &= 0b1100;
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

            //en passant
            if(((fromSquare & R7) != 0) & ((toSquare & R5) != 0))
            {
                epFlags = fromSquare >> 8;
            }
            if(move.getFlags() == 0b0101)
            {
                toSquare = toSquare << 8;
            }
        }
        else if(move.piece == 2)
        {
            //rooks
            blackRooks ^= fromSquare;
            blackRooks += toSquare;
            if(fromSquare == A8)
            {
                castlingFlags &= 0b0111;
            }
            else if(fromSquare == H8)
            {
                castlingFlags &= 0b1011;
            }
        }

        //captures
        if((whiteKing & toSquare) != 0)
            whiteKing ^= toSquare;
        if((whiteKnights & toSquare) != 0)
            whiteKnights ^= toSquare;
        if((whitePawns & toSquare) != 0)
            whitePawns ^= toSquare;
        if((whiteRooks & toSquare) != 0)
            whitePieces ^= toSquare;
        if((whitePieces & toSquare) != 0)
            whitePieces ^= toSquare;

    }
    else
    {
        //all pieces
        whitePieces ^= fromSquare;
        whitePieces += toSquare;
        if(move.piece == 0)
        {
            //king
            whiteKing = move.absoluteMove;
            if(move.getFlags() == 0b0010)
            {
                //kingside castling: update rook and pieces.
                whiteRooks ^= H1;
                whiteRooks ^= F1;
                whitePieces ^= H1;
                whitePieces ^= F1;
            }
            if(move.getFlags() == 0b0011)
            {
                //queenside castling: update rook and pieces.
                whiteRooks ^= A1;
                whiteRooks ^= D1;
                whitePieces ^= A1;
                whitePieces ^= D1;
            }
            castlingFlags &= 0b0011;
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

            //en passant should be "turned on"
            if(((fromSquare & R2) != 0) & ((toSquare & R4) != 0))
            {
                epFlags = fromSquare << 8;
            }
            //en passant was performed
            if(move.getFlags() == 0b0101)
            {
                toSquare = toSquare >> 8;
            }
        }
        else if(move.piece == 2)
        {
            //rooks
            whiteRooks ^= fromSquare;
            whiteRooks += toSquare;
            if(fromSquare == A1)
            {
                castlingFlags &= 0b0111;
            }
            else if(fromSquare == H1)
            {
                castlingFlags &= 0b1011;
            }
        }

        if((blackKing & toSquare) != 0)
            blackKing ^= toSquare;
        if((blackKnights & toSquare) != 0)
            blackKnights ^= toSquare;
        if((blackPawns & toSquare) != 0)
            blackPawns ^= toSquare;
        if((blackRooks & toSquare) != 0)
            blackRooks ^= toSquare;
        if((blackPieces & toSquare) != 0)
            blackPieces ^= toSquare;
    }
    color = !color;
    moveHistory.push_back(move);
}

void Board::printMoveset(uint64_t moveSet) {
    for(int i = 7; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            if ((moveSet >> ((i * 8) + j) & 0b1) == 0b1)
                std::cout << "X ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

