/**
 * @file chess.cpp
 * @author Ondrej
 * @brief Chess board representation
 *
*/

#include "chess.hpp"

/** Sets up default position for white player being at bottom */
std::map<Position, Piece> Chess::setupWhite(void)
{
  std::map<Position, Piece> pieces;
  Piece piece;

  /* White pieces */
  piece.color = Color::White;
  
  // Rook
  piece.type = PieceType::Rook;
  pieces[{0,0}] =  piece;
  pieces[{7,0}] =  piece;
  
  // Knight
  piece.type = PieceType::Knight;
  pieces[{1,0}] =  piece;
  pieces[{6,0}] =  piece;
  
  // Bishop
  piece.type = PieceType::Bishop;
  pieces[{2,0}] =  piece;
  pieces[{5,0}] =  piece;
  
  // Queen
  piece.type = PieceType::Queen;
  pieces[{3,0}] =  piece;
  
  // King
  piece.type = PieceType::King;
  pieces[{4,0}] =  piece;
  
  // Pawns
  piece.type = PieceType::Pawn;
  for (int i = 0; i < 8; i ++)
    pieces[{i,1}] = piece;
  
  /* Black pieces */
  piece.color = Color::Black;
  
  // Rook
  piece.type = PieceType::Rook;
  pieces[{0,7}] =  piece;
  pieces[{7,7}] =  piece;
  
  // Knight
  piece.type = PieceType::Knight;
  pieces[{1,7}] =  piece;
  pieces[{6,7}] =  piece;
  
  // Bishop
  piece.type = PieceType::Bishop;
  pieces[{2,7}] =  piece;
  pieces[{5,7}] =  piece;
  
  // Queen
  piece.type = PieceType::Queen;
  pieces[{3,7}] =  piece;
  
  // King
  piece.type = PieceType::King;
  pieces[{4,7}] =  piece;
  
  // Pawns
  piece.type = PieceType::Pawn;
  for (int i = 0; i < 8; i ++)
    pieces[{i,6}] = piece;
  
  return pieces;
}

/** Sets up default position for black player being at bottom */
std::map<Position, Piece> Chess::setupBlack(void)
{
   std::map<Position, Piece> pieces;
   Piece piece;

  /* Black pieces */
  piece.color = Color::Black;
  
  // Rook
  piece.type = PieceType::Rook;
  pieces[{0,0}] =  piece;
  pieces[{7,0}] =  piece;
  
  // Knight
  piece.type = PieceType::Knight;
  pieces[{1,0}] =  piece;
  pieces[{6,0}] =  piece;
  
  // Bishop
  piece.type = PieceType::Bishop;
  pieces[{2,0}] =  piece;
  pieces[{5,0}] =  piece;
  
  // Queen
  piece.type = PieceType::Queen;
  pieces[{4,0}] =  piece;
  
  // King
  piece.type = PieceType::King;
  pieces[{3,0}] =  piece;
  
  // Pawns
  piece.type = PieceType::Pawn;
  for (int i = 0; i < 8; i ++)
    pieces[{i,1}] = piece;
  
  /* White pieces */
  piece.color = Color::White;
  
  // Rook
  piece.type = PieceType::Rook;
  pieces[{0,7}] =  piece;
  pieces[{7,7}] =  piece;
  
  // Knight
  piece.type = PieceType::Knight;
  pieces[{1,7}] =  piece;
  pieces[{6,7}] =  piece;
  
  // Bishop
  piece.type = PieceType::Bishop;
  pieces[{2,7}] =  piece;
  pieces[{5,7}] =  piece;
  
  // Queen
  piece.type = PieceType::Queen;
  pieces[{4,7}] =  piece;
  
  // King
  piece.type = PieceType::King;
  pieces[{3,7}] =  piece;
  
  // Pawns
  piece.type = PieceType::Pawn;
  for (int i = 0; i < 8; i ++)
    pieces[{i,6}] = piece;
  
  return pieces;
}


Chess::Chess(Color color)
{
  m_bottomPlayer = color;
  Piece piece;

  /* Sets default position for white to start and be at the bottom */
  if (color == Color::White)
    m_pieces = this -> setupWhite();

  /* Sets default position for white to start and be at the bottom */
  else
    m_pieces = this -> setupBlack();
}

/** Returns value (0 = white, 1 = black player */
size_t Chess::value(Color color)
{
  size_t value = 0;
  for (const auto & [pos, piece]: m_pieces)
  {
    if (piece.color == color || piece.color == color)
    {
      switch (piece.type)
      {
        case PieceType::Pawn:
          value += 1;
          break;
        
        case PieceType::Knight:
          value += 3;
          break;
        
        case PieceType::Bishop:
          value += 3;
          break;

        case PieceType::Rook:
          value += 5;
          break;

         case PieceType::Queen:
          value += 9;
          break; 
      }
    }
  }

  return value;
}


