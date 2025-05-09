/**
 * @file engine.hpp
 * @author Ondrej
 * @brief Chess engine class
 *
*/

#pragma once

#include <utility>
#include <cstddef> 

// Position on chess board
using Position = std::pair<size_t, size_t>;

enum class Color
{
  White, 
  Black
};

enum class PieceType
{
  King,
  Queen,
  Rook,
  Bishop,
  Knight,
  Pawn,
};

struct Piece
{
  Color color;
  PieceType type;
};
