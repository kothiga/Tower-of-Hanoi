# Copyright: (C) 2022, SIRRL Social and Intelligent Robotics Research Laboratory, University of Waterloo
# Authors: Austin Kothig <austin.kothig@uwaterloo.ca>
# CopyPolicy: Released under the terms of the MIT License.

cmake_minimum_required(VERSION 3.12)


set(TARGET_NAME iosTower)

set(${TARGET_NAME}_SRC
    src/main.cpp
    src/iosPlayer.cpp
    ../game/src/game.cpp
    ../game/src/player.cpp
    ../game/src/board.cpp
    ../game/src/solver.cpp
)

set(${TARGET_NAME}_HDR
    include/iosPlayer.hpp
    ../game/include/game.hpp
    ../game/include/player.hpp
    ../game/include/board.hpp
    ../game/include/solver.hpp
)

add_executable(
    ${TARGET_NAME} 
    ${${TARGET_NAME}_HDR}
    ${${TARGET_NAME}_SRC}
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE 
    ./include
    ../game/include
)

target_link_libraries(
    ${TARGET_NAME}
)

install(
    TARGETS        ${TARGET_NAME}
    DESTINATION    bin  
)

############################################################
