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
            else if((whiteBishops >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "B ";
            else if((blackBishops >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "b ";
            else if((whiteQueens >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "Q ";
            else if((blackQueens >> ((i*8) + j) & 0b1) == 0b1)
                std::cout << "q ";
            else
                std::cout << "· ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Board::Board()
{
    whitePieces =  0x000000000000ffff;
    whiteKing =    0x0000000000000008;
    whitePawns =   0x000000000000ff00;
    whiteKnights = 0x0000000000000042;
    whiteRooks =   0x0000000000000081;
    whiteBishops = 0x0000000000000024;
    whiteQueens =  0x0000000000000010;

    blackPieces =  0xffff000000000000;
    blackKing =    0x0800000000000000;
    blackPawns =   0x00ff000000000000;
    blackKnights = 0x4200000000000000;
    blackRooks =   0x8100000000000000;
    blackBishops = 0x2400000000000000;
    blackQueens =  0x1000000000000000;

    color = false;

    epFlags = 0;
    castlingFlags = 0b1111;

    moveHistory = std::vector<Move>();
}

Board::Board(bool color, uint64_t whitePieces, uint64_t blackPieces, uint64_t whiteKing, uint64_t blackKing, uint64_t whiteKnights,
             uint64_t blackKnights, uint64_t whitePawns, uint64_t blackPawns, uint64_t whiteRooks, uint64_t blackRooks,
             uint64_t whiteBishops, uint64_t blackBishops, uint64_t whiteQueens, uint64_t blackQueens)
{
    this->whitePieces =  whitePieces;
    this->whiteKing =    whiteKing;
    this->whitePawns =   whitePawns;
    this->whiteKnights = whiteKnights;
    this->whiteRooks =   whiteRooks;
    this->whiteBishops = whiteBishops;
    this->whiteQueens =  whiteQueens;

    this->blackPieces =  blackPieces;
    this->blackKing =    blackKing;
    this->blackPawns =   blackPawns;
    this->blackKnights = blackKnights;
    this->blackRooks =   blackRooks;
    this->blackBishops = blackBishops;
    this->blackQueens =  blackQueens;

    this->color = color;
    epFlags = 0;
    castlingFlags = 0b0000;
    moveHistory = std::vector<Move>();
}

std::vector<Move> Board::legalMoves()
{
    if(color)
    {
        std::vector<Move> moves = MoveGeneration::pseudoLegalMoves(color, whitePieces, blackPieces, blackKing, blackKnights, blackPawns, blackRooks, blackBishops, blackQueens, epFlags, castlingFlags);
        MoveGeneration::filterLegalMoves(moves, color, blackPieces, whitePieces, blackKing, whiteKing, whiteKnights, whitePawns, whiteRooks, whiteBishops, whiteQueens);
        return moves;
    }
    else
    {
        std::vector<Move> moves = MoveGeneration::pseudoLegalMoves(color, whitePieces, blackPieces, whiteKing, whiteKnights, whitePawns, whiteRooks, whiteBishops, whiteQueens, epFlags, castlingFlags);
        MoveGeneration::filterLegalMoves(moves, color, whitePieces, blackPieces, whiteKing, blackKing, blackKnights, blackPawns, blackRooks, blackBishops, blackQueens);
        return moves;
    }
}

void Board::makeMove(Move move)
{
    if(move.absoluteMove == 0)
    {
        return;
    }
    uint64_t fromSquare = sixBitToSquare[move.getFromSquare()];
    uint64_t toSquare = sixBitToSquare[move.getToSquare()];
    if(color)
    {
        //all pieces
        blackPieces ^= fromSquare;
        blackPieces ^= toSquare;
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
            blackKnights ^= toSquare;
        }
        else if(move.piece == 5)
        {
            //pawns
            blackPawns ^= fromSquare;
            //knight
            if(move.getFlags() == 0b0110)
            {
                blackKnights ^= toSquare;
            }
            //bishop
            if(move.getFlags() == 0b0111)
            {
                blackBishops ^= toSquare;
            }
            //rook
            if(move.getFlags() == 0b1000)
            {
                blackRooks ^= toSquare;
            }
            //queen
            if(move.getFlags() == 0b1001)
            {
                blackQueens ^= toSquare;
            }
            //no promotion
            else
            {
                blackPawns ^= toSquare;

                //en passant
                if (((fromSquare & R7) != 0) & ((toSquare & R5) != 0))
                {
                    //to undo this you need to go back two moves.
                    epFlags = fromSquare >> 8;
                }
                if (move.getFlags() == 0b0101)
                {
                    toSquare = toSquare << 8;
                    if(epFlags != 0)
                    {
                        epFlags = 0;
                    }
                }
            }
        }
        else if(move.piece == 2)
        {
            //rooks
            blackRooks ^= fromSquare;
            blackRooks ^= toSquare;
            if(fromSquare == A8)
            {
                castlingFlags &= 0b1101;
            }
            else if(fromSquare == H8)
            {
                castlingFlags &= 0b1110;
            }
        }
        else if(move.piece == 3)
        {
            //bishops
            blackBishops ^= fromSquare;
            blackBishops ^= toSquare;
        }
        else if(move.piece == 1)
        {
            //queens
            blackQueens ^= fromSquare;
            blackQueens ^= toSquare;
        }

        //captures
        if((whiteKing & toSquare) != 0)
            whiteKing ^= toSquare;
        if((whiteKnights & toSquare) != 0)
            whiteKnights ^= toSquare;
        if((whitePawns & toSquare) != 0)
            whitePawns ^= toSquare;
        if((whiteRooks & toSquare) != 0)
            whiteRooks ^= toSquare;
        if((whiteBishops & toSquare) != 0)
            whiteBishops ^= toSquare;
        if((whiteQueens & toSquare) != 0)
            whiteQueens ^= toSquare;
        if((whitePieces & toSquare) != 0)
            whitePieces ^= toSquare;

    }
    else
    {
        //all pieces
        whitePieces ^= fromSquare;
        whitePieces ^= toSquare;
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
            whiteKnights ^= toSquare;
        }
        else if(move.piece == 5)
        {
            //pawns
            whitePawns ^= fromSquare;
            //en-passant and promotion should be handled here.
            //knight
            if(move.getFlags() == 0b0110)
            {
                whiteKnights ^= toSquare;
            }
            //bishop
            if(move.getFlags() == 0b0111)
            {
                whiteBishops ^= toSquare;
            }
            //rook
            if(move.getFlags() == 0b1000)
            {
                whiteRooks ^= toSquare;
            }
            //queen
            if(move.getFlags() == 0b1001)
            {
                whiteQueens ^= toSquare;
            }
            else
            {
                whitePawns ^= toSquare;
                //en passant should be "turned on"
                if (((fromSquare & R2) != 0) & ((toSquare & R4) != 0))
                {
                    epFlags = fromSquare << 8;
                }
                //en passant was performed
                if (move.getFlags() == 0b0101)
                {
                    toSquare = toSquare >> 8;
                    if(epFlags != 0)
                    {
                        epFlags = 0;
                    }
                }
            }
        }
        else if(move.piece == 2)
        {
            //rooks
            whiteRooks ^= fromSquare;
            whiteRooks ^= toSquare;
            if(fromSquare == A1)
            {
                castlingFlags &= 0b0111;
            }
            else if(fromSquare == H1)
            {
                castlingFlags &= 0b1011;
            }
        }
        else if(move.piece == 3)
        {
            //bishops
            whiteBishops ^= fromSquare;
            whiteBishops ^= toSquare;
        }
        else if(move.piece == 1)
        {
            //queens
            whiteQueens ^= fromSquare;
            whiteQueens ^= toSquare;
        }

        if((blackKing & toSquare) != 0)
            blackKing ^= toSquare;
        if((blackKnights & toSquare) != 0)
            blackKnights ^= toSquare;
        if((blackPawns & toSquare) != 0)
            blackPawns ^= toSquare;
        if((blackRooks & toSquare) != 0)
            blackRooks ^= toSquare;
        if((blackBishops & toSquare) != 0)
            blackBishops ^= toSquare;
        if((blackQueens & toSquare) != 0)
            blackQueens ^= toSquare;
        if((blackPieces & toSquare) != 0)
            blackPieces ^= toSquare;
    }
    color = !color;
    moveHistory.emplace_back(move);
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

bool Board::isGameOver()
{
    std::vector<Move> lm = legalMoves();
    return lm.empty() | isThreefoldRepetition();
}

bool Board::isThreefoldRepetition()
{
    //alternate board for testing.
//    uint64_t whitePieces2 =  0x0010000000000001;
//    uint64_t king =    0x0000000000000001;
//    uint64_t pawns =   0x0010000000000000;
//    uint64_t knights = 0x0000000000000000;
//    uint64_t rooks =   0x0000000000000000;
//    uint64_t bishops = 0x0000000000000000;
//    uint64_t queens =  0x0000000000000000;
//
//    uint64_t pieces =  0x0000000000000004;
//    uint64_t bKing =    0x0000000000000004;
//    uint64_t i =   0x0000000000000000;
//    uint64_t bKN = 0x0000000000000000;
//    uint64_t Brook =   0x0000000000000000;
//    uint64_t bbish = 0x0000000000000000;
//    uint64_t bQueen =  0x0000000000000000;
    //Board b2 = Board(false, whitePieces2, pieces, king, bKing, knights, bKN, pawns, i, rooks, Brook, bishops, bbish, queens, bQueen);
    Board b2 = Board();
    int repeatCount = 0;
    for(Move m : moveHistory)
    {
        if(equals(b2))
        {
            repeatCount++;
        }
        b2.makeMove(m);
    }
    if(repeatCount >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::equals(Board other)
{
    return whitePieces == other.whitePieces && blackPieces == other.blackPieces && whiteRooks == other.whiteRooks && blackRooks == other.blackRooks
    && whiteQueens == other.whiteQueens && blackQueens == other.blackQueens && whiteBishops == other.whiteBishops && blackBishops == other.blackBishops
    && whiteKing == other.whiteKing && blackKing == other.blackKing && whiteKnights == other.whiteKnights && blackKnights == other.blackKnights
    && whitePawns == other.whitePawns && blackPawns == other.blackPawns;
}

bool Board::isCheck()
{
    uint64_t knights;
    uint64_t rooks;
    uint64_t pawns;
    uint64_t bishops;
    uint64_t queens;
    uint64_t oPieces;
    uint64_t mPieces;


    if(color)
    {
        knights = whiteKnights;
        rooks = whiteRooks;
        pawns = whitePawns;
        bishops = whiteBishops;
        queens = whiteQueens;
        oPieces = whitePieces;
        mPieces = blackPieces;
        //check for checks.
        uint64_t attacks = whiteKingMoves(whiteKing, oPieces, mPieces);
        uint64_t knightAttacks = 0;
        while((knights & -knights) > 0)
        {
            uint64_t knight = (knights & -knights);
            knightAttacks |= whiteKnightMoves(knight, oPieces, mPieces);
            knights ^= knight;
        }
        uint64_t pawnAttacks = 0;
        while((pawns & -pawns) > 0)
        {
            uint64_t pawn = (pawns & -pawns);
            pawnAttacks |= whitePawnAttacks(pawn);
            pawns ^= pawn;
        }
        uint64_t rookAttacksint = 0;
        while((rooks & -rooks) > 0)
        {
            uint64_t rook = (rooks & -rooks);
            rookAttacksint |= rookAttacks(rook, mPieces, oPieces);
            rooks ^= rook;
        }
        uint64_t bishopAttacksint = 0;
        while((bishops & -bishops) > 0)
        {
            uint64_t bishop = (bishops & -bishops);
            bishopAttacksint |= bishopAttacks(bishop, mPieces, oPieces);
            bishops ^= bishop;
        }
        uint64_t queenAttacksint = 0;
        while((queens & -queens) > 0)
        {
            uint64_t queen = (queens & -queens);
            queenAttacksint |= queenAttacks(queen, mPieces, oPieces);
            queens ^= queen;
        }

        attacks = attacks | knightAttacks | pawnAttacks | rookAttacksint | bishopAttacksint | queenAttacksint;
        if( (blackKing & attacks) != 0b0)
        {
            return true;
        }
    }
        //white
    else
    {
        knights = blackKnights;
        rooks = blackRooks;
        pawns = blackPawns;
        bishops = blackBishops;
        queens = blackQueens;
        oPieces = blackPieces;
        mPieces = whitePieces;
        //check for checks.
        uint64_t attacks = blackKingMoves(blackKing, whitePieces, blackPieces);
        uint64_t knightAttacks = 0;
        while((knights & -knights) > 0)
        {
            uint64_t knight = (knights & -knights);
            knightAttacks |= blackKnightMoves(knight, mPieces, oPieces);
            knights ^= knight;
        }
        uint64_t pawnAttacks = 0;
        while((pawns & -pawns) > 0)
        {
            uint64_t pawn = (pawns & -pawns);
            pawnAttacks |= blackPawnAttacks(pawn);
            pawns ^= pawn;
        }
        uint64_t rookAttacksint = 0;
        while((rooks & -rooks) > 0)
        {
            uint64_t rook = (rooks & -rooks);
            rookAttacksint |= rookAttacks(rook, mPieces, oPieces);
            rooks ^= rook;
        }
        uint64_t bishopAttacksint = 0;
        while((bishops & -bishops) > 0)
        {
            uint64_t bishop = (bishops & -bishops);
            bishopAttacksint |= bishopAttacks(bishop, mPieces, oPieces);
            bishops ^= bishop;
        }
        uint64_t queenAttacksint = 0;
        while((queens & -queens) > 0)
        {
            uint64_t queen = (queens & -queens);
            queenAttacksint |= queenAttacks(queen, mPieces, oPieces);
            queens ^= queen;
        }

        attacks = attacks | knightAttacks | pawnAttacks | rookAttacksint | bishopAttacksint | queenAttacksint;
        if( (whiteKing & attacks) != 0)
        {
            return true;
        }
    }
    return false;
}


