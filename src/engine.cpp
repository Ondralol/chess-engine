/**
  * @file engine.cpp
  * @author Ondrej
  * @brief Chess engine class
 *
*/
 
#include "engine.hpp"
#include <climits>
#include <iostream>

/** Find the best move for current chess game*/
std::pair<Position, Position> Engine::findBestMove(Chess game, int depth)
{
  std::vector<std::pair<Position, Position>> moves = game.findMoves();
  std::cout << "All moves:" << std::endl;
  for (const auto & [first, second]: moves)
    std::cout << first.first << " " << first.second << std::endl;

  // returns {{-1,-1},{-1,-1}} if no move can be made
  if (moves.empty())
    return {{-1, -1}, {-1,-1}};
  

  Color player = game.toMove();
  int bestScore = (player == Color::White) ? INT_MIN : INT_MAX;
  std::pair<Position, Position> bestMove = moves[0]; // default move
  
  for (const auto & [from, to]: moves)
  {
    game.makeMove(from, to);
    int score = minimax(game, depth -1, INT_MIN, INT_MAX, player == Color::Black);
    game.undo();

    if ((player == Color::White && score > bestScore) || 
        (player == Color::Black && score < bestScore))
    {
      bestScore = score;
      bestMove = {from, to};
    }
  }
  
  return bestMove;
}
 
/** Minimax algorithm to find the best move */
int Engine::minimax(Chess & game, int depth, int alpha, int beta, bool maximizingPlayer)
{
  if (depth == 0)
  {  
    int res = game.fastEval();
    return res;
    if (maximizingPlayer && game.isChecking())
      res -= 3;
    else
      res += 3;
    
    return res;
  }

  std::vector<std::pair<Position, Position>> moves = game.findMoves();
  if (moves.empty())
  {
    bool isChecking = game.isChecking();
    //isChecking = true;
    if (maximizingPlayer && isChecking)
      return -10000;
    else if (!maximizingPlayer && isChecking)
      return +10000;
    
    // Stalemate
    return 0;
  }

  if (maximizingPlayer)
  {
    int maxEval = INT_MIN;
    for (const auto & [from, to]: moves)
    {
      game.makeMove(from, to);
      int eval = minimax(game, depth -1, alpha, beta, false);
      game.undo();
      maxEval = std::max(maxEval, eval);
      alpha = std::max(alpha, eval);
      if (beta <= alpha)
        break;
    }
    return maxEval;
  }
  
  else
  {
    int minEval = INT_MAX;
    for (const auto & [from, to]: moves)
    {
      game.makeMove(from, to);
      int eval = minimax(game, depth -1, alpha, beta, true);
      game.undo();
      minEval = std::min(minEval, eval);
      beta = std::min(beta, eval);
      if (beta <= alpha)
        break;
    }
    return minEval;
  }

}


