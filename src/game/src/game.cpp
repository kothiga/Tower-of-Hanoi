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
    ull goal_hash = _board->getHashableGoal();

    //-- Loop until interrupt occurs.
    while (_running) {

        //-- Get an action from the user.
        action act = _player->getAction();

        //-- Set vars outside switch.
        bool success;
        std::string showable;
        ull hash; pii hint;

        switch (act.selection) {
        
        case action::HELP:
            //-- Flush message using concrete write.
            _player->writeOutput(act.msg);
            break;

        case action::MOVE:
            //-- Try and make the move provided.
            //_player->writeOutput("[debug] Moving peice from " 
            //    + std::to_string(act.from) + " to " 
            //    + std::to_string(act.to) + "!!");

            success = _board->move(act.from, act.to);
            if (success) {
                //-- If the move was good and we're at the goal state
                //-- give notice and close the program.
                hash = _board->getHashableState();
                if (hash == goal_hash) {
                    _player->writeOutput("2");
                    //_running = false;
                    break;
                }
            }
            //if (!success) {
            //    _player->writeOutput("[debug] Move action failed!!");
            //} else {
            //    showable = _board->getShowableState();
            //    _player->writeOutput(showable);
            //}
            _player->writeOutput((success ? "1" : "0"));

            break;

        case action::STATUS:
            //-- Generate the boards status.
            showable = _board->getShowableState();
            _player->writeOutput(showable);
            break;

        case action::GOAL:
            //-- Generate the boards goal.
            showable = _board->getShowableGoal();
            _player->writeOutput(showable);
            break;

        case action::HINT:
            //-- Ask the solver for the next optimal move. 
            hash = _board->getHashableState();
            hint = _solver->getBestMove(hash);
            showable = std::to_string(hint.first) + " " + std::to_string(hint.second);
            _player->writeOutput(showable);
            break;

        case action::HASH:
            //-- Get the hash from the board and send it.
            hash = _board->getHashableState();
            showable = std::to_string(hash);
            _player->writeOutput(showable);
            break;

        case action::DIST:
            //-- Get the distance to the goal from the solver for the current state.
            hash = _board->getHashableState();
            showable = std::to_string(_solver->getDistance(hash));
            _player->writeOutput(showable);
            break;

        case action::SET:
            //-- Try setting the board state from a hash. Keep the previous as a backup.
            hash = _board->getHashableState();
            success = _board->setFromHashableState(act.hash);
            showable = ( success ? "1" : "0" );
            if (!success) {
                _board->setFromHashableState(hash);
            }
            _player->writeOutput(showable);
            break;

        case action::QUIT:
            //-- Stop the game and exit.
            showable = _board->getShowableState();
            //_player->writeOutput(showable);
            _player->writeOutput("Stopping the game...");
            _running = false;
            break;

        default:
            break;
        }
    }


    return 0;
}
