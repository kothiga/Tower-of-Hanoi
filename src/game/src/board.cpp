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
    // <REMOVE>
    std::cout << "[debug] Board Destroyed." << std::endl;
    // <\REMOVE>
}


bool Board::init() {

    //-- Allocate storage for the board.
    this->allocateNewBoard();
    
    //-- Check bounds for number of pegs and disks.
    if (_num_disk < 3 || _num_disk > 6) { return false; }
    if (_num_peg  < 3 || _num_peg  > 6) { return false; }

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
    
    //-- Decode the state vec from the hash.
    std::vector<std::size_t> encoding = generateEncoding(hash);

    //-- Allocate storage for the board.
    this->allocateNewBoard();

    //-- For each disk size, choose to place a disk on each peg
    //-- based on the values in the state vec.
    for (std::size_t ddx = 0; ddx < _num_disk; ++ddx) {
        
        std::vector<std::size_t> placed((_bicolor ? 2 : 1), 0);
        for (std::size_t pdx = 0; pdx < _num_peg; ++pdx) {
            
            //-- Calculate the current pos in the vec.
            std::size_t idx = ddx + (pdx * _num_disk);
            
            //-- If zero, no disk to be placed.
            if (encoding[idx] == 0) { continue; }

            //-- Get the size and color 
            std::size_t disk_size  = (_num_disk - ddx);
            std::size_t disk_color = (encoding[idx] - 1) % 2;

            //-- Push the disk onto the board, and increment the
            //-- number of disks for this color placed.
            _state[pdx].push_back(Disk(disk_size, disk_color));
            placed[disk_color] += 1;

            std::cout << _state[pdx][ _state[pdx].size()-1 ] << " ";

            //-- Check to see if this state holds a second disk.
            if (encoding[idx] >= 3) {
                std::size_t second_color = (disk_color + 1) % 2;
                _state[pdx].push_back(Disk(disk_size, second_color));
                placed[second_color] += 1;
                std::cout << _state[pdx][ _state[pdx].size()-1 ] << " ";
            }
        }

        //-- Check to see if too many or too few disks were placed per color.
        //-- If Mono, this will just be one check, if Bicolor it will be two.
        for (std::size_t idx = 0; idx < placed.size(); ++idx) {
            if (placed[idx] != 1) { return false; }
        }
        std::cout << std::endl;
    } 
    std::cout << std::endl;
    

    //-- Declare that the board has been initialized.
    return _board_set = true;
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
            ret += "(";
            ret += (d.getColor() ? "W1":"B0");
            ret += ":" + std::to_string(d.getSize()) + ") ";
        } 
        ret += "\n";
    }
    ret += ">>>\n";
    // <\REMOVE>


    return ret;
}


unsigned long long Board::getHashableState() {
    
    //-- Set up a vector that the hash can be computed from.
    std::vector<std::size_t> encoding = generateEncoding();

   // <REMOVE>
    for (int idx = 0; idx < encoding.size(); ++idx) {
        if ((idx % _num_disk) == 0) std::cout << "| ";
        std::cout << encoding[idx] << " ";
    }
    std::cout << "|" << std::endl;
    // <\REMOVE>

    //-- Compute and return the hash from the encoding.
    return computeHash(encoding);
}


unsigned long long Board::computeHash(std::vector<std::size_t> encoding) {

    //-- Compute the hash of the board state.
    unsigned long long hash = 0;

    long long int power = 1;
    for (std::size_t edx = 0; edx < encoding.size(); ++edx) {

        // <REMOVE>
        if (edx) std::cout << " + ";
        std::cout << encoding[edx] << "*" << power;
        // <\REMOVE>

        hash += (encoding[edx] * power);
        power *= ( _bicolor ? 5 : 2 );
    }
    // <REMOVE>
    std:: cout << " = " << hash << std::endl;
    // <\REMOVE>

    return hash;
}


std::vector<std::size_t> Board::generateEncoding() {

    //-- Set up a vector to hold the converted hash.
    std::vector<std::size_t> encoding(_num_peg * _num_disk);

    //-- Step through the board state and build a vector to hash.
    for (std::size_t pdx = 0; pdx < _state.size(); ++pdx) {
        for (std::size_t ddx = 0; ddx < _state[pdx].size(); ++ddx) {
            
            //-- Get a copy of this disk.
            Disk d = _state[pdx][ddx];

            //-- Compute the index of the encoding vector from the current disk.
            std::size_t edx = (_num_disk - d.getSize()) + (pdx * _num_disk);

            if (_bicolor) {
                // 5 States 

                //-- 0 : Disk not present at position
                //-- 1 : Black disk present
                //-- 2 : White disk present
                //-- 3 : Black disk with white disk ontop
                //-- 4 : White disk with black disk ontop

                //-- Find which state we have.
                std::size_t state = d.getColor() + 1; // Black:0, White:1


                //-- Need to look above the current disk (height+1) to determine state.
                if (ddx+1 < _state[pdx].size()) {

                    //-- Get the disk above and check if the sizes are the same.
                    Disk top = _state[pdx][ddx+1];
                    if (d.getSize() == top.getSize()) {

                        //-- Case 3/4: adjust state val.
                        state += 2;

                        //-- Advance disk index so we don't look at this twice.
                        ddx += 1;
                    }
                }

                //-- Set the found state.
                encoding[edx] = state;

            } else {
                // 2 States

                //-- 0 : Disk not present at position
                //-- 1 : Disk is present
                encoding[edx] = 1;
            }
        }
    }

    return encoding;
}


std::vector<std::size_t> Board::generateEncoding(unsigned long long hash) {

    //-- Set up a vector to hold the converted hash.
    std::vector<std::size_t> encoding(_num_peg * _num_disk);

    for (std::size_t edx = 0; edx < encoding.size(); ++edx) {

        // <REMOVE>
        //std::cout << hash << "\t= ";
        // <\REMOVE>

        encoding[edx] = hash % ( _bicolor ? 5 : 2 );
        hash /= ( _bicolor ? 5 : 2 );

        // <REMOVE>
        //std::cout << encoding[edx] << "*" << ( _bicolor ? 5 : 2 ) << " + " << hash << std::endl;
        // <\REMOVE>
    }

    return encoding;
}


bool Board::move(int from, int to) {

    // If the board state has not been set, return false.
    if (!_board_set) { return false; }

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


void Board::allocateNewBoard() {

    //-- Declare that the board is uninitialized.
    _board_set = false;

    //-- Clear out board state to start anew.
    _state.clear();

    //-- Allocate the proper number of pegs for the board.
    for (std::size_t idx = 0; idx < _num_peg; ++idx) {
        _state.push_back(std::vector<Disk>());
        _state[idx].reserve(_num_disk*2 + 1);
    }

    return;
}
