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

#ifndef TOWER_OF_HANOI_PLAYER_HPP
#define TOWER_OF_HANOI_PLAYER_HPP

#include <memory>
#include <sstream>
#include <string>
#include <vector>


struct action {
    int from, to; std::string msg;
    enum { HELP, MOVE, STATUS, GOAL, HINT, QUIT } selection;
};


class Player {

    private:
    /* ============================================================================
    **  Temp.
    ** ============================================================================ */
    std::size_t _temp;

    
    protected:
    /* ============================================================================
    **  Temp.
    ** ============================================================================ */
    std::size_t _temp2;


    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Player();


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~Player();


    /* ============================================================================
    **  Get an action using the pure virutal functions implemented by the 
    **  concrete implementations.
    **
    ** @retrun an action to pass to the game environment.
    ** ============================================================================ */
    action getAction();


    /* ============================================================================
    **  Pure virtual function to be implemented in subclasses.
    **  Appropriately flush some output to the user of the interface.
    ** ============================================================================ */
    virtual void writeOutput(const std::string) = 0;


    protected:
    /* ============================================================================
    **  Pure virtual function to be implemented in subclasses.
    **  Appropriately read in some input from the user interface.
    ** ============================================================================ */
    virtual std::string readInput() = 0;


    /* ===========================================================================
    **  Get a string containing command for helping.
    ** 
    ** @return text to be returned and flushed by the interface.
    ** =========================================================================== */
    std::string getHelpString();


    private:
    /* ===========================================================================
    **  Get a string containing command for helping.
    ** 
    ** @return text to be returned and flushed by the interface.
    ** =========================================================================== */
    std::vector<std::string> parseString(const std::string& str);

    // (filters floating point numbers too)
    bool isStringInt(const std::string& str);
    
};

#endif /* TOWER_OF_HANOI_PLAYER_HPP */
