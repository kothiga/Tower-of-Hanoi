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

#ifndef TOWER_OF_HANOI_YARPPLAYER_HPP
#define TOWER_OF_HANOI_YARPPLAYER_HPP

#include <iostream>
#include <memory>
#include <string>

#include <yarp/os/Bottle.h>
#include <yarp/os/RpcServer.h>

#include <player.hpp>


class YarpPlayer : public Player {

    private:
    /* ============================================================================
    **  Yarp RPC server for receiving commands and replying information.
    ** ============================================================================ */
    yarp::os::RpcServer port;


    public:
    /* ============================================================================
    **  Main Constructor.
    ** ============================================================================ */
    YarpPlayer();


    /* ===========================================================================
    **  Destructor.
    ** =========================================================================== */
    ~YarpPlayer();


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

#endif /* TOWER_OF_HANOI_YARPPLAYER_HPP */
