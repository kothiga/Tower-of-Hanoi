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

#ifndef TOWER_OF_HANOI_IOSPLAYER_HPP
#define TOWER_OF_HANOI_IOSPLAYER_HPP

#include <iostream>
#include <memory>
#include <string>

#include <player.hpp>


class IosPlayer : public Player {

    private:
    /* ============================================================================
	**  Temp.
	** ============================================================================ */
	std::size_t _temp3;


    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    IosPlayer();


    /* ===========================================================================
	**  Destructor.
	** =========================================================================== */
    ~IosPlayer();


    /* ============================================================================
    **  Appropriately flush some output to the user of the interface.
    **
    ** @param output string containing text to flush to the user.
    ** ============================================================================ */
    void writeOutput(const std::string output);


    private:
    /* ===========================================================================
	**  Read input from the iostream.
    **
    ** @return clean string to parse into an action.
	** =========================================================================== */
    std::string readInput();
    
};

#endif /* TOWER_OF_HANOI_IOSPLAYER_HPP */
