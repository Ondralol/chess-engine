/**
 * @file main.cpp
 * @author Ondrej
 * @brief Main function that parses input arguments and calls other functions/methods
*/


#include "boardVisualisation.hpp"

#include <iomanip>

/**
 * @ Manages the whole program
 * - Argument : Positive ingeger N that stands for the depth of MinMax Algorithm
*/

int main (int argc, char ** argv)
{
  
  // Default depth
  size_t depth = 8;
  
  if (argc > 2)
    return EXIT_FAILURE;

  if (argc == 2)
  {
    std::istringstream parse(argv[1]);
    if (!parse >> depth)
      return EXIT_FAILURE;
  }

  unsigned screenWidth = sf::VideoMode::getDesktopMode().width;
  unsigned screenHeight = sf::VideoMode::getDesktopMode().height;
  BoardVisualisation board(screenWidth, screenHeight);
  

  /* Simulate board */
  std::map<Position, Piece> pieces;
  Piece piece;

  /*  White pieces  */
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
  

  board.updatePieces(pieces);
  /* Runs the main window loop*/
  board.mainLoop();
    
}

