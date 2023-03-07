//
// Created by Jeb Barker on 3/7/23.
//

#ifndef CHESSWITHBITBOARDS_MOVEGENERATION_H
#define CHESSWITHBITBOARDS_MOVEGENERATION_H

#include <cstdint>
#include <vector>
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

//Sqconst uares
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

//Piece Move Generators:
//returns pseudo-legal king moves without castling
uint64_t whiteKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t blackKingMoves(uint64_t& kingPos, uint64_t& whitePieces, uint64_t& blackPieces);

//returns pseudo-legal knight moves
uint64_t whiteKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces);
uint64_t blackKnightMoves(uint64_t& knightPos, uint64_t& whitePieces, uint64_t& blackPieces);

//returns pseudo-legal pawn moves with en-passant and without promotion.
uint64_t whitePawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags);
uint64_t blackPawnMoves(uint64_t& pawnPos, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t& specialFlags);

//TODO: sliding piece moves

//full pseudo-legal move generation:
/**
 * @param color true for black false for white.
 */
std::vector<uint64_t> pseudoLegalMoves(bool color, uint64_t& whitePieces, uint64_t& blackPieces, uint64_t kingPos, uint64_t knights, uint64_t pawns, uint64_t epFlags);
#endif //CHESSWITHBITBOARDS_MOVEGENERATION_H


