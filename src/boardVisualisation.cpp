/**
 * @file boardVisualisation.cpp
 * @author Ondrej
 * @brief Class that visualises the chess board
 *
*/

#include "boardVisualisation.hpp"

#include <memory>
#include <string>
#include <random>
#include <thread>
#include <sstream>
#include <functional>


/** Processes all user input */
void BoardVisualisation::processInput(sf::Event & event)
{
  unsigned int smallerWinSize = std::min(m_window.getSize().x, m_window.getSize().y);
  float squareSize = (smallerWinSize - 75) / DIMENSION;

  /* Close window if window is closed */
  if (event.type == sf::Event::Closed)
    m_window.close();

  /** Close window if ESC is pressed */
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    m_window.close();

  else if (event.type == sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      // Raw display coordinates
      sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
      // Window coordinates
      sf::Vector2f windowPos = m_window.mapPixelToCoords(mousePos);
      float XMouse = windowPos.x;
      float YMouse = windowPos.y;
      
      // Check if any piece was clicked
      for (const auto & [pos, piece]: m_pieces)
      {
        size_t XPos = pos.first;
        size_t YPos = (7-pos.second);
        float XSquare = LEFT_PADDING + XPos * squareSize;
        float YSquare = TOP_PADDING + YPos * squareSize;
        
        // Check if mouse is inside the square
        if (XMouse > XSquare && XMouse < XSquare + squareSize && YMouse > YSquare &&
            YMouse < YSquare + squareSize)
        {
          m_holding = pos;
        }

       //std::cout << "Mouse: (" << XMouse << ", " << YMouse << ", Square (" << XSquare << ", " << YSquare << ")" << std::endl;
      }
    }
  }

  else if (event.type == sf::Event::MouseButtonReleased)
  {
    if (event.mouseButton.button == sf::Mouse::Left && m_holding.first != -1)
    {
      // Raw display coordinates
      sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
      // Window coordinates
      sf::Vector2f windowPos = m_window.mapPixelToCoords(mousePos);
      float XMouse = windowPos.x;
      float YMouse = windowPos.y;
      
      bool empty = true;
      // Check if any piece was clicked
      for (const auto & [pos, piece]: m_pieces)
      {
        size_t XPos = pos.first;
        size_t YPos = (7-pos.second);
        float XSquare = LEFT_PADDING + XPos * squareSize;
        float YSquare = TOP_PADDING + YPos * squareSize;
        
        // Check if mouse is inside the square
        if (XMouse > XSquare && XMouse < XSquare + squareSize && YMouse > YSquare &&
            YMouse < YSquare + squareSize)
        {
          empty = false;
        }
      }
      if (empty)
      {
        Piece oldPiece = m_pieces[m_holding];
        int newX = (XMouse - LEFT_PADDING) / squareSize;
        int newY = 8 - (YMouse - TOP_PADDING) / squareSize;
        std::cout << newX << " " << newY << std::endl;
        if (newX >= 0 && newX <= 7 && newY >= 0 && newY <= 7)
        {
          m_pieces.erase(m_holding);
          m_pieces[{newX, newY}] = oldPiece;
        }
      }
      m_holding.first = -1;
    }
  }
}

/** The main loop */
void BoardVisualisation::mainLoop(void)
{
  m_startTime = std::chrono::high_resolution_clock::now();
  unsigned int smallerWinSize = std::min(m_window.getSize().x, m_window.getSize().y);
  float squareSize = (smallerWinSize - 75) / DIMENSION;

  sf::Event event;
  sf::Clock clock;
  float currentStepTime = 0.0f;
  while (m_window.isOpen())
  {
    while (m_window.pollEvent(event))
    {
      this -> processInput(event);
    }

    m_window.clear(sf::Color(39,36,33,255));
    
    showBoard();
    
    // If currently holding
    if (m_holding.first != -1)
    {
      // Raw display coordinates
      sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
      
      // Window coordinates
      sf::Vector2f windowPos = m_window.mapPixelToCoords(mousePos);
      
      // Displays the piece on the cursour (-squareSize to adjust from offset - displaying from top left corner, not middle)
      this -> showPieceXY(m_pieces[m_holding], windowPos.x - squareSize / 2, windowPos.y - squareSize / 2);
    }
    m_window.display();

  }
}

/** Loads texture from cache/file */
std::shared_ptr<sf::Texture> BoardVisualisation::loadTexture(std::string filename)
{
  if (m_textureCache.find(filename) != m_textureCache.end())
    return m_textureCache[filename];

  auto texture = std::make_shared<sf::Texture>();
  if (!texture -> loadFromFile(filename))
    return nullptr;

  m_textureCache[filename] = texture;
  return texture;
}

/** Updates position of pieces on the board */
void BoardVisualisation::updatePieces(std::map<Position, Piece> pieces)
{
  m_pieces = pieces;
}

/** Shows piece on exact coordinates */
void BoardVisualisation::showPieceXY(Piece piece, size_t X, size_t Y)
{
  unsigned int smallerWinSize = std::min(m_window.getSize().x, m_window.getSize().y);
  float squareSize = (smallerWinSize - 75) / DIMENSION;

  std::shared_ptr<sf::Texture> texture;
  if (piece.color == Color::White)
    {
      switch(piece.type)
      {
        case PieceType::King:
          texture = this -> loadTexture("assets/king_white.png");
          break;
        
        case PieceType::Queen:
          texture = this -> loadTexture("assets/queen_white.png");
          break;
        
        case PieceType::Rook:
          texture = this -> loadTexture("assets/rook_white.png");
          break;
        
        case PieceType::Bishop:
          texture = this -> loadTexture("assets/bishop_white.png");
          break;
        
        case PieceType::Knight:
          texture = this -> loadTexture("assets/knight_white.png");
          break;
        
        case PieceType::Pawn:
          texture = this -> loadTexture("assets/pawn_white.png");
          break;
      }
    }
    else
    {
      switch(piece.type)
      {
        case PieceType::King:
          texture = this -> loadTexture("assets/king_black.png");
          break;
        
        case PieceType::Queen:
          texture = this -> loadTexture("assets/queen_black.png");
          break;
        
        case PieceType::Rook:
          texture = this -> loadTexture("assets/rook_black.png");
          break;
        
        case PieceType::Bishop:
          texture = this -> loadTexture("assets/bishop_black.png");
          break;
        
        case PieceType::Knight:
          texture = this -> loadTexture("assets/knight_black.png");
          break;
        
        case PieceType::Pawn:
          texture = this -> loadTexture("assets/pawn_black.png");
          break;
      }
    }
    
    texture -> setSmooth(true);
    sf::Sprite sprite;
    sprite = sf::Sprite(*texture);
    sprite.setScale(squareSize / texture -> getSize().x, squareSize / texture -> getSize().y);
    sprite.setPosition(X, Y);
    m_window.draw(sprite);
}


/** Displays pieces on chess board */
void BoardVisualisation::showPieces(void)
{
  unsigned int smallerWinSize = std::min(m_window.getSize().x, m_window.getSize().y);
  float squareSize = (smallerWinSize - 75) / DIMENSION;

  for (auto &[pos, piece]: m_pieces)
  {
    // Dont display the piece that is being held
    if (pos.first == m_holding.first && pos.second == m_holding.second)
      continue;

    size_t XPos = pos.first;
    size_t YPos = (7-pos.second);
    this -> showPieceXY(piece, LEFT_PADDING + XPos * squareSize, TOP_PADDING + YPos * squareSize);
  }
  
}

/** Displays the whole board */
void BoardVisualisation::showBoard(void)
{
  unsigned int smallerWinSize = std::min(m_window.getSize().x, m_window.getSize().y);
  float squareSize = (smallerWinSize - 75) / DIMENSION;

  sf::VertexArray squares(sf::Quads, DIMENSION * DIMENSION * 4);
  size_t vertexIndex = 0;

  float X = LEFT_PADDING;
  float Y = TOP_PADDING;

  for (size_t i = 0; i < DIMENSION; i ++)
  {
    for (size_t j = 0; j < DIMENSION; j ++)
    {
      sf::Color color;
      /* Decide colour based on square positon */
      if ((i % 2 != 0 && j % 2 != 0)|| (i % 2 == 0 && j % 2 == 0) )
        color = sf::Color(238,238,210,255);
      else
        color = sf::Color(118,150,86,255);

      squares[vertexIndex].color = color;
      squares[vertexIndex].position = sf::Vector2f(X, Y);
      vertexIndex ++;

      squares[vertexIndex].color = color;
      squares[vertexIndex].position = sf::Vector2f(X + squareSize, Y);
      vertexIndex ++;

      squares[vertexIndex].position = sf::Vector2f(X + squareSize, Y + squareSize);
      squares[vertexIndex].color = color;
      vertexIndex ++;

      squares[vertexIndex].color = color;
      squares[vertexIndex].position = sf::Vector2f(X, Y + squareSize);
      vertexIndex ++;

      X += squareSize;
    }
    
    Y += squareSize;
    X = LEFT_PADDING;

  }
  m_window.draw(squares);
  
  /* Display the pieces */
  this -> showPieces();

}


