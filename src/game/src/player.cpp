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

#include <player.hpp>


Player::Player() {

}


Player::~Player() {

}


action Player::getAction() {

    //-- Read in some input.
    std::string inp = this->readInput();
    std::vector<std::string> input = this->parseString(inp);

    //-- Parse out the action
    action ret;

    if (input.size()) {

        //-- What is the command?
        std::string cmd = input[0];

        if (cmd == "quit" || cmd == "exit") {
            ret.selection = action::QUIT;
            return ret;
        }

        if (cmd == "dist") {
            ret.selection = action::DIST;
            return ret;
        }

        if (cmd == "hash") {
            ret.selection = action::HASH;
            return ret;
        }

        if (cmd == "hint") {
            ret.selection = action::HINT;
            return ret;
        }

        if (cmd == "status" || cmd == "show") {
            ret.selection = action::STATUS;
            return ret;
        }

        if (cmd == "goal") {
            ret.selection = action::GOAL;
            return ret;
        }

        if (cmd == "help") {
            ret.selection = action::HELP;
            ret.msg = this->getHelpString();
            return ret;
        }

        if (cmd == "set") {

            //-- Check correct number of inputs for command.
            if (input.size() != 2) {
                ret.selection = action::HELP;
                ret.msg = "[Error] Incorrect number of arguments for ``set`` command!! "
                    "Received ``" + std::to_string(input.size()) + "`` expected ``2``.\n\n"
                    + this->getHelpString();
                return ret;
            }

            //-- Get the hash from the string.
            std::string hash;
            hash = input[1];

            //-- Check that this is an integer (unsigned long long).
            if (!this->isStringInt(hash, false)) {
                ret.selection = action::HELP;
                ret.msg = "[Error] Received ``" + hash + "``. Expected an unsigned integer.\n\n"
                + this->getHelpString();
                return ret;
            }

            //-- Set meets selection criteria. Return it.
            ret.selection = action::SET;
            try {
                ret.hash = std::stoull(hash);
            } catch(std::out_of_range) {

                ret.selection = action::HELP;
                ret.msg = "[Error] Received an unsigned long long value out of range. Got ``" 
                + hash + "``. Please ensure hash is a propper unsigned long long.\n\n" 
                + this->getHelpString();

            }

            return ret;
        }

        if (cmd == "move") {

            //-- Check correct number of inputs for command.
            if (input.size() != 3) {
                ret.selection = action::HELP;
                ret.msg = "[Error] Incorrect number of arguments for ``move`` command!! "
                    "Received ``" + std::to_string(input.size()) + "`` expected ``3``.\n\n"
                    + this->getHelpString();
                return ret;
            }

            //-- Get the from and to strings.
            std::string u, v;
            u = input[1]; v = input[2];

            //-- Check that these are both integers.
            if (!this->isStringInt(u) || !this->isStringInt(v)) {
                ret.selection = action::HELP;
                ret.msg = "[Error] Received ``" + u + "`` and ``" + v + "``. Expected two integers.\n\n"
                + this->getHelpString();
                return ret;
            }

            //-- Move meets selection criteria. Return it.
            //-- Note:
            //--   U and V at this stage may be a negative integer.
            //--   It is up to the game to ensure the move passed
            //--   passed to the board uses values in the correct 
            //--   range, as the player isn't aware of the board conf.
            ret.selection = action::MOVE;
            try {

                ret.from = std::stoi(u);
                ret.to   = std::stoi(v);

            } catch(std::out_of_range) {

                ret.selection = action::HELP;
                ret.msg = "[Error] Received an integer value out of range. Got ``" 
                + u + "`` and ``" + v + "``. Please ensure u and v are propper integers.\n\n" 
                + this->getHelpString();

            }

            return ret;
        }

        //-- Action not found.
        ret.selection = action::HELP;
        ret.msg = "[Error] Unknown action ``" + inp + "`` given!!\n\n" + this->getHelpString();

    } else {
        ret.selection = action::HELP;
        ret.msg = "[Error] No action given!!\n\n" + this->getHelpString();
    }

    return ret;
}


std::string Player::getHelpString() {

    std::string ret;
    ret = \
    "Possible actions:                                               \n"
    "    help                ``display this helpful message``        \n"
    "    move int(u) int(v)  ``move the disk from peg u to peg v``   \n"
    "    status/show         ``get current board configuration``     \n"
    "    goal                ``show what the goal state``            \n"
    "    hint                ``request a hint for what next action`` \n"
    "    hash                ``get the current board state hash``    \n"
    "    dist                ``get the distance to the goal state``  \n"
    "    set longlong(hash)  ``set the current board state as hash`` \n"
    "    quit/exit           ``stop the game and exit``              \n"
    "";

    return ret;
}


std::vector<std::string> Player::parseString(const std::string& str) {
    
    //-- Set up the parse and return buffer.
    std::stringstream ss(str);
    std::vector< std::string > ret;

    std::string s;
    while (ss >> s) {

        //-- Transform string to be all lowercase.
        std::string::iterator it = s.begin();
        while (it != s.end()) {
            *it = std::tolower(*it); ++it;
        }

        //-- Push string into return buffer.
        ret.push_back(s);
    }

    return ret;
}


bool Player::isStringInt(const std::string& str, bool be_signed/*=true*/) {
    //-- Check if string contains any characters that aren't 0-9 or negative.
    return !str.empty() && str.find_first_not_of( 
        (be_signed ? "-0123456789" : "0123456789")) == std::string::npos;
}
