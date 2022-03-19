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

    this->_start_hash = this->_board->getHashableState();
    this->_goal_hash  = this->_board->getHashableGoal();

    //-- Ensure these data structures are cleared out of old data.
    this->_sssp.clear();
    this->_dist.clear();
    this->_moves.clear();
    this->_solved = false;

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
    this->_dist.clear();
    this->_moves.clear();

    // <REMOVE>
    std::cout << "[debug] Solver Destroyed." << std::endl;
    // <\REMOVE>
}


void Solver::solve() {

    //-- TODO: If it's already solved reset/return?
    if (_solved) { return; }

    //-- Get the hash for the goal state, then set the board as it.
    ull goal_hash = _board->getHashableGoal();
    //bool success  = _board->setFromHashableState(goal_hash); //TODO: Needed?

    //if (!success) {
    //    std::cerr << "[error] Could not set goal hash!" << std::endl;
    //    return;
    //}

    //-- Init a queue for the breadth-first search in getting the 
    //-- single-source shortest path to all existing states.
    std::queue<ull> bfs; 

    //-- Seed the bfs with our first state that we're looking at.
    bfs.push(goal_hash);
    _dist[goal_hash] = 0;

    //-- Loop until all states have been reached.
    while (!bfs.empty()) {

        //-- Get the current state.
        ull cur_state = bfs.front();
        bfs.pop();

        //-- Check and see if this state has alread been seen.
        if (_sssp.find(cur_state) != _sssp.end()) {
            continue;
        }

        //-- Set the board state to the current state.
        bool success = _board->setFromHashableState(cur_state);
        if (!success) {
            std::cerr << "[error] Could not set current hash!" << std::endl;
            return;
        }

        //-- Iterate through and try all possible moves.
        mvec state_moves;
        for (std::size_t mdx = 0; mdx < _moves.size(); ++mdx) {

            //-- Try the move, if it didn't take, move onto the next.
            success = _board->move(_moves[mdx].first, _moves[mdx].second);
            if (!success) { continue; }

            //-- Get the hash of the successful move.    
            ull move_hash = _board->getHashableState();
            bfs.push(move_hash);

            //-- Reverse the move.
            success = _board->move(_moves[mdx].second, _moves[mdx].first);

            //-- Error check the state.
            if (!success) {
                std::cerr << "[error] Could not reverse the move!" << std::endl;
                return;
            }

            //-- If this state has not been seen before,
            //-- set how many moves there are to the
            //-- goal state for this state.
            if (_dist.find(move_hash) == _dist.end()) {
                _dist[move_hash] = _dist[cur_state] + 1;
            }

            //-- Add this move as an edge to the sssp possible states.
            move current_move;
            current_move.from = _moves[mdx].first;
            current_move.to   = _moves[mdx].second;
            current_move.hash =  move_hash;
            current_move.dist = _dist[move_hash];

            state_moves.push_back(current_move);
        }

        //-- Set the computed sssp moves for the current state.
        _sssp[cur_state] = state_moves;
    }

    //-- This has been computed!
    _solved = true;

    std::cout << "Num states=" << _sssp.size() << std::endl;
    
    return;
}


pii Solver::getBestMove(ull hash) {

    if (_sssp.find(hash) == _sssp.end()) { return std::make_pair(-1,-1); }
    mvec state_moves = _sssp[hash];

    // <REMOVE>
    std::cout << "Hash: " << hash << std::endl;
    std::size_t min_idx = 0;
    std::cout << "\t - (" << state_moves[min_idx].from << "," << state_moves[min_idx].to << ")  -->  " 
                  << state_moves[min_idx].dist << ":" << state_moves[min_idx].hash << std::endl;
    // <\REMOVE>

    for (std::size_t mdx = 1; mdx < state_moves.size(); ++mdx) {

        // <REMOVE>
        std::cout << "\t - (" << state_moves[mdx].from << "," << state_moves[mdx].to << ")  -->  " 
                  << state_moves[mdx].dist << ":" << state_moves[mdx].hash << std::endl;
        // <\REMOVE>

        if (state_moves[min_idx].dist > state_moves[mdx].dist) {
            min_idx = mdx;
        }
    }

    return std::make_pair(state_moves[min_idx].from, state_moves[min_idx].to);
}


ull Solver::getDistance(ull hash) {
    return _dist[hash];
}


std::string Solver::flushSolution() {

    std::string ret = "";
    std::string tabx1(4,  ' ');
    std::string tabx2(8,  ' ');
    std::string tabx3(12, ' ');

    ret += "[\n";
    ret += tabx1 + "{\n" +
        tabx2 + "\"pegs\":    \"" + std::to_string(_board->getNumPegs())   + "\",\n" + 
        tabx2 + "\"disks\":   \"" + std::to_string(_board->getNumDisks())  + "\",\n" + 
        tabx2 + "\"bicolor\": \"" + std::to_string(_board->getIsBicolor()) + "\"\n"  +
        tabx1 + "},\n";

    ret += tabx1 + "{\n" + 
        tabx2 + "\"start\": \"" + std::to_string(_start_hash) + "\",\n" +
        tabx2 + "\"goal\":  \"" + std::to_string(_goal_hash)  + "\"\n"  +
        tabx1 + "},\n";

    ret += tabx1 + "{\n";
    for (auto it = _sssp.begin(); it != _sssp.end(); ++it) {

        if (it != _sssp.begin()) { ret += ",\n"; }
        
        ret += tabx2 + "\"" + std::to_string(it->first) + "\": {\n";

        mvec state_moves = it->second;
        for (std::size_t mdx = 0; mdx < state_moves.size(); ++mdx) {
            if (mdx) { ret += ",\n"; }
            ret += tabx3 + "\"(" + 
                std::to_string(state_moves[mdx].from) + "," +
                std::to_string(state_moves[mdx].to) + ")\": { \"hash\": \"" +
                std::to_string(state_moves[mdx].hash) + "\", \"dist\": \"" + 
                std::to_string(state_moves[mdx].dist) + "\" }";
        }

        ret += "\n" + tabx2 + "}";
    }
    ret += "\n" + tabx1 + "}\n";
    ret += "]";

    std::cout << ret << std::endl;

    return ret;
}
