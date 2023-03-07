cmake_minimum_required(VERSION 3.24)
project(ChessWithBitBoards)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessWithBitBoards main.cpp MoveGeneration.h MoveGeneration.cpp Move.cpp Move.h)
