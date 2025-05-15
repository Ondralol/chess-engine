/**
 * @file chess.cpp
 * @author Ondrej
 * @brief Chess board representation
 *
*/

#include "chess.hpp"

#include <cmath>
#include <iostream>

/** Sets up default position for white player being at bottom */
std::map<Position, Piece> Chess::setup(void)
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

/** Simple board setup (for showcase and testing */
std::map<Position, Piece> Chess::simpleSetup1()
{
  std::map<Position, Piece> pieces;
  Piece piece;
  
  piece.type = PieceType::King;
  piece.color = Color::White;
  pieces[{4,4}] = piece;
  piece.type = PieceType::Rook;
  //pieces[{4,6}] = piece;
  pieces[{4,3}] = piece;
  pieces[{1,0}] = piece;


  piece.color = Color::Black;
  piece.type = PieceType::King;
  pieces[{3,1}] = piece;
  
  piece.type = PieceType::Rook;
  pieces[{3,2}] = piece;

  return pieces;
}


/** Simple board setup (for showcase and testing */
std::map<Position, Piece> Chess::simpleSetup2()
{
  std::map<Position, Piece> pieces;
  Piece piece;
  
  piece.type = PieceType::King;
  piece.color = Color::White;
  pieces[{4,4}] = piece;
  piece.type = PieceType::Rook;
  //pieces[{4,6}] = piece;
  pieces[{4,3}] = piece;
  pieces[{1,0}] = piece;
  pieces[{4,0}] = piece;

  piece.color = Color::Black;
  piece.type = PieceType::King;
  pieces[{3,1}] = piece;
  
  //piece.type = PieceType::Rook;
  //pieces[{3,2}] = piece;

  return pieces;
}


/** Simple board setup (for showcase and testing */
std::map<Position, Piece> Chess::simpleSetup3()
{
  std::map<Position, Piece> pieces;
  Piece piece;
  
  piece.type = PieceType::King;
  piece.color = Color::White;
  pieces[{4,4}] = piece;
  piece.type = PieceType::Rook;
  //pieces[{4,6}] = piece;
  pieces[{4,3}] = piece;
  //pieces[{1,0}] = piece;


  piece.color = Color::Black;
  piece.type = PieceType::King;
  pieces[{3,1}] = piece;
  
  piece.type = PieceType::Rook;
  pieces[{3,2}] = piece;

  return pieces;
}


Chess::Chess()
{
  //m_pieces = this -> setup();
  m_pieces = this -> simpleSetup2();
  m_toMove = Color::White;
}


/** Check if the move does not put your own king at check, expects valid move on input */
// NOTE: Not checking if new pos is not out of range, but it should not matter considering what type of operations I do here
bool Chess::isCheck(Position pos1, Position pos2)
{
  // Simulate move
  std::map<Position, Piece> piecesCopy = m_pieces;
  
  Piece piece = piecesCopy[pos1];
  piecesCopy.erase(pos1); // What if I erase the enemy king?
  piecesCopy[pos2] = piece;
  
  Position kingPos;
  bool found = false;
  // Find king position
  for (int i = 0; i < BOARD_SIZE && !found; i ++)
  {
    for (int j = 0; j < BOARD_SIZE && !found; j ++)
      if (piecesCopy.find({i,j}) != piecesCopy.end() && piecesCopy[{i,j}].type == PieceType::King 
          && piecesCopy[{i,j}].color == piece.color)
      {
        kingPos = {i, j};
        found = true;
      }
  }
  // Simulate all from the other color check if king is attacked
  std::map<Position, Piece> pieces;

  // Get all pieces from the board
  for (int i = 0; i < BOARD_SIZE; i ++)
  {
    for (int j = 0; j < BOARD_SIZE; j ++)
      if (piecesCopy.find({i,j}) != piecesCopy.end() && piecesCopy[{i,j}].color != piece.color)
        pieces[{i, j}] =  piecesCopy[{i,j}];
  }
  
  // Iterate over all pieces and try all the possible moves
  Position newPos;
  for (const auto & [pos, piece]: pieces)
  {
    switch (piece.type)
    {
      case PieceType::King:
        for (const auto & dir: KING_MOVES)
        {  
          newPos = Position(pos.first + dir.first, pos.second + dir.second);
          if (this -> isValidKingMove(piecesCopy, pos, newPos) && kingPos == newPos)
            return true;
        }
        break;
      
      case PieceType::Rook:
        for (const auto & dir: ROOK_MOVES)
        {
          for (int i = 1; i < 3; i++)
          {
            newPos = Position(pos.first + i * dir.first, pos.second + i * dir.second);
            if (this -> isValidRookMove(piecesCopy, pos, newPos) && kingPos == newPos)
              return true;
          }
        }
        break;

    }

  }
  return false;
}

/* If current positiong is checking */
bool Chess::isChecking()
{
  Position kingPos;
  bool found = false;
  // Find king position
  for (int i = 0; i < BOARD_SIZE && !found; i ++)
  {
    for (int j = 0; j < BOARD_SIZE && !found; j ++)
      if (m_pieces.find({i,j}) != m_pieces.end() && m_pieces[{i,j}].type == PieceType::King 
          && m_pieces[{i,j}].color == m_toMove)
      {
        kingPos = {i, j};
        found = true;
      }
  }
  // Simulate all from the other color check if king is attacked
  std::map<Position, Piece> pieces;

  // Get all pieces from the board
  for (int i = 0; i < BOARD_SIZE; i ++)
  {
    for (int j = 0; j < BOARD_SIZE; j ++)
      if (m_pieces.find({i,j}) != m_pieces.end() && m_pieces[{i,j}].color != m_toMove)
        pieces[{i, j}] =  m_pieces[{i,j}];
  }
  
  // Iterate over all pieces and try all the possible moves
  Position newPos;
  for (const auto & [pos, piece]: pieces)
  {
    switch (piece.type)
    {
      case PieceType::King:
        for (const auto & dir: KING_MOVES)
        {  
          newPos = Position(pos.first + dir.first, pos.second + dir.second);
          if (this -> isValidKingMove(m_pieces, pos, newPos) && kingPos == newPos)
            return true;
        }
        break;
      
      case PieceType::Rook:
        for (const auto & dir: ROOK_MOVES)
        {
          for (int i = 1; i < 3; i++)
          {
            newPos = Position(pos.first + i * dir.first, pos.second + i * dir.second);
            if (this -> isValidRookMove(m_pieces, pos, newPos) && kingPos == newPos)
              return true;
          }
        }
        break;

    }

  }
  return false;
}



/** Find all moves for white/black player */
std::vector<std::pair<Position, Position>> Chess::findMoves()
{
  std::vector<std::pair<Position, Position>> moves; 
  std::map<Position, Piece> pieces;

  // Get all pieces from the board
  for (int i = 0; i < BOARD_SIZE; i ++)
  {
    for (int j = 0; j < BOARD_SIZE; j ++)
      if (m_pieces.find({i,j}) != m_pieces.end() && m_pieces[{i,j}].color == m_toMove)
        pieces[{i, j}] =  m_pieces[{i,j}];
  }
  
  // Iterate over all pieces and try all the possible moves
  Position newPos;
  for (const auto & [pos, piece]: pieces)
  {
    switch (piece.type)
    {
      case PieceType::King:
        for (const auto & dir: KING_MOVES)
        {
          newPos = Position(pos.first + dir.first, pos.second + dir.second);
          if (!(this -> isCheck(pos, newPos)) && isValidMove(pos, newPos))
            moves.push_back({pos, newPos});
        }
        break;
      
      case PieceType::Rook:
        for (const auto & dir: ROOK_MOVES)
        {
          for (int i = 1; i < 3; i++)
          {
            newPos = Position(pos.first + i * dir.first, pos.second + i  * dir.second);
            if (!(this -> isCheck(pos, newPos)) && isValidMove(pos, newPos))
              moves.push_back({pos, newPos});
          }
        }
        break;
    }

  }
  //std::cout << moves.size() << std::endl;
  return moves;
}

/** Validates move for pawn */
// TODO en passant, upgrade
bool Chess::isValidPawnMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2)
{
  Piece piece1 = pieces[pos1];
  
  // Validate moves for white pawns
  if (piece1.color == Color::White)
  {
    // check one move up
    if (pos1.first == pos2.first && pos1.second + 1 == pos2.second && pieces.find(pos2) == pieces.end())
      return true;

    // check two moves up if its the first move
    if (pos1.first == pos2.first && pos1.second + 2 == pos2.second && pieces.find(pos2) == pieces.end() 
        && pieces.find({pos1.first, pos1.second + 1}) == pieces.end() && pos1.second == 1)
      return true;

    // Check diagonal to left move
    if (pos1.first - 1 == pos2.first && pos1.second + 1 == pos2.second && pieces.find(pos2) != pieces.end())
      if (pieces[pos2].color == Color::Black)
        return true;
    
    // Check diagonal to right move
    if (pos1.first + 1 == pos2.first && pos1.second + 1 == pos2.second && pieces.find(pos2) != pieces.end())
      if (pieces[pos2].color == Color::Black)
        return true;
  }
   
  // Validate moves for black pawns
  else
  {
    // check one move up
    if (pos1.first == pos2.first && pos1.second - 1 == pos2.second && pieces.find(pos2) == pieces.end())
      return true;

    // check two moves up if its the first move
    if (pos1.first == pos2.first && pos1.second - 2 == pos2.second && pieces.find(pos2) == pieces.end() 
        && pieces.find({pos1.first, pos1.second - 1}) == pieces.end() && pos1.second == 6)
      return true;

    // Check diagonal to left move
    if (pos1.first - 1 == pos2.first && pos1.second - 1 == pos2.second && pieces.find(pos2) != pieces.end())
      if (pieces[pos2].color == Color::Black)
        return true;
    
    // Check diagonal to right move
    if (pos1.first + 1 == pos2.first && pos1.second - 1 == pos2.second && pieces.find(pos2) != pieces.end())
      if (pieces[pos2].color == Color::Black)
        return true;
  }
  
  return false;
}

/** Validates move for king */
// TODO Castling
bool Chess::isValidKingMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2)
{
  if (std::abs(pos1.first - pos2.first) <= 1 && std::abs(pos1.second - pos2.second) <= 1)
  {
    //Checks if position is empty or if oposing color is at that position
    if (pieces.find(pos2) == pieces.end())
      return true;

    if (pieces[pos1].color != pieces[pos2].color)
      return true;
  }
  return false;
}

/** Validates move for Rook */
bool Chess::isValidRookMove(std::map<Position, Piece> & pieces, Position pos1, Position pos2)
{
  // Check if the move is vertical
  if (pos1.first == pos2.first)
  {
    // Check if there is clear path between the two postions
    int step;
    if (pos1.second > pos2.second)
      step = -1;
    else
      step = 1;

    for (int i = pos1.second + step; i < pos2.second; i += step)
    {
      if (pieces.find({pos1.first, i}) != pieces.end())
        return false;
    }
  }
 
  // Check if the move is horizontal
  else if (pos1.second == pos2.second)
  {
    // Check if there is clear path between the two postions
    int step;
    if (pos1.first > pos2.first)
      step = -1;
    else
      step = 1;

    for (int i = pos1.first + step; i < pos2.first; i += step)
    {
      if (pieces.find({i, pos1.second}) != pieces.end())
        return false;
    }
  }
  
  else
    return false;

  //Checks if position is empty or if oposing color is at that position
  if (pieces.find(pos2) == pieces.end())
    return true;

  if (pieces[pos1].color != pieces[pos2].color)
    return true;
  
  return false;
}


/** Checks if move is valid */
bool Chess::isValidMove(Position pos1, Position pos2)
{
  /* Checks if the positions are not out of bounds of the board or if the positions are the same */
  if (pos1.first < 0 || pos1.first > BOARD_SIZE - 1 || pos1.second < 0 || pos1.second > BOARD_SIZE - 1 || pos2.first < 0 || pos2.first > BOARD_SIZE - 1 ||
      pos2.second < 0 || pos2.second > BOARD_SIZE - 1 || pos1 == pos2)
    return false;

  // Check if there is any piece at pos1
  if (m_pieces.find(pos1) == m_pieces.end())
    return false;

  Piece piece1 = m_pieces[pos1];

  // If the player that made the move is the one who is to move
  if (piece1.color != m_toMove)
    return false;
  
  // Check if the move does not put you in check
  if (this -> isCheck(pos1, pos2))
    return false;
  
  // Now check if the move is valid
  switch (piece1.type)
  {
    case PieceType::Pawn:
      return isValidPawnMove(m_pieces, pos1, pos2); 
    
    case PieceType::King:
      return isValidKingMove(m_pieces, pos1, pos2);

    case PieceType::Rook:
      return isValidRookMove(m_pieces, pos1, pos2);
  }
  
  return true;
}

/** Makes move: Pos1 (from), Pos2 (to) */
// Why is this bool?
bool Chess::makeMove(Position pos1, Position pos2)
{
  Piece piece = m_pieces[pos1];
  
  // Default value
  Piece capturedPiece;
  capturedPiece.type = PieceType::Empty;

  if (m_pieces.find(pos2) != m_pieces.end())
    capturedPiece = m_pieces[pos2];


  m_pieces.erase(pos1);
  m_pieces[pos2] = piece;

  // Change whose turn it is
  if (m_toMove == Color::White)
    m_toMove = Color::Black;
  else
    m_toMove = Color::White;
  
  // Save move to the log
  Move move;
  move.from = pos1;
  move.to = pos2;
  move.movedPiece = piece;
  move.capturedPiece = capturedPiece;
  move.wasFirstMove = false;

  m_moveLog.push(move);

  return true;
}

/** Undo the last move */
void Chess::undo()
{
  Move move = m_moveLog.top();
  m_moveLog.pop();

  m_pieces.erase(move.to);
  m_pieces[move.from] = move.movedPiece;

  // If captured piece was no empty
  if (move.capturedPiece.type != PieceType::Empty)
    m_pieces[move.to] = move.capturedPiece;
  
  // Revert whose turn it is
  if (m_toMove == Color::White)
    m_toMove = Color::Black;
  else
    m_toMove = Color::White;
}

/** Returns color of player that is about to move */
Color Chess::toMove()
{
  return m_toMove;
}

/** Returns value (0 = white, 1 = black player */
size_t Chess::evaluate(Color color)
{
  size_t value = 0;
  for (const auto & [pos, piece]: m_pieces)
  {
    if (piece.color == color)
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
          
         case PieceType::King:
          value += 0;
          break;
      }
    }
  }

  return value;
}

/** Returns white - black evaluation */
int Chess::fastEval()
{
  int value = 0;
  for (const auto & [pos, piece]: m_pieces)
  {
    int tmpVal = 0;
    switch (piece.type)
    {
      case PieceType::Pawn:
        tmpVal += 1;
        break;
        
      case PieceType::Knight:
        tmpVal += 3;
        break;
        
      case PieceType::Bishop:
        tmpVal += 3;
        break;

      case PieceType::Rook:
        tmpVal += 5;
        break;

       case PieceType::Queen:
        tmpVal += 9;
        break;
          
       case PieceType::King:
        tmpVal += 0;
        break;
    }
     
    if (piece.color == Color::White)
      value += tmpVal;
    else
      value -= tmpVal;
  }
  
  return value;
}

