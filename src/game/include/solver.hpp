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

#ifndef TOWER_OF_HANOI_SOLVER_HPP
#define TOWER_OF_HANOI_SOLVER_HPP

#include <memory>

class Solver {
    
    private:
    /* ============================================================================
	**  Temp.
	** ============================================================================ */
	std::size_t _temp;

    
    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Solver();


    /* ===========================================================================
	**  Destructor.
	** =========================================================================== */
    ~Solver();


    private:
    /* ===========================================================================
	**  Temp.
	** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_SOLVER_HPP */
