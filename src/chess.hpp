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
#include <vector>
#include <array>

// Position on chess board
using Position = std::pair<int, int>;

constexpr std::array<Position, 8> KING_MOVES = {{
  {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}
}};

constexpr std::array<Position, 4> ROOK_MOVES = {{
  {1,0}, {-1,0}, {0,1}, {0,-1}
}};

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


/* White player is the botom player in this representation, position (0,0) represents bottom left corner of the board */
/* First coordinate represents X Axis, second coordinate represents Y Axis */

class Chess
{
  public:
    
    /** Constructor  white is botton player, black is bottom player */
    Chess();
    
    /** Sets up default position for white player being at bottom */
    static std::map<Position, Piece> setup(void);
    
    /** Simple board setup (for showcase and testing */
    static std::map<Position, Piece> simpleSetup(void);

    /** Returns current state of board */
    std::map<Position, Piece> getBoard(void) {return m_pieces;};
    
    /** Check if the move does not put your own king at check */
    bool isCheck(Position pos1, Position pos2);
    
    /** Find all moves for current colour */
    std::vector<std::pair<Position, Position>> findMoves();
    
    /** Validates move for pawn */
    static bool isValidPawnMove(std::map<Position, Piece> pieces, Position pos1, Position pos2);
  
    /** Validates move for king */
    static bool isValidKingMove(std::map<Position, Piece> pieces, Position pos1, Position pos2);
  
    /** Validates move for Rook */
    static bool isValidRookMove(std::map<Position, Piece> pieces, Position pos1, Position pos2);

    /** Checks if move is valid */
    bool isValidMove(Position pos1, Position pos2);

    /** Makes move: Pos1 (from), Pos2 (to) */
    bool makeMove(Position pos1, Position pos2);
    
    /** Returns color of player that is about to move */
    Color toMove();

    /** Returns value (1 = white, 0 = black player */
    size_t evaluate(Color color);
    
  private:
    
    // Current state of the board                                                                                             
    std::map<Position, Piece> m_pieces;
 
    // Who is to move
    Color m_toMove;
};


