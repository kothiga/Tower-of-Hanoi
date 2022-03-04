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
#include <map>
#include <queue>
#include <utility>
#include <vector>

#include <board.hpp>


typedef std::pair<int,int> pii;
typedef unsigned long long ull;


class Solver {

    private:
    /* ============================================================================
    **  Private variables of the solver.
    ** ============================================================================ */
    std::map<ull,std::vector<pii>> _sssp;
    
    std::shared_ptr<Board> _board;
    std::vector<pii>       _moves;
    
    bool _solved;

    
    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    Solver(std::size_t pegs=3, std::size_t disks=3, bool isBicolor=false);


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~Solver();

    
    /* ===========================================================================
    **  Perform a single-source shortest path search from the goal state 
    **  to all existing states for quick look ups of the next best move.
    ** =========================================================================== */
    void solve();


    /* ===========================================================================
    **  Look up the next best move corresponding to 
    ** =========================================================================== */
    pii getBestMove(ull hash);


    private:
    /* ===========================================================================
    **  Temp.
    ** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_SOLVER_HPP */
