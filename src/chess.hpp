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
#include <stack>

// Position on chess board
using Position = std::pair<int, int>;

#define BOARD_SIZE 5

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
  Empty
};

struct Piece
{
  Color color;
  PieceType type;
};

struct Move
{
  Position from;
  Position to;
  Piece movedPiece;
  Piece capturedPiece;
  bool wasFirstMove;
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
    static std::map<Position, Piece> simpleSetup1(void);

    /** Simple board setup (for showcase and testing */
    static std::map<Position, Piece> simpleSetup2(void);

    /** Simple board setup (for showcase and testing */
    static std::map<Position, Piece> simpleSetup3(void);

    /** Returns current state of board */
    std::map<Position, Piece> getBoard(void) {return m_pieces;};
    
    /** Check if the move does not put your own king at check */
    bool isCheck(Position pos1, Position pos2);
    
    /** Check if the move checks other king */
    bool isChecking();

    /** Find all moves for current colour */
    std::vector<std::pair<Position, Position>> findMoves();
    
    /** Validates move for pawn */
    static bool isValidPawnMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2);
  
    /** Validates move for king */
    static bool isValidKingMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2);
  
    /** Validates move for Rook */
    static bool isValidRookMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2);

    /** Checks if move is valid */
    bool isValidMove(Position pos1, Position pos2);

    /** Makes move: Pos1 (from), Pos2 (to) */
    bool makeMove(Position pos1, Position pos2);
    
    /** Returns color of player that is about to move */
    Color toMove(void);

    /** Returns value (1 = white, 0 = black player */
    size_t evaluate(Color color);
    
    /** Returns white - black evaluation */
    int fastEval();
    
    /** Undo the last move */
    void undo(void);

    /** Returns last move */
    Move lastMove(void)
    {
      return m_moveLog.top();
    }

  private:
    
    // Current state of the board                                                                                             
    std::map<Position, Piece> m_pieces;
    
    std::stack<Move> m_moveLog;

    // Who is to move
    Color m_toMove;
};


