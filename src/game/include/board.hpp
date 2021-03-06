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
#include <memory>
#include <sstream>
#include <string>
#include <vector>


typedef unsigned long long ull;


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
        os << "(" << (dsk.color ? "W1" : "B0") << ":" << dsk.size << ")"; 
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
    std::vector<std::vector<Disk>> _goal;  // Goal state.



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
    bool setFromHashableState(ull hash);


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
    **  Get the raw goal state of the game board.
    **
    ** @return a 2D vector that holds a copy of raw goal state.
    ** =========================================================================== */
    std::vector<std::vector<Disk>> getRawGoal();


    /* ===========================================================================
    **  Get a showable state of the board state or goal state.
    **
    ** @return a string that can be passed to the user interface.
    ** =========================================================================== */
    std::string getShowableState();
    std::string getShowableGoal();


    /* ===========================================================================
    **  Get a unique descriptor of the state of the game board or the goal state.
    **
    ** @return a hash that can be passed to a solving interface.
    ** =========================================================================== */
    ull getHashableState();
    ull getHashableGoal();


    /* ===========================================================================
    **  Compute the hash of an input vector representing the state of the game board.
    **
    ** @param encoding  a vector holding the positional presence of disks.
    **
    ** @return a unique hash for the vector.
    ** =========================================================================== */
    ull computeHash(std::vector<std::size_t> encoding);


    /* ===========================================================================
    **  Compute the corresponding vector repersenting the game board from an input hash.
    **  If no hash is provided, will generate the encoding from the board's raw state.
    **
    ** @param [optional] hash  a unique hash for a board state.
    **
    ** @return an encoding representing the state of the game board.
    ** =========================================================================== */
    std::vector<std::size_t> generateEncoding(const std::vector<std::vector<Disk>> board);
    std::vector<std::size_t> generateEncoding(ull hash);


    /* ===========================================================================
    **  Move the top peg from one peg to another.
    **
    ** @param from  The source peg.
    ** @param to    The target peg.
    **
    ** @return a string that can be passed to the user interface.
    ** =========================================================================== */
    bool move(const int from, const int to);


    private:
    /* ===========================================================================
    **  Allocate fresh storage space for the board.
    ** =========================================================================== */
    void allocateNewBoard();


    /* ===========================================================================
    **  Draw a nicely formatted board.
    ** 
    ** @param board  Desired game board to draw (current/goal state).
    **
    ** @return A UTF-8 string to pass to be displayed.
    ** =========================================================================== */
    std::string drawBoard(const std::vector<std::vector<Disk>> board);


    /* ===========================================================================
    **  Helper function that returns a string str repeated n times.
    ** 
    ** @param str  Desired repeated string.
    ** @param n    The number of times to repeat it.
    **
    ** @return str*n
    ** =========================================================================== */
    std::string repeatString(const std::string& str, int n);

};

#endif /* TOWER_OF_HANOI_BOARD_HPP */
