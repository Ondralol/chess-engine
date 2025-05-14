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
  /* Runs the main window loop*/
  board.mainLoop();
    
}

