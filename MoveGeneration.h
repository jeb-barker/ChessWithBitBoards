//
// Created by Jeb Barker on 3/7/23.
//

#ifndef CHESSWITHBITBOARDS_MOVEGENERATION_H
#define CHESSWITHBITBOARDS_MOVEGENERATION_H

#include <cstdint>
#include <vector>
#include "Move.h"
//define reference table:

//Files
const uint64_t A = 0x8080808080808080;
const uint64_t B = 0x4040404040404040;
const uint64_t C = 0x2020202020202020;
const uint64_t D = 0x1010101010101010;
const uint64_t E = 0x0808080808080808;
const uint64_t F = 0x0404040404040404;
const uint64_t G = 0x0202020202020202;
const uint64_t H = 0x0101010101010101;

//Ranks
const uint64_t R8 = 0xff00000000000000;
const uint64_t R7 = 0x00ff000000000000;
const uint64_t R6 = 0x0000ff0000000000;
const uint64_t R5 = 0x000000ff00000000;
const uint64_t R4 = 0x00000000ff000000;
const uint64_t R3 = 0x0000000000ff0000;
const uint64_t R2 = 0x000000000000ff00;
const uint64_t R1 = 0x00000000000000ff;

//Squares
const uint64_t A1 = A & R1;
const uint64_t A2 = A & R2;
const uint64_t A3 = A & R3;
const uint64_t A4 = A & R4;
const uint64_t A5 = A & R5;
const uint64_t A6 = A & R6;
const uint64_t A7 = A & R7;
const uint64_t A8 = A & R8;

const uint64_t B1 = B & R1;
const uint64_t B2 = B & R2;
const uint64_t B3 = B & R3;
const uint64_t B4 = B & R4;
const uint64_t B5 = B & R5;
const uint64_t B6 = B & R6;
const uint64_t B7 = B & R7;
const uint64_t B8 = B & R8;

const uint64_t C1 = C & R1;
const uint64_t C2 = C & R2;
const uint64_t C3 = C & R3;
const uint64_t C4 = C & R4;
const uint64_t C5 = C & R5;
const uint64_t C6 = C & R6;
const uint64_t C7 = C & R7;
const uint64_t C8 = C & R8;

const uint64_t D1 = D & R1;
const uint64_t D2 = D & R2;
const uint64_t D3 = D & R3;
const uint64_t D4 = D & R4;
const uint64_t D5 = D & R5;
const uint64_t D6 = D & R6;
const uint64_t D7 = D & R7;
const uint64_t D8 = D & R8;

const uint64_t E1 = E & R1;
const uint64_t E2 = E & R2;
const uint64_t E3 = E & R3;
const uint64_t E4 = E & R4;
const uint64_t E5 = E & R5;
const uint64_t E6 = E & R6;
const uint64_t E7 = E & R7;
const uint64_t E8 = E & R8;

const uint64_t F1 = F & R1;
const uint64_t F2 = F & R2;
const uint64_t F3 = F & R3;
const uint64_t F4 = F & R4;
const uint64_t F5 = F & R5;
const uint64_t F6 = F & R6;
const uint64_t F7 = F & R7;
const uint64_t F8 = F & R8;

const uint64_t G1 = G & R1;
const uint64_t G2 = G & R2;
const uint64_t G3 = G & R3;
const uint64_t G4 = G & R4;
const uint64_t G5 = G & R5;
const uint64_t G6 = G & R6;
const uint64_t G7 = G & R7;
const uint64_t G8 = G & R8;

const uint64_t H1 = H & R1;
const uint64_t H2 = H & R2;
const uint64_t H3 = H & R3;
const uint64_t H4 = H & R4;
const uint64_t H5 = H & R5;
const uint64_t H6 = H & R6;
const uint64_t H7 = H & R7;
const uint64_t H8 = H & R8;

const uint64_t files[8] = {
        A,B,C,D,E,F,G,H
};
const uint64_t ranks[8] = {
        R8,R7,R6,R5,R4,R3,R2,R1
};

namespace Rays
{
    extern uint64_t rays[8][64];
    void initializeRays();
}

//uint64_t squares --> 6 bit representation
#include <unordered_map>
const std::unordered_map<uint64_t, uint16_t> squareToSixBit = {
        {A8,0 },{B8,1 },{C8, 2 },{D8,3},{E8, 4},{F8, 5},{G8, 6},{H8, 7},
        {A7,8 },{B7,9 },{C7,10},{D7,11},{E7,12},{F7,13},{G7,14},{H7,15},
        {A6,16},{B6,17},{C6,18},{D6,19},{E6,20},{F6,21},{G6,22},{H6,23},
        {A5,24},{B5,25},{C5,26},{D5,27},{E5,28},{F5,29},{G5,30},{H5,31},
        {A4,32},{B4,33},{C4,34},{D4,35},{E4,36},{F4,37},{G4,38},{H4,39},
        {A3,40},{B3,41},{C3,42},{D3,43},{E3,44},{F3,45},{G3,46},{H3,47},
        {A2,48},{B2,49},{C2,50},{D2,51},{E2,52},{F2,53},{G2,54},{H2,55},
        {A1,56},{B1,57},{C1,58},{D1,59},{E1,60},{F1,61},{G1,62},{H1,63},
};
const uint64_t sixBitToSquare[64] = {
        A8, B8, C8,D8, E8, F8, G8, H8,
        A7, B7, C7,D7, E7, F7, G7, H7,
        A6, B6,C6,D6, E6, F6, G6, H6,
        A5, B5,C5,D5, E5, F5, G5, H5,
        A4, B4,C4,D4, E4, F4, G4, H4,
        A3, B3,C3,D3, E3, F3, G3, H3,
        A2, B2,C2,D2, E2, F2, G2, H2,
        A1, B1,C1,D1, E1, F1, G1, H1,
};
const std::string squareNames[64] = {
        "a8", "b8", "c8","d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7","d7", "e7", "f7", "g7", "h7",
        "a6", "b6","c6","d6", "e6", "f6", "g6", "h6",
        "a5", "b5","c5","d5", "e5", "f5", "g5", "h5",
        "a4", "b4","c4","d4", "e4", "f4", "g4", "h4",
        "a3", "b3","c3","d3", "e3", "f3", "g3", "h3",
        "a2", "b2","c2","d2", "e2", "f2", "g2", "h2",
        "a1", "b1","c1","d1", "e1", "f1", "g1", "h1",
};
const std::string pieceNames[6] = {
        "K", "Q", "R", "B", "N", ""
};

//Piece Move Generators:
//returns pseudo-legal king moves without castling
uint64_t whiteKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t blackKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces);

//returns Move for castling k/q side.
Move kingsideCastle(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces, bool color);
Move queensideCastle(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces, bool color);

//returns pseudo-legal knight moves
uint64_t whiteKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t blackKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces);

//returns pseudo-legal pawn moves with en-passant and without promotion.
uint64_t whitePawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags);
uint64_t blackPawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags);

uint64_t whitePawnAttacks(uint64_t& pawnPos);
uint64_t blackPawnAttacks(uint64_t& pawnPos);


//TODO: sliding piece moves
uint64_t rookAttacks(uint64_t& rookPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t bishopAttacks(uint64_t& bishopPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t queenAttacks(uint64_t queenPos, uint64_t whitePieces, uint64_t blackPieces);

uint64_t count_leading_zeros(uint64_t src);
uint64_t count_trailing_zeros(uint64_t src);

namespace MoveGeneration {
    //full pseudo-legal move generation:
    /**
     * @param color true for black false for white.
     */
    std::vector<Move>
    pseudoLegalMoves(bool color, uint64_t &whitePieces, uint64_t &blackPieces, uint64_t kingPos, uint64_t knights,
                     uint64_t pawns, uint64_t rooks, uint64_t bishops, uint64_t queens, uint64_t &epFlags, uint16_t &castlingFlags);

    void filterLegalMoves(std::vector<Move> &pseudoLegalMoves, bool color, uint64_t myPieces, uint64_t oppPieces,
                          uint64_t kingPos, uint64_t oppKingPos, uint64_t oppKnights, uint64_t oppPawns,
                          uint64_t oppRooks, uint64_t oppBishops, uint64_t oppQueens);
}

#endif //CHESSWITHBITBOARDS_MOVEGENERATION_H


