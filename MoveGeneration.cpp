//
// Created by Jeb Barker on 3/7/23.
//
#include "MoveGeneration.h"

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
    return (pawnPos << 8) & ~(whitePieces | blackPieces) |
         (((pawnPos << 8) & ~(whitePieces | blackPieces) & R3) << 8) & ~(whitePieces | blackPieces) |
         ((((pawnPos & ~H) << 7) | ((pawnPos & ~A) << 9)) & (blackPieces | specialFlags));
}

uint64_t blackPawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags)
{
    return (pawnPos >> 8) & ~(whitePieces | blackPieces) |
           (((pawnPos >> 8) & ~(whitePieces | blackPieces) & R6) >> 8) & ~(whitePieces | blackPieces) |
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

std::vector<Move> pseudoLegalMoves(bool color, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t kingPos, uint64_t knights, uint64_t pawns, uint64_t epFlags)
{
    std::vector<Move> moves;
    //black to move
    if(color)
    {

        uint64_t kingMoves = blackKingMoves(kingPos, whitePieces, blackPieces);
        while((kingMoves & -kingMoves) > 0)
        {
            moves.push_back(Move((kingMoves & -kingMoves), (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingMoves & -kingMoves)) << 4), 0));
            kingMoves ^= (kingMoves & -kingMoves);
        }

        uint64_t knightMoves;
        while((knights & -knights) > 0)
        {
            uint64_t currMove = (knights & -knights);
            knightMoves = blackKnightMoves(currMove, whitePieces, blackPieces);

            while((knightMoves & -knightMoves) > 0)
            {
                moves.push_back(Move(knightMoves & -knightMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(knightMoves & -knightMoves)) << 4), 4) );
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
                moves.push_back(Move(pawnMoves & -pawnMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(pawnMoves & -pawnMoves)) << 4), 5) );
                pawnMoves ^= (pawnMoves & -pawnMoves);
            }
            pawns ^= currMove;
        }

    }
    else
    {
        uint64_t kingMoves = whiteKingMoves(kingPos, whitePieces, blackPieces);
        while((kingMoves & -kingMoves) > 0)
        {
            moves.push_back(Move((kingMoves & -kingMoves), (((squareToSixBit.at(kingPos) << 6) + squareToSixBit.at(kingMoves & -kingMoves)) << 4), 0));
            kingMoves ^= (kingMoves & -kingMoves);
        }

        uint64_t knightMoves;
        while((knights & -knights) > 0)
        {
            uint64_t currMove = (knights & -knights);
            knightMoves = whiteKnightMoves(currMove, whitePieces, blackPieces);

            while((knightMoves & -knightMoves) > 0)
            {
                moves.push_back(Move(knightMoves & -knightMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(knightMoves & -knightMoves)) << 4), 4) );
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
                moves.push_back(Move(pawnMoves & -pawnMoves, (((squareToSixBit.at(currMove) << 6) + squareToSixBit.at(pawnMoves & -pawnMoves)) << 4), 5) );
                pawnMoves ^= (pawnMoves & -pawnMoves);
            }
            pawns ^= currMove;
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





