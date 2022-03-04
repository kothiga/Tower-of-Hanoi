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
    this->_goal.clear();
    // <REMOVE>
    std::cout << "[debug] Board Destroyed." << std::endl;
    // <\REMOVE>
}


bool Board::init() {

    //-- Allocate storage for the board.
    this->allocateNewBoard();
    
    //-- Check bounds for number of pegs and disks.
    if (_num_disk < 3 || _num_disk > 6) { return false; } //TODO: What is the upperbound for these w.r.t. 
    if (_num_peg  < 3 || _num_peg  > 6) { return false; } //      the hash function and 64-bit ull?

    //-- Allocate the goal only once.
    _goal.clear();
    for (std::size_t idx = 0; idx < _num_peg; ++idx) {
        _goal.push_back(std::vector<Disk>());
        _goal[idx].reserve(_num_disk*2 + 1);
    }

    //-- Init the board state to the default state.
    if (_bicolor) {
        for (std::size_t size = 0; size < _num_disk; ++size) {
            _state[0].push_back(Disk(_num_disk - size, (size+1) % 2));
            _state[1].push_back(Disk(_num_disk - size, (size+2) % 2));

            _goal[0].push_back(Disk(_num_disk - size, 0)); // Black.
            _goal[1].push_back(Disk(_num_disk - size, 1)); // White.
        }
    } else {
        for (std::size_t size = 0; size < _num_disk; ++size) {
            _state[0].push_back(Disk(_num_disk - size));

            _goal[_num_peg-1].push_back(Disk(_num_disk - size));
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


std::vector<std::vector<Disk>> Board::getRawGoal() {
    return _goal;
}


std::string Board::getShowableState() {
    return drawBoard(_state);    
}


std::string Board::getShowableGoal() {
    return drawBoard(_goal);    
}


ull Board::getHashableState() {
    
    //-- Set up a vector that the hash can be computed from.
    std::vector<std::size_t> encoding = generateEncoding(_state);

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


ull Board::getHashableGoal() {

    //-- Set up a vector that the hash can be computed from.
    std::vector<std::size_t> encoding = generateEncoding(_goal);
    
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


ull Board::computeHash(std::vector<std::size_t> encoding) {

    //-- Compute the hash of the board state.
    ull hash = 0;

    ull power = 1;
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


std::vector<std::size_t> Board::generateEncoding(const std::vector<std::vector<Disk>> board) {

    //-- Set up a vector to hold the converted hash.
    std::vector<std::size_t> encoding(_num_peg * _num_disk);

    //-- Step through the board state and build a vector to hash.
    for (std::size_t pdx = 0; pdx < board.size(); ++pdx) {
        for (std::size_t ddx = 0; ddx < board[pdx].size(); ++ddx) {
            
            //-- Get a copy of this disk.
            Disk d = board[pdx][ddx];

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
                if (ddx+1 < board[pdx].size()) {

                    //-- Get the disk above and check if the sizes are the same.
                    Disk top = board[pdx][ddx+1];
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


std::vector<std::size_t> Board::generateEncoding(ull hash) {

    //-- Set up a vector to hold the converted hash.
    std::vector<std::size_t> encoding(_num_peg * _num_disk);

    //-- Recover the encoding from the hash.
    for (std::size_t edx = 0; edx < encoding.size(); ++edx) {

        encoding[edx] = hash % ( _bicolor ? 5 : 2 );
        hash /= ( _bicolor ? 5 : 2 );

    }

    return encoding;
}


bool Board::move(const int from, const int to) {

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


std::string Board::drawBoard(const std::vector<std::vector<Disk>> board) {

    //-- Set some aliases for the ascii characters.
    const std::string peg   = "\u2502";
    const std::string base  = "\u2632";
    const std::string black = "\u2593";
    const std::string white = "\u2591";
    const std::string btwn  = "  ";

    //-- Init the return string.
    std::string ret = "";

    //-- Use some buffer for a single line.
    std::string line = "";
    
    //-- Width of a line.
    int line_width = 1 + btwn.length() + (((_num_disk * 2) + 1 + btwn.length()) * _num_peg);
    line += repeatString(" ", line_width);// + "\n";
    
    //-- Set the position indicators.
    int idx = 1;
    for (int pdx = 0; pdx < _num_peg; ++pdx) {
        idx += btwn.length() + _num_disk;
        
        line[idx-1] = '[';
        line[idx]   = '0'+pdx;
        line[idx+1] = ']';

        idx += 1 + _num_disk;
    }

    //-- Append the first line.
    ret = line + ret;

    //-- Add a line for the base of the game board.
    line = " ";
    line += repeatString(base, line_width-2) + "\n";
    ret = line + ret;

    //-- Find the max height of a single peg.
    std::size_t max_height = 0;
    for (std::size_t idx = 0; idx < board.size(); ++idx) {
        max_height = (board[idx].size() > max_height) ? board[idx].size() : max_height;
    }
    max_height += 1;


    //-- Step through each height 
    for (std::size_t hdx = 0; hdx < max_height; ++hdx) {

        //-- Clear the buffer an init the first space.
        line = " ";
        for (std::size_t pdx = 0; pdx < _num_peg; ++pdx) {

            //-- Add some space between pegs.
            line += btwn;

            //-- Empty position case.
            if (board[pdx].size() <= hdx) {
                line += std::string(_num_disk, ' ') + peg + std::string(_num_disk, ' ');
            } else {
                Disk d = board[pdx][hdx];
                line += std::string(_num_disk - d.getSize(), ' ');
                line += repeatString((d.getColor() ? white : black), (d.getSize()*2) + 1);
                line += std::string(_num_disk - d.getSize(), ' ');
            }
        }

        //-- Add this row to the return buffer.
        ret = line + "\n" + ret;
    }


    ret = "\n\n" + ret + "\n";
    //std::cout << ret << std::endl;
    //std::cout << "01234567890123456789012345678901234567890" << std::endl;
    //std::cout << "0         1         2         3         4" << std::endl;
    
    return ret;
}


std::string Board::repeatString(const std::string& str, int n) {
    std::ostringstream os;
    while (n--)
        os << str;
    return os.str();
}
