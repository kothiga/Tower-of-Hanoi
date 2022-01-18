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
}


Game::~Game() {
    //-- Release the shared_ptr resource.
    this->_player.reset();
    this->_board.reset();
}


bool Game::configure(std::map<std::string,std::string> conf) {
    //TODO: take strings from conf and set appropriately.
    return true;
}


int Game::run() {

    //-- Set the running status of the game.
    _running = true;

    //-- Loop until interrupt occurs.
    while (_running) {

        //-- Get an action from the user.
        action act = _player->getAction();

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
            break;

        case action::STATUS:
            //-- Generate the boards status.
            _player->writeOutput("[debug] Generating current board status...");
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
