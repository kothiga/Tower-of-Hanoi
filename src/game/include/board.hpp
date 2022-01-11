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

class Board {

    private:
    /* ============================================================================
	**  Temp.
	** ============================================================================ */
	std::size_t _temp;

    
    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Board();


    /* ===========================================================================
	**  Destructor.
	** =========================================================================== */
    ~Board();


    private:
    /* ===========================================================================
	**  Temp.
	** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_BOARD_HPP */
