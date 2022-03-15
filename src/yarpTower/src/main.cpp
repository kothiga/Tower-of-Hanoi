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

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <yarp/os/Network.h>

#include <yarpPlayer.hpp>
#include <game.hpp>


std::map<std::string,std::string> getArgs(int, char**);


int main (int argc, char **argv) {

    //-- Init the yarp network.
    yarp::os::Network yarp;

    //-- Get the arguments from input.
    std::map<std::string,std::string> conf = getArgs(argc, argv);

    //-- Init the iostream player.
    std::shared_ptr<YarpPlayer> player(new YarpPlayer);

    //-- Init and configure the game.
    Game tower(player);
    tower.configure(conf);
    
    //-- Run the game and return its status.
    return tower.run();
}


std::map<std::string,std::string> getArgs(int argc, char **argv) {

    //-- Init the dictionary for the arguments.
    std::map<std::string,std::string> dict;
    dict.clear();

    return dict;
}
