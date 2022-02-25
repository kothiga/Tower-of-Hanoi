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

#ifndef TOWER_OF_HANOI_BOARD_HPP
#define TOWER_OF_HANOI_BOARD_HPP

#include <iostream>
#include <cmath>
#include <memory>
#include <vector>


class Disk {
    private:
    int size, color;

    public:
    Disk(int s, int c=0) : size(s), color(c) {}
    int  getSize()  { return size;  }
    int  getColor() { return color; }
    bool operator>(const Disk& lhs)  { return this->size >  lhs.size; }
    bool operator==(const Disk& lhs) { return this->size == lhs.size; }
    bool operator==(const int lhs)   { return this->size == lhs;      }
    friend std::ostream& operator<<(std::ostream& os, const Disk& dsk) { 
        os << "(" << dsk.color << "," << dsk.size << ")"; 
        return os; 
    }
};


class Board {

    private:
    /* ============================================================================
    **  Private variables of the board.
    ** ============================================================================ */
    std::size_t _num_peg;  // Number of pegs.
    std::size_t _num_disk; // Number of disks.
    bool        _bicolor;  // Whether the game is bicolor or normal version.

    bool _board_set;
    std::vector<std::vector<Disk>> _state; // Board state.


    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Board(std::size_t pegs=3, std::size_t disks=3, bool isBicolor=false);


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~Board();


    /* ===========================================================================
    **  Initialize the board state with the current settings.
    **
    ** @return success of initializing the board.
    ** =========================================================================== */
    bool init();


    /* ============================================================================
    **  Set the number of pegs for the board. 
    **  Setting this after calling init will put the board into an uninitialized state.
    **
    ** @param pegs  Number of pegs (positions) a disk can go on the board.
    ** ============================================================================ */
    void setNumPegs(std::size_t pegs);


    /* ============================================================================
    **  Set the number of disks for the board. 
    **  Setting this after calling init will put the board into an uninitialized state.
    **
    ** @param disks  Number of disks that will move around on the board.
    ** ============================================================================ */
    void setNumDisks(std::size_t disks);


    /* ============================================================================
    **  Set the board type to bicolor (true) or normal (false). 
    **  Setting this after calling init will put the board into an uninitialized state.
    **
    ** @param isBicolor  Truth value of if the board type should be bicolor or not.
    ** ============================================================================ */
    void setBicolor(bool isBicolor);


    /* ===========================================================================
    **  Set the game board state from a unique descriptor.
    **
    ** @param hash  The unique descriptor for the desired board state.
    **
    ** @return success of if the given hash was accepted. If false, board state is unchanged.
    ** =========================================================================== */
    bool setFromHashableState(unsigned long long hash);


    /* ===========================================================================
    **  Get the number of pegs for the board.
    **
    ** @return a long int that tells the number of pegs.
    ** =========================================================================== */
    std::size_t getNumPegs();


    /* ===========================================================================
    **  Get the number of disks (per color) for the board.
    **
    ** @return a long int that tells the number of disks (per color).
    ** =========================================================================== */
    std::size_t getNumDisks();


    /* ===========================================================================
    **  Get if the board is set for mono or bicolor version.
    **
    ** @return a boolean that tells if the game is bicolor.
    ** =========================================================================== */
    bool getIsBicolor();


    /* ===========================================================================
    **  Get the raw state of the game board.
    **
    ** @return a 2D vector that holds a copy of raw board state.
    ** =========================================================================== */
    std::vector<std::vector<Disk>> getRawState();


    /* ===========================================================================
    **  Get a showable state of the game board.
    **
    ** @return a string that can be passed to the user interface.
    ** =========================================================================== */
    std::string getShowableState();


    /* ===========================================================================
    **  Get a unique descriptor of the state of the game board.
    **
    ** @return a hash that can be passed to a solving interface.
    ** =========================================================================== */
    unsigned long long getHashableState();


    /* ===========================================================================
    **  Move the top peg from one peg to another.
    **
    ** @param from  The source peg.
    ** @param to    The target peg.
    **
    ** @return a string that can be passed to the user interface.
    ** =========================================================================== */
    bool move(int from, int to);


    private:
    /* ===========================================================================
    **  Temp.
    ** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_BOARD_HPP */
