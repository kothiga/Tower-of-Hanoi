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

#include <yarpPlayer.hpp>


YarpPlayer::YarpPlayer() : Player() {

    //-- Open the yarp rpc port.
    port.open("/yarpTower/rpc");

}


YarpPlayer::~YarpPlayer() {
    std::cout << "[debug] YarpPlayer Destroyed." << std::endl;
}


void YarpPlayer::writeOutput(const std::string output) {

    //-- Flush the output to the rpc client.
    yarp::os::Bottle response;
    response.addString(output);

    port.reply(response);

    return;
}


std::string YarpPlayer::readInput() {

    //-- Get some input from the an rpc client.
    yarp::os::Bottle cmd;
    port.read(cmd, true);

    std::string ret;
    ret = cmd.toString();

    return ret;
}
