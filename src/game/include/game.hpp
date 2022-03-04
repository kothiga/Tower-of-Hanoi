/* ================================================================================
 * Copyright: (C) 2022, SIRRL Social and Intelligent Robotics Research Laboratory, 
 *     University of Waterloo, All rights reserved.
 * 
 * Authors: 
 *     Austin Kothig <austin.kothig@uwaterloo.ca>
 * 
 * CopyPolicy: Released under the terms of the MIT License. 
 *     See the accompanying LICENSE file for details.
 * ================================================================================
 */

#ifndef TOWER_OF_HANOI_GAME_HPP
#define TOWER_OF_HANOI_GAME_HPP

#include <atomic>
#include <map>
#include <memory>
#include <string>

#include <player.hpp>
#include <board.hpp>
#include <solver.hpp>


class Game {

    private:
    /* ============================================================================
    **  Private variables of the game.
    ** ============================================================================ */
    std::shared_ptr<Player> _player;
    std::shared_ptr<Board>  _board;
    std::shared_ptr<Solver> _solver;
    std::atomic<bool> _running;

    
    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Game(std::shared_ptr<Player> player);


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~Game();


    /* ===========================================================================
    ** Configure and setup the game environment. 
    **
    ** @param conf : variables for configuring the game environment.
    **
    ** @return whether or not the configuration was a success.
    ** =========================================================================== */
    bool configure(std::map<std::string,std::string> conf);


    /* ===========================================================================
    **  Entry point for the game's start.
    **
    ** @return exit code of the game's status (0: success, 1: errors encountered).
    ** =========================================================================== */
    int run();


    private:
    /* ===========================================================================
    **  Temp.
    ** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_GAME_HPP */
