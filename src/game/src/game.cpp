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

#include <game.hpp>


Game::Game(std::shared_ptr<Player> player) {
    //-- Take a reference to the shared_ptr resource.
    this->_player = player;
    this->_board  = std::make_shared<Board>();
    this->_solver = std::make_shared<Solver>();
}


Game::~Game() {
    //-- Release the shared_ptr resource.
    this->_player.reset();
    this->_board.reset();
    this->_solver.reset();
    std::cout << "[debug] Game Destroyed." << std::endl;
}


bool Game::configure(std::map<std::string,std::string> conf) {
    //TODO: take strings from conf and set appropriately.

    _board->setNumPegs(3);
    _board->setNumDisks(4);
    _board->setBicolor(true);

    _board->init();

    // Start a timer.
    auto start = std::chrono::high_resolution_clock::now();

    _solver.reset(new Solver(3, 4, true));
    _solver->solve();

    // End the timer.
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Took "
         << ((float)std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()) / 1000.0
         << " seconds to run the solve function." << std::endl;

    return true;
}


int Game::run() {

    //-- Set the running status of the game.
    _running = true;

    //-- Loop until interrupt occurs.
    while (_running) {

        //-- Get an action from the user.
        action act = _player->getAction();

        //-- Set vars outside switch.
        bool success;
        std::string showable;

        switch (act.selection) {
        
        case action::HELP:
            //-- Flush message using concrete write.
            _player->writeOutput(act.msg);
            break;

        case action::MOVE:
            //-- Try and make the move provided.
            _player->writeOutput("[debug] Moving peice from " 
                + std::to_string(act.from) + " to " 
                + std::to_string(act.to) + "!!");

            success = _board->move(act.from, act.to);
            if (!success) {
                _player->writeOutput("[debug] Move action failed!!");
            } else {
                showable = _board->getShowableState();
                ull hash = _board->getHashableState();
                pii hint = _solver->getBestMove(hash);
                showable = "Hint: (" + std::to_string(hint.first) + "," + std::to_string(hint.second) + ")\n\n" + showable;
                _player->writeOutput(showable);
            }

            break;

        case action::STATUS:
            //-- Generate the boards status.
            _player->writeOutput("[debug] Generating current board status...");
            showable = _board->getShowableState();
            _player->writeOutput(showable);
            break;

        case action::GOAL:
            //-- Generate the boards goal.
            _player->writeOutput("[debug] Generating board goal state...");
            showable = _board->getShowableGoal();
            _player->writeOutput(showable);
            break;

        case action::HINT:
            //-- Ask the solver for the next optimal move. 
            _player->writeOutput("[debug] Generating a hint! Hold tight...");
            break;

        case action::QUIT:
            //-- Stop the game and exit.
            _player->writeOutput("Stopping the game...");
            _running = false;
            break;

        default:
            break;
        }
    }


    return 0;
}
