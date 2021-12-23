# Copyright: (C) 2022, SIRRL Social and Intelligent Robotics Research Laboratory, University of Waterloo
# Authors: Austin Kothig <austin.kothig@uwaterloo.ca>
# CopyPolicy: Released under the terms of the MIT License.

cmake_minimum_required(VERSION 3.12)


# Add iostream based interface.
add_subdirectory(iosTower)


# Add yarp based interface.
if(BUILD_YARP)
    add_subdirectory(yarpTower)
endif()


# Add ncurses based interface.
if(BUILD_NCURSES)
    add_subdirectory(ncursesTower)
endif()

############################################################
