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

    //std::cout << "Board hash: " << b.getHashableState() << std::endl;
    //printState(b.getRawState());

    // Make some legal moves.
    EXPECT_TRUE(b.move(0, 1));
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(0, 3));

    //std::cout << "Board hash: " << b.getHashableState() << std::endl;
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

    //std::cout << "Board hash: " << b.getHashableState() << std::endl;
    //printState(b.getRawState());

}
TEST(BoardTest, BoardMove_Bicolor) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_EQ(3, b.getNumPegs());
    EXPECT_EQ(4, b.getNumDisks());
    EXPECT_TRUE(b.getIsBicolor());
    EXPECT_TRUE(b.init());

    std::cout << "Board hash: " << b.getHashableState() << std::endl;
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

    std::cout << "Board hash: " << b.getHashableState() << std::endl;
    printState(b.getRawState());

    // Make some legal moves.
    EXPECT_TRUE(b.move(0, 2));
    EXPECT_TRUE(b.move(1, 2));
    EXPECT_TRUE(b.move(1, 2));
    EXPECT_TRUE(b.move(1, 0));

    std::cout << "Board hash: " << b.getHashableState() << std::endl;
    printState(b.getRawState());

}


//
// BoardTest_BoardGetHashableState
//
TEST(BoardTest, BoardGetHashableState_Mono) {

    Board b(/*pegs=*/4, /*disks=*/3, /*isBicolor=*/false);
    EXPECT_TRUE(b.init());
    
    unsigned long long h = b.getHashableState();
    printState(b.getRawState());

}
TEST(BoardTest, BoardGetHashableState_Bicolor) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_TRUE(b.init());

    unsigned long long h = b.getHashableState();
    printState(b.getRawState());

}


//
// BoardTest_BoardSetFromHashableState
//
TEST(BoardTest, BoardSetFromHashableState_Mono) {



}
TEST(BoardTest, BoardSetFromHashableState_Bicolor) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_TRUE(b.init());

    std::vector<std::size_t> state;
    unsigned long long hash;

    // Board State
    //                  [XX]      [O]
    //        [OO]      [OOO]     [X]
    //        [OOOO]    [XXXX]    [XXX]
    state = { 2,0,2,0,  1,2,1,0,  0,1,0,3 };
    hash  = b.computeHash(state);

    EXPECT_TRUE(b.setFromHashableState(hash));
    EXPECT_EQ(hash, b.getHashableState());

    printState(b.getRawState());


    // Board State
    //                  [XX]      
    //                  [OO]      
    //        [XXX]     [OOO]     [X]
    //        [OOOO]    [XXXX]    [O]
    state = { 2,1,0,0,  1,2,4,0,  0,0,0,4 };
    hash  = b.computeHash(state);

    EXPECT_TRUE(b.setFromHashableState(hash));
    EXPECT_EQ(hash, b.getHashableState());

    printState(b.getRawState());



    // Board State
    //                  [XX]      
    //        [X]       [OO]      
    //        [XXX]     [OOO]     [O]
    //        [OOOO]    [XXXX]    [XXXX]
    state = { 2,1,0,1,  1,2,4,0,  1,0,0,2 };
    hash  = b.computeHash(state);

    EXPECT_FALSE(b.setFromHashableState(hash));
    //EXPECT_EQ(hash, b.getHashableState());

    printState(b.getRawState());

}


//
// BoardTest_GetShowableState
//
TEST(BoardTest, BoardGetShowableState_Mono) {

}
TEST(BoardTest, BoardGetShowableState_Bicolor) {

    Board b(/*pegs=*/3, /*disks=*/4, /*isBicolor=*/true);
    EXPECT_TRUE(b.init());

    std::vector<std::size_t> state;
    unsigned long long hash;

    // Board State
    //                  [XX]      [O]
    //        [OO]      [OOO]     [X]
    //        [OOOO]    [XXXX]    [XXX]
    state = { 2,0,2,0,  1,2,1,0,  0,1,0,3 };
    hash  = b.computeHash(state);

    EXPECT_TRUE(b.setFromHashableState(hash));
    EXPECT_EQ(hash, b.getHashableState());

    std::cout << b.getShowableState() << std::endl << std::endl;

}
