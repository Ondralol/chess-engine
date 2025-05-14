/**
 * @file engine.hpp
 * @author Ondrej
 * @brief Chess engine class
 *
*/

#pragma once

#include "chess.hpp"

class Engine
{
  public:
    Engine() {};

    /** Find the best move for current chess game*/
    std::pair<Position, Position> findBestMove(Chess game, int depth);

  private:
    
    /** Minimax algorithm to find the best move */
    int minimax(Chess & game, int depth, int alpha, int beta, bool maximizingPlayer);
};

