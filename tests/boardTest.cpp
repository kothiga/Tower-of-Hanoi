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
#include <board.hpp>
#include <gtest/gtest.h>

/*
// Demonstrate some basic assertions.
TEST(BoardTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
*/

//
// Helper function.
//
void printState(std::vector<std::vector<Disk>> state) {
    std::cout << ">>>" << std::endl;
    for (auto p : state) {
        for (auto d : p) {
            std::cout << d << " "; 
        } 
        std::cout << std::endl;
    }
    std::cout << ">>>" << std::endl;
    return;
}


//
// BoardTest_BoardConstructor
//
TEST(BoardTest, BoardConstructor_Default) {

    Board b;
    EXPECT_EQ(3, b.getNumPegs());
    EXPECT_EQ(3, b.getNumDisks());
    EXPECT_FALSE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

}
TEST(BoardTest, BoardConstructor_Parameter1) {

    Board b(/*pegs=*/4, /*disks=*/5);
    EXPECT_EQ(4, b.getNumPegs());
    EXPECT_EQ(5, b.getNumDisks());
    EXPECT_FALSE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

}
TEST(BoardTest, BoardConstructor_Parameter2) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_EQ(3, b.getNumPegs());
    EXPECT_EQ(4, b.getNumDisks());
    EXPECT_TRUE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

}
TEST(BoardTest, BoardConstructor_Parameter3) {

    Board b(/*pegs=*/9, /*disks=*/1);
    EXPECT_EQ(9, b.getNumPegs()); //out of range falues.
    EXPECT_EQ(1, b.getNumDisks());
    EXPECT_FALSE(b.getIsBicolor());
    EXPECT_FALSE(b.init());

}


//
// BoardTest_BoardMove
//
TEST(BoardTest, BoardMove_Mono) {

    Board b(/*pegs=*/4, /*disks=*/5);
    EXPECT_EQ(4, b.getNumPegs());
    EXPECT_EQ(5, b.getNumDisks());
    EXPECT_FALSE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

    //printState(b.getRawState());

    // Make some legal moves.
    EXPECT_TRUE(b.move(0, 1));
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(0, 3));

    //printState(b.getRawState());

    // Make a few bad moves.
    EXPECT_FALSE(b.move(0, 3));
    EXPECT_FALSE(b.move(2, 1));
    EXPECT_FALSE(b.move(3, 2));

    // Make some legal moves.
    EXPECT_TRUE(b.move(2, 3));
    EXPECT_TRUE(b.move(1, 3));
    EXPECT_TRUE(b.move(0, 1));
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(1, 2));

    // Try an empty peg move.
    EXPECT_FALSE(b.move(0, 3));

    //printState(b.getRawState());

}
TEST(BoardTest, BoardMove_Bicolor) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_EQ(3, b.getNumPegs());
    EXPECT_EQ(4, b.getNumDisks());
    EXPECT_TRUE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

    printState(b.getRawState());

    // Make some legal moves.
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(1, 2));
    EXPECT_TRUE(b.move(0, 1));
    EXPECT_TRUE(b.move(2, 1));
    EXPECT_TRUE(b.move(2, 1));

    // Make a few bad moves.
    EXPECT_FALSE(b.move(2, 0));
    EXPECT_FALSE(b.move(0, 1));

    printState(b.getRawState());

    // Make some legal moves.
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(1, 2));
    EXPECT_TRUE(b.move(1, 2));
    EXPECT_TRUE(b.move(1, 0));

    printState(b.getRawState());

}


//
// BoardTest_BoardGetHashableState
//
TEST(BoardTest, BoardGetHashableState_Mono) {



}
TEST(BoardTest, BoardGetHashableState_Bicolor) {



}