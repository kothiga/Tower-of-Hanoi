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

#include <iosPlayer.hpp>


IosPlayer::IosPlayer() : Player() {


}


IosPlayer::~IosPlayer() {

}


void IosPlayer::writeOutput(const std::string output) {

    //-- Flush the output to the user.
    std::cout << output << std::endl;

    return;
}


std::string IosPlayer::readInput() {

    //-- Get some input from the input stream.
    std::cout << "\n>> ";
    std::string ret;
    getline(std::cin, ret);

    return ret;
}
