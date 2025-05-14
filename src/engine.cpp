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

  std::pair<Position, Position> bestMove;
  for (const auto & [from, to]: moves)
  {
    Chess copy = game;
    copy.makeMove(from, to);
    int score = minimax(copy, depth -1, 1e9, 1e9, player == Color::Black);

    if ((player == Color::White && score > bestScore) || (player == Color::Black && score < bestScore))
    {
      bestScore = score;
      bestMove = {from, to};
    }
  }
  
  std::cout << "best move:" << bestMove.first.first << " " << bestMove.first.second << std::endl;
  return bestMove;
}
 
/** Minimax algorithm to find the best move */
int Engine::minimax(Chess game, int depth, int alpha, int beta, bool maximizingPlayer)
{
  if (depth == 0)
    return game.evaluate(Color::White) - game.evaluate(Color::Black);
  
  std::vector<std::pair<Position, Position>> moves = game.findMoves();
  if (moves.empty())
    return game.evaluate(Color::White) - game.evaluate(Color::Black);
  
  if (maximizingPlayer)
  {
    int maxEval = -1e9;
    for (const auto & [from, to]: moves)
    {
      Chess copy = game;
      copy.makeMove(from, to);
      int eval = minimax(copy, depth -1, alpha, beta, false);
      maxEval = std::max(maxEval, eval);
      alpha = std::max(alpha, eval);
      if (beta <= alpha)
        break;
    }
    return maxEval;
  }
  
  else
  {
    int minEval = 1e9;
    for (const auto & [from, to]: moves)
    {
      Chess copy = game;
      copy.makeMove(from, to);
      int eval = minimax(copy, depth -1, alpha, beta, true);
      minEval = std::min(minEval, eval);
      beta = std::min(beta, eval);
      if (beta <= alpha)
        break;
    }
    return minEval;
  }

}


