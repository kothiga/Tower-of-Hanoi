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

#include <solver.hpp>

Solver::Solver(std::size_t pegs/*=3*/, std::size_t disks/*=3*/, bool isBicolor/*=false*/) {

    //-- Create a fresh board and initialize it.
    this->_board = std::make_shared<Board>(pegs, disks, isBicolor);
    this->_board->init();

    //-- Ensure these data structures are cleared out of old data.
    this->_sssp.clear();
    this->_moves.clear();

    //-- Get all combinations of possible game moves.
    for (int i = 0; i < pegs; ++i) {
        for (int j = 0; j < pegs; ++j) {
            
            //-- Skip moves with the same to/from.
            if (i == j) { continue; }

            //-- Push this move into the possible moves.
            this->_moves.push_back(std::make_pair(i,j));
        }
    }
}


Solver::~Solver() {
    //-- Release the shared_ptr resources.
    this->_board.reset();

    //-- Clear stored data.
    this->_sssp.clear();
    this->_moves.clear();

    // <REMOVE>
    std::cout << "[debug] Solver Destroyed." << std::endl;
    // <\REMOVE>
}


void Solver::solve() {

    //-- Get the hash for the goal state, then set the board as it.
    ull goalHash = _board->getHashableGoal();
    bool success = _board->setFromHashableState(goalHash);

    if (!success) {
        std::cerr << "[error] Could not set goal hash!" << std::endl;
        return;
    }

    //-- Init a queue for the breadth-first search in getting the 
    //-- single-source shortest path to all existing states.
    std::queue<ull> bfs; 

    
    return;
}


pii Solver::getBestMove(ull hash) {

}

