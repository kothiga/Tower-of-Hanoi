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

#include <board.hpp>


Board::Board(std::size_t pegs/*=3*/, std::size_t disks/*=3*/, bool isBicolor/*=false*/) :
    _num_peg(pegs), _num_disk(disks), _bicolor(isBicolor) {
    
    this->_board_set = false;
    this->_state.clear();
}


Board::~Board() {
    this->_state.clear();
    //TODO: REMOVE.
    //std::cout << "[debug] Board Destroyed." << std::endl;
}


bool Board::init() {

    //-- Declare that the board is uninitialized.
    _board_set = false;

    //-- Clear out board state to start anew.
    _state.clear();

    //-- Check bounds for number of pegs and disks.
    if (_num_disk < 3 || _num_disk > 8) { return false; }
    if (_num_peg  < 3 || _num_peg  > 8) { return false; }

    //-- Allocate the proper number of pegs for the board.
    for (std::size_t idx = 0; idx < _num_peg; ++idx) {
        _state.push_back(std::vector<Disk>());
        _state[idx].reserve(_num_disk*2 + 1);
    }

    //-- Init the board state to the default state.
    if (_bicolor) {
        for (std::size_t size = 0; size < _num_disk; ++size) {
            _state[0].push_back(Disk(_num_disk - size, (size+1) % 2));
            _state[1].push_back(Disk(_num_disk - size, (size+2) % 2));
        }
    } else {
        for (std::size_t size = 0; size < _num_disk; ++size) {
            _state[0].push_back(Disk(_num_disk - size));
        }
    }

    //-- Declare that the board has been initialized.
    _board_set = true;

    return true;
}


void Board::setNumPegs(std::size_t pegs) {
    _board_set = false;
    _num_peg = pegs;
    return;
}


void Board::setNumDisks(std::size_t disks) {
    _board_set = false;
    _num_disk = disks;
    return;
}


void Board::setBicolor(bool isBicolor) {
    _board_set = false;
    _bicolor = isBicolor;
    return;
}


bool Board::setFromHashableState(unsigned long long hash) {
    //TODO: IMPLEMENT.
    return true;
}


std::size_t Board::getNumPegs() {
    return _num_peg;
}


std::size_t Board::getNumDisks() {
    return _num_disk;
}


bool Board::getIsBicolor() {
    return _bicolor;
}


std::vector<std::vector<Disk>> Board::getRawState() {
    return _state;
}


std::string Board::getShowableState() { //TODO: IMPLEMENT.

    //-- Find the max height of a single peg.
    std::size_t max_height = 0;
    for (std::size_t idx = 0; idx < _state.size(); ++idx) {
        max_height = (_state[idx].size() > max_height) ? _state[idx].size() : max_height;
    }

    std::string ret = "";

    //TODO: 
    // <REMOVE>
    ret += ">>>\n";
    for (std::size_t idx = 0; idx < _state.size(); ++idx) {
        ret += ("[" + std::to_string(idx) + "] ");
        for (auto d : _state[idx]) {
            ret += ("(" + std::to_string(d.getColor()) + "," + std::to_string(d.getSize()) + ") "); 
        } 
        ret += "\n";
    }
    ret += ">>>\n";
    // <\REMOVE>


    return ret;
}


unsigned long long Board::getHashableState() { //TODO: IMPLEMENT.
    
    unsigned long long ret = 0;
    std::vector<std::size_t> hash;

    for (std::size_t pdx = 0; pdx < _num_peg; ++pdx) {

        std::size_t height = 0;
        for (std::size_t ddx = 0; ddx < _num_disk; ++ddx) {
            
            //-- Check if height is out of range.
            if (height >= _state[pdx].size()) { continue; }
            
            //-- What is the current disk we're looking at?
            int disk_size = _num_disk - ddx;

            //-- Check to see if it's a match.
            std::size_t current_val = 0;
            if (_state[pdx][height] == disk_size) {

                if (_bicolor) {
                    // 5 States 

                    //-- 0 : Disk not present at position
                    //-- 1 : Black disk present
                    //-- 2 : White disk present
                    //-- 3 : Black disk with white disk ontop
                    //-- 4 : White disk with black disk ontop

                    // Need to look above the current disk (height+1) to determine state.


                    // (case 1/2) height += 1
                    // (case 3/4) height += 2

                } else {
                    // 2 States

                    //-- 0 : Disk not present at position
                    //-- 1 : Disk is present

                    //current_val = pow(2, ddx + (pdx * _num_disk));

                    //-- Increase the height.
                    height++;
                }
            }

            ret += current_val;
        }
    }

    for (auto h : hash) std::cout << h << " ";
    std::cout << std::endl;

    return ret;
}



bool Board::move(int from, int to) {

    //-- Check if to and from are within range of our pegs.
    if (from < 0 || from >= _num_peg) { return false; }
    if (to   < 0 || to   >= _num_peg) { return false; }
    
    //-- Check if the from position has a disk to take.
    if (_state[from].size() == 0) { return false; }

    //-- Check if the top disk of from can go onto the top disk of to.
    Disk disk = _state[from].back();
    if (_state[to].size() && disk > _state[to].back()) { return false; }

    //-- Else everything is okay, make the move.
    _state[from].pop_back();
    _state[to].push_back(disk);

    return true;
}
