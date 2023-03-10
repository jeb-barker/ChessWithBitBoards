//
// Created by Jeb Barker on 3/7/23.
//
#include <iostream>
#include "MoveGeneration.h"
#include <bit>

uint64_t whiteKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces)
{
    return ((kingPos & ~H) << 7 |
            (kingPos & ~H) >> 1 |
            (kingPos & ~H) >> 9 |
            (kingPos & ~A) << 9 |
            (kingPos & ~A) << 1 |
            (kingPos & ~A) >> 7 |
            (kingPos)      << 8 |
            (kingPos)      >> 8) & ~whitePieces;
}

Move kingsideCastle(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces, bool color)
{
    uint64_t notAllPieces = (whitePieces | blackPieces);
    if(((((kingPos >> 1) & notAllPieces) == 0) && (((kingPos >> 2) & notAllPieces) == 0 )))
    {
        return Move(kingPos >> 2, (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingPos >> 2)) << 4) + 0b0010, 0, color);
    }
    return Move(0,0,-1,0);
}

Move queensideCastle(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces, bool color)
{
    uint64_t notAllPieces = (whitePieces | blackPieces);
    if(((((kingPos << 1) & notAllPieces) == 0) && (((kingPos << 2) & notAllPieces) == 0) && (((kingPos << 3) & notAllPieces) == 0)))
    {
        return Move(kingPos << 2, (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingPos << 2)) << 4) + 0b0011, 0, color);
    }
    return Move(0,0,-1,0);
}

uint64_t blackKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces)
{
    return ((kingPos & ~H) << 7 |
            (kingPos & ~H) >> 1 |
            (kingPos & ~H) >> 9 |
            (kingPos & ~A) << 9 |
            (kingPos & ~A) << 1 |
            (kingPos & ~A) >> 7 |
            (kingPos)      << 8 |
            (kingPos)      >> 8) & ~blackPieces;
}

uint64_t whiteKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces)
{
    return ((knightPos & ~G & ~H) << 6  |
            (knightPos & ~G & ~H) >> 10 |
            (knightPos & ~A & ~B) << 10 |
            (knightPos & ~A & ~B) >> 6  |
            (knightPos & ~H)      << 15 |
            (knightPos & ~H)      >> 17 |
            (knightPos & ~A)      << 17 |
            (knightPos & ~A)      >> 15) & ~whitePieces;
}

uint64_t blackKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces)
{
    return ((knightPos & ~G & ~H) << 6  |
            (knightPos & ~G & ~H) >> 10 |
            (knightPos & ~A & ~B) << 10 |
            (knightPos & ~A & ~B) >> 6  |
            (knightPos & ~H)      << 15 |
            (knightPos & ~H)      >> 17 |
            (knightPos & ~A)      << 17 |
            (knightPos & ~A)      >> 15) & ~blackPieces;
}

uint64_t whitePawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags)
{
    return ((pawnPos << 8) & ~(whitePieces | blackPieces)) |
           (((((pawnPos << 8) & ~(whitePieces | blackPieces)) & R3) << 8) & ~(whitePieces | blackPieces)) |
           ((((pawnPos & ~H) << 7) | ((pawnPos & ~A) << 9)) & (blackPieces | specialFlags));
}

uint64_t blackPawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags)
{
    return ((pawnPos >> 8) & ~(whitePieces | blackPieces)) |
           (((((pawnPos >> 8) & ~(whitePieces | blackPieces)) & R6) >> 8) & ~(whitePieces | blackPieces)) |
           ((((pawnPos & ~A) >> 7) | ((pawnPos & ~H) >> 9)) & (whitePieces | specialFlags));
}

uint64_t whitePawnAttacks(uint64_t& pawnPos)
{
    return ((pawnPos & ~H) << 7) | ((pawnPos & ~A) << 9);
}

uint64_t blackPawnAttacks(uint64_t& pawnPos)
{
    return ((pawnPos & ~A) >> 7) | ((pawnPos & ~H) >> 9);
}

uint64_t rookAttacks(uint64_t& rookPos, uint64_t& whitePieces, uint64_t& blackPieces)
{
    uint64_t attacks = 0;
    uint64_t blockers = (whitePieces | blackPieces);
    //north
    attacks |= Rays::rays[0][squareToSixBit.at(rookPos)];
    if((Rays::rays[0][squareToSixBit.at(rookPos)] & blockers) != 0)
    {
        attacks &= ~Rays::rays[0][63 - count_trailing_zeros(Rays::rays[0][squareToSixBit.at(rookPos)] & blockers)];
    }
    //east
    attacks |= Rays::rays[1][squareToSixBit.at(rookPos)];
    if((Rays::rays[1][squareToSixBit.at(rookPos)] & blockers) != 0)
    {
        attacks &= ~Rays::rays[1][count_leading_zeros(Rays::rays[1][squareToSixBit.at(rookPos)] & blockers)];
    }
    //south
    attacks |= Rays::rays[2][squareToSixBit.at(rookPos)];
    if(Rays::rays[2][squareToSixBit.at(rookPos)] & blockers)
    {
        attacks &= ~Rays::rays[2][count_leading_zeros(Rays::rays[2][squareToSixBit.at(rookPos)] & blockers)];
    }
    //west
    attacks |= Rays::rays[3][squareToSixBit.at(rookPos)];
    if(Rays::rays[3][squareToSixBit.at(rookPos)] & blockers)
    {
        attacks &= ~Rays::rays[3][63 - count_trailing_zeros(Rays::rays[3][squareToSixBit.at(rookPos)] & blockers)];
    }
    return attacks;
}

std::vector<Move> pseudoLegalMoves(bool color, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t kingPos, uint64_t knights, uint64_t pawns, uint64_t rooks, uint64_t& epFlags, uint16_t& castlingFlags)
{
    std::vector<Move> moves;
    //black to move
    if(color)
    {
        //black king moves
        uint64_t kingMoves = blackKingMoves(kingPos, whitePieces, blackPieces);
        while((kingMoves & -kingMoves) > 0)
        {
            moves.push_back(Move((kingMoves & -kingMoves), (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingMoves & -kingMoves)) << 4), 0, true));
            kingMoves ^= (kingMoves & -kingMoves);
        }
        //kingside castling:
        if((castlingFlags & 0b0001) == 0b0001)
        {
            Move m = kingsideCastle(kingPos, whitePieces, blackPieces, color);
            if(m.getPiece() != -1)
                moves.push_back(m);
        }
        //queenside castling:
        if((castlingFlags & 0b0010) == 0b0010)
        {
            Move m = queensideCastle(kingPos, whitePieces, blackPieces, color);
            if(m.getPiece() != -1)
                moves.push_back(m);
        }
        uint64_t knightMoves;
        while((knights & -knights) > 0)
        {
            uint64_t currMove = (knights & -knights);
            knightMoves = blackKnightMoves(currMove, whitePieces, blackPieces);

            while((knightMoves & -knightMoves) > 0)
            {
                moves.push_back(Move(knightMoves & -knightMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(knightMoves & -knightMoves)) << 4), 4, true) );
                knightMoves ^= (knightMoves & -knightMoves);
            }
            knights ^= currMove;
        }

        uint64_t pawnMoves;
        while((pawns & -pawns) > 0)
        {
            uint64_t currMove = (pawns & -pawns);
            pawnMoves = blackPawnMoves(currMove, whitePieces, blackPieces, epFlags);

            while((pawnMoves & -pawnMoves) > 0)
            {
                uint16_t ep = 0;
                if(epFlags == (pawnMoves & -pawnMoves))
                {
                    ep = 0b0101;
                }
                moves.push_back(Move(pawnMoves & -pawnMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(pawnMoves & -pawnMoves)) << 4) + ep, 5, true) );
                pawnMoves ^= (pawnMoves & -pawnMoves);
            }
            pawns ^= currMove;
        }

        uint64_t rookMoves;
        while((rooks & -rooks) > 0)
        {
            uint64_t currMove = (rooks & -rooks);
            rookMoves = rookAttacks(currMove, whitePieces, blackPieces);
            //can't capture own pieces
            rookMoves &= ~blackPieces;
            while((rookMoves & -rookMoves) > 0)
            {
                moves.push_back(Move(rookMoves & -rookMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(rookMoves & -rookMoves)) << 4), 2, true) );
                rookMoves ^= (rookMoves & -rookMoves);
            }
            rooks ^= currMove;
        }

    }
    else
    {
        uint64_t kingMoves = whiteKingMoves(kingPos, whitePieces, blackPieces);
        while((kingMoves & -kingMoves) > 0)
        {
            moves.push_back(Move((kingMoves & -kingMoves), (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingMoves & -kingMoves)) << 4), 0, false));
            kingMoves ^= (kingMoves & -kingMoves);
        }

        //castling for white
        if((castlingFlags & 0b0100) == 0b0100)
        {
            Move m = kingsideCastle(kingPos, whitePieces, blackPieces, color);
            if(m.getPiece() != -1)
                moves.push_back(m);
        }
        //queenside castling:
        if((castlingFlags & 0b1000) == 0b1000)
        {
            Move m = queensideCastle(kingPos, whitePieces, blackPieces, color);
            if(m.getPiece() != -1)
                moves.push_back(m);
        }

        uint64_t knightMoves;
        while((knights & -knights) > 0)
        {
            uint64_t currMove = (knights & -knights);
            knightMoves = whiteKnightMoves(currMove, whitePieces, blackPieces);

            while((knightMoves & -knightMoves) > 0)
            {
                moves.push_back(Move(knightMoves & -knightMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(knightMoves & -knightMoves)) << 4), 4, false) );
                knightMoves ^= (knightMoves & -knightMoves);
            }
            knights ^= currMove;
        }

        uint64_t pawnMoves;
        while((pawns & -pawns) > 0)
        {
            uint64_t currMove = (pawns & -pawns);
            pawnMoves = whitePawnMoves(currMove, whitePieces, blackPieces, epFlags);

            while((pawnMoves & -pawnMoves) > 0)
            {
                uint16_t ep = 0;
                if(epFlags == (pawnMoves & -pawnMoves))
                {
                    ep = 0b0101;
                }
                moves.push_back(Move(pawnMoves & -pawnMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(pawnMoves & -pawnMoves)) << 4) + ep, 5, false) );
                pawnMoves ^= (pawnMoves & -pawnMoves);
            }
            pawns ^= currMove;
        }

        uint64_t rookMoves;
        while((rooks & -rooks) > 0)
        {
            uint64_t currMove = (rooks & -rooks);
            rookMoves = rookAttacks(currMove, whitePieces, blackPieces);
            //can't capture own pieces
            rookMoves &= ~whitePieces;
            while((rookMoves & -rookMoves) > 0)
            {
                moves.push_back(Move(rookMoves & -rookMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(rookMoves & -rookMoves)) << 4), 2, false) );
                rookMoves ^= (rookMoves & -rookMoves);
            }
            rooks ^= currMove;
        }

    }
    return moves;
}

void filterLegalMoves(std::vector<Move>& pseudoLegalMoves, bool color, uint64_t myPieces, uint64_t oppPieces, uint64_t kingPos, uint64_t oppKingPos, uint64_t oppKnights, uint64_t oppPawns)
{
    for(int i = 0; i < pseudoLegalMoves.size(); i++)
    {
        Move move = pseudoLegalMoves[i];

        if(color)
        {
            //update king board and piece board.
            //kingPos ^= (move.absoluteMove & -move.absoluteMove);
            myPieces += move.absoluteMove;

            //check for checks.
            uint64_t attacks = whiteKingMoves(oppKingPos, myPieces, oppPieces);
            uint64_t knightAttacks = 0;
            while((oppKnights & -oppKnights) > 0)
            {
                uint64_t knight = (oppKnights & -oppKnights);
                knightAttacks |= whiteKnightMoves(knight, oppPieces, myPieces);
                oppKnights ^= (oppKnights & -oppKnights);
            }
            uint64_t pawnAttacks = 0;
            while((oppPawns & -oppPawns) > 0)
            {
                uint64_t pawn = (oppPawns & -oppPawns);
                pawnAttacks |= whitePawnAttacks(pawn);
                oppPawns ^= (oppPawns & -oppPawns);
            }
            attacks = attacks | knightAttacks | pawnAttacks;
            if(move.getPiece() == 0)
            {
                if( (move.absoluteMove & attacks) != 0 )
                {
                    pseudoLegalMoves.erase(pseudoLegalMoves.begin()+i);
                }
                //check all castling squares
            }
            else
            {
                if( (kingPos & attacks) != 0 )
                {
                    pseudoLegalMoves.erase(pseudoLegalMoves.begin()+i);
                }
            }


            myPieces ^= move.absoluteMove;
        }
        //white
        else
        {
            //update king board and piece board.
            //kingPos ^= (move.absoluteMove & -move.absoluteMove);
            myPieces += move.absoluteMove;

            //check for checks.
            uint64_t attacks = blackKingMoves(oppKingPos, myPieces, oppPieces);
            uint64_t knightAttacks = 0;
            while((oppKnights & -oppKnights) > 0)
            {
                uint64_t knight = (oppKnights & -oppKnights);
                knightAttacks |= blackKnightMoves(knight, myPieces, oppPieces);
                oppKnights ^= (oppKnights & -oppKnights);
            }
            uint64_t pawnAttacks = 0;
            while((oppPawns & -oppPawns) > 0)
            {
                uint64_t pawn = (oppPawns & -oppPawns);
                pawnAttacks |= blackPawnAttacks(pawn);
                oppPawns ^= (oppPawns & -oppPawns);
            }
            attacks = attacks | knightAttacks | pawnAttacks;
            if(move.getPiece() == 0)
            {
                if( (move.absoluteMove & attacks) != 0 )
                {
                    pseudoLegalMoves.erase(pseudoLegalMoves.begin()+i);
                }
                //check all castling squares (and check for if king is in check now)
            }
            else
            {
                if( (kingPos & attacks) != 0 )
                {
                    pseudoLegalMoves.erase(pseudoLegalMoves.begin()+i);
                }
            }
            myPieces ^= move.absoluteMove;
        }
    }
}

uint64_t Rays::rays[8][64];
void Rays::initializeRays()
{
    for(int square = 0; square < 64; square++)
    {
        Rays::rays[0][63-square] = (uint64_t)0x0101010101010100 << square;
        Rays::rays[2][square] = (uint64_t)0x0080808080808080 >> square;
        Rays::rays[1][square] = ((uint64_t)0x7F00000000000000 >> square) & ranks[square / 8];
        Rays::rays[3][63-square] = ((uint64_t)(0x00000000000000FE) << square) & ranks[7-(square / 8)];
    }
    std::cout << "initialized rays" << std::endl;
}

uint64_t count_leading_zeros(uint64_t src)
{
    return __builtin_clzll(src);
}

uint64_t count_trailing_zeros(uint64_t src)
{
    return __builtin_ctzll(src);
}

