/**
 * @file chess.hpp
 * @author Ondrej
 * @brief Chess board representation
 *
*/

#pragma once

#include <utility>
#include <cstddef> 
#include <map>

// Position on chess board
using Position = std::pair<int, int>;

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

class Chess
{
  public:
    
    /** Constructor - 1 = white is botton player, 0 = black is bottom player */
    Chess(Color color);
    
    /** Sets up default position for white player being at bottom */
    static std::map<Position, Piece> setupWhite(void);
    
    /** Sets up default position for black player being at bottom */
    static std::map<Position, Piece> setupBlack(void);

    /** Returns current state of board */
    std::map<Position, Piece> getBoard(void) {return m_pieces;};
    
    /** Checks if move is valid */
    bool isValidMove(Position pos1, Position pos2, Piece piece1, Piece piece2);

    /** Makes move: Pos1 (from), Pos2 (to) */
    bool makeMove(Position pos1, Position pos2);
    
    /** Returns value (1 = white, 0 = black player */
    size_t value(Color color);

  private:
    
    // Current state of the board                                                                                             
    std::map<Position, Piece> m_pieces;
 
    // If white player is on the botton
    Color m_bottomPlayer;
    
    // Who is to move
    Color m_toMove;
};


