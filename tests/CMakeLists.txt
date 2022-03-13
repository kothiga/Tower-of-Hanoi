# Copyright: (C) 2022, SIRRL Social and Intelligent Robotics Research Laboratory, University of Waterloo
# Authors: Austin Kothig <austin.kothig@uwaterloo.ca>
# CopyPolicy: Released under the terms of the MIT License.

cmake_minimum_required(VERSION 3.12)

# Get the googletest suite.
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

############################################################

set(TARGET_NAME test_TowerOfHanoi)

include_directories(../src/game/include/)

set(${TARGET_NAME}_SRC
    ../src/game/src/board.cpp
    ../src/game/src/solver.cpp
)

set(${TARGET_NAME}_HDR
    ../src/game/include/board.hpp
    ../src/game/include/solver.hpp
)

set(${TARGET_NAME}_tests
    boardTest.cpp
    gameTest.cpp
    solverTest.cpp
)

add_executable(
    ${TARGET_NAME}
    ${${TARGET_NAME}_HDR}
    ${${TARGET_NAME}_SRC}
    ${${TARGET_NAME}_tests}
)

target_link_libraries(
    ${TARGET_NAME}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})

############################################################
