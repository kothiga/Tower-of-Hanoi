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

#include <memory>
#include <vector>


struct Disk {
    int size;
    int color;
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
    **  Get a showable state of the game board.
    **
    ** @return a string that can be passed to the user interface.
    ** =========================================================================== */
    std::string getShowableState();


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
