/**
 * @file boardVisualisation.hpp
 * @author Ondrej
 * @brief Class that visualises the chess board
 *
*/

#pragma once

#include "chess.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <chrono>

#define DIMENSION 8 // board size

#define TOP_PADDING_TEXT 20.0f
#define LEFT_PADDING_TEXT 15.0f
#define TOP_PADDING 75.0f
#define LEFT_PADDING 50.0f
#define TOP_PADDING_GRAPH 450.0f
#define LEFT_PADDING_GRAPH 15.0f
#define GRAPH_SIZE_X 450.0f
#define GRAPH_SIZE_Y 300.0f

class BoardVisualisation
{
public:
  BoardVisualisation(unsigned screenWidth, unsigned screenHeight)
    : m_window (sf::RenderWindow (sf::VideoMode({screenWidth, screenHeight}), "Chess Engine")),
     m_chess ()
  {
    m_window.setFramerateLimit(60);
    m_font.loadFromFile("assets/open_sans");
  }

  /** Processes the user input during visualisation */
  void processInput(sf::Event & event);

  /** The main visualisation loop */
  void mainLoop(void);

  /** Loads texture from cache/file */
  std::shared_ptr<sf::Texture> loadTexture(std::string filename);
  
  /** Displays hint on board*/
  void showHint(Position pos);

  /** Shows piece on exact coordinates */
  void showPieceXY(Piece piece, size_t X, size_t Y);

  /** Shows pieces on chess board */
  void showPieces(void);

  /** Displays the whole chess board */
  void showBoard(void);
  
  /** Flips the board */
  void flipBoard(void); // will need to inverse the holding and dragging as well as all the pieces

private:
  // Main window
  sf::RenderWindow m_window;
  
  Chess m_chess;

  // Which color is on the bottom
  Color m_bottomPlayer;

  // Currently holding piece - (-1, -1) means that no piece is being held
  Position m_holding = {-1, -1};

  std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textureCache;
  sf::Font m_font;
  std::chrono::high_resolution_clock::time_point m_startTime;
};

