#pragma once

#include <iostream>
#include <assert.h>
#include <stdio.h>

#include <bitset>

class BitSet {

public: 
    BitSet(int i);
    ~BitSet();
    static BitSet* allocBitSet(int i);
    static void freeBitSet(BitSet*);
    static void setBit(BitSet* b, int i);
    static void clearBit(BitSet* b, int i);
    static bool getBit(BitSet* b, int i);
    void readBitSet(char *filename, BitSet* b);
    void writeBitSet(char *filename, BitSet *b);
    int getBytesForBits(int i);
    static void testGetBytesForBits();
    static void testGetCharIndex();
    static void testGetBitShift();
    static void testSetBit();
    static void testClearBit();
    int num_bits_;
    char *bits_;
private:
    int getCharIndex(int i);
    int getBitShift(int i);
    //void setBit(BitSet* b, int i, bool value);
};