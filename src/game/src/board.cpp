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
}


Board::~Board() {
    this->_state.clear();
}


bool Board::init() {
    return false;
}


void Board::setNumPegs(std::size_t pegs) {

    this->_board_set = false; // reset the board state.
    this->_num_peg = pegs;

    return;
}


void Board::setNumDisks(std::size_t disks) {

    this->_board_set = false; // reset the board state.
    this->_num_disk = disks;

    return;
}


void Board::setBicolor(bool isBicolor) {

    this->_board_set = false; // reset the board state.
    this->_bicolor = isBicolor;

    return;
}


std::string Board::getShowableState() {
    return "";
}


bool Board::move(int from, int to) {
    return false;
}
