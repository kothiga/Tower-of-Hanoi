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
#include <unordered_map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include <board.hpp>


typedef std::pair<int,int> pii;
typedef unsigned long long ull;

struct move {
    int from, to;
    ull hash;
    ull dist;
};

typedef std::vector<move> mvec;


class Solver {

    private:
    /* ============================================================================
    **  Private variables of the solver.
    ** ============================================================================ */
    std::shared_ptr<Board>       _board;
    std::unordered_map<ull,mvec> _sssp;
    std::unordered_map<ull,ull>  _dest;
    std::vector<pii>             _moves;
    
    bool _solved;
    ull  _start_hash;
    ull  _goal_hash;

  
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
    **  Look up the next best move corresponding to the input hash.
    **
    ** @param hash  the hash corresponding to a board state. 
    **
    ** @return a pair of ints that represent the next best move.
    ** =========================================================================== */
    pii getBestMove(ull hash);


    /* ===========================================================================
    **  Flush the single source shortest path from all board states to the goal state.
    **
    ** @return a string in json format.
    ** =========================================================================== */
    std::string flushSolution();


    private:
    /* ===========================================================================
    **  Temp.
    ** =========================================================================== */
    void temp();
    
};

#endif /* TOWER_OF_HANOI_SOLVER_HPP */
