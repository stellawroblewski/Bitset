#define GET_BYTES_FOR_BITS_DEBUG 0

#include "bitset.hh"
#include "limits.h"
#include <fstream>

BitSet::BitSet(int i) {
    num_bits_ = i;
    bits_ = new char[getBytesForBits(num_bits_)];
} 

int BitSet::getBytesForBits(int i) {
    if (i < 0) {
        abort();
    }
    int mod = num_bits_ % CHAR_BIT;
    int add = 0;
    if (mod == 0 || i == 0 ) {
        add = 1;
    }
    if (GET_BYTES_FOR_BITS_DEBUG) { 
        std::cout << "    getBytesForBits: num_bits_ = " << num_bits_ << "\n";
        std::cout << "    getBytesForBits: CHAR_BIT = " << CHAR_BIT << "\n";
        std::cout << "    getBytesForBits: mod = " << mod << "\n"; 
        std::cout << "    getBytesForBits: add = " << add << "\n"; 
    }
    return (i / CHAR_BIT) + add;
}

BitSet::~BitSet(){
    delete this;
}

BitSet* BitSet::allocBitSet(int i){
    return new BitSet(i);
}

void BitSet::freeBitSet(BitSet* b){
    delete b;
}

void BitSet::setBit(BitSet* b, int i) {
    // what char index are we on?
    int charIndex = b->getCharIndex(i);
    // what bit for that index
    int bitShift = b->getBitShift(i);
    b->bits_[charIndex] |= ( 1 << bitShift );
}

bool BitSet::getBit(BitSet* b, int i) {
    // what char index are we on?
    int charIndex = b->getCharIndex(i);
    // what bit for that index
    int bitShift = b->getBitShift(i);
    return ( b->bits_[charIndex] >> bitShift ) & 1;
}

void BitSet::clearBit(BitSet* b, int i) {
    // what char index are we on?
    int charIndex = b->getCharIndex(i);
    // what bit for that index
    int bitShift = b->getBitShift(i);

    // 1011 1000 OR
    // 0100 0000
    // 1011 1000
    b->bits_[charIndex] &= ~( 1 << bitShift );
}

int BitSet::getCharIndex(int i) {
    if (i < 0) {
        abort();
    }
    if (i >= num_bits_) {
        abort();
    }
    return getBytesForBits(i) - 1;
}

/*
15 14 13 12 
0  0  0  0  0000 0000 0000

1  0  0  0  0000
*/
int BitSet::getBitShift(int i) {
    if (i < 0) {
        abort();
    }
    if (i >= num_bits_ ) {
        abort();
    }
    return (i - getCharIndex(i)*CHAR_BIT);
}


/*void BitSet::readBitSet(char *filename, BitSet* b) {
    std::ifstream inMyStream(filename);
    std::string line;
    int c = 0;
    if (inMyStream.is_open()){
        while(getline(inMyStream,line)){
            c += line.length();
        }
    }
    inMyStream.close();
    b = allocBitSet(c);
    std::ifstream infile;
    int n = 0;
    char letter[0];
    infile.open(filename);
    while (infile.peek() != EOF){
        infile >> letter;
        if (letter* == 0){
            setBit(b, n);
        }
        n++;
    }
    infile.close();
}*/



void BitSet::writeBitSet(char *filename, BitSet *b) {
    std::ofstream outputFile;
    outputFile.open(filename);
    int x = 0;
    while (x <= b->num_bits_){
        bool bit = getBit(b, x);
        std::cout << bit << std::endl;
        x++;
    }
    outputFile.close();
}


int main() { 
    //BitSet::testGetBytesForBits();
    //BitSet::testGetCharIndex();
    //BitSet::testGetBitShift();
    //BitSet::testSetBit();
    //BitSet::testClearBit();
    return 0; 
}

//TEST FUNCTIONS BELOW








void BitSet::testSetBit() {
    int num_bits = 16;
    for (int i = 0; i <= num_bits; i++){
        BitSet *b = new BitSet(num_bits);
        std::cout << "get   " ;
        for (int i = num_bits - 1; i >= 0; i--){
            std::cout << BitSet::getBit(b, i) ;
        }
        std::cout << "\n" ;        std::cout << "setBit " << i << "\n" ;
        BitSet::setBit(b, i);
        std::cout << "get   " ;
        for (int i = num_bits - 1; i >= 0; i--){
            std::cout << BitSet::getBit(b, i) ;
        }
        std::cout << "\n\n" ;
    }

}
void BitSet::testClearBit() {
    int num_bits = 16;
    for (int i = 0; i <= num_bits; i++){
        BitSet *b = new BitSet(num_bits);
        for (int i = num_bits - 1; i >= 0; i--){
            BitSet::setBit(b, i);
        }
        std::cout << "get   " ;
        for (int i = num_bits - 1; i >= 0; i--){
            std::cout << BitSet::getBit(b, i) ;
        }
        std::cout << "\n" ;        std::cout << "clearBit " << i << "\n" ;
        BitSet::clearBit(b, i);
        std::cout << "get   " ;
        for (int i = num_bits - 1; i >= 0; i--){
            std::cout << BitSet::getBit(b, i) ;
        }
        std::cout << "\n\n" ;
    }

}


void BitSet::testGetBytesForBits() {
    int num_bits = 16;
    BitSet *b = new BitSet(num_bits);
    for (int i = 0; i <= num_bits; i++){
        std::cout << "getBytesForBits " << i << ": " << b->getBytesForBits(i) << "\n";
    }
}

void BitSet::testGetCharIndex() {
    int num_bits = 16;
    BitSet *b = new BitSet(num_bits);
    for (int i = 0; i <= num_bits; i++){
        std::cout << "getCharIndex " << i << ": " << b->getCharIndex(i) << "\n";
    }
}

void BitSet::testGetBitShift() {
    int num_bits = 16;
    BitSet *b = new BitSet(num_bits);
    for (int i = 0; i <= num_bits; i++){
        std::cout << "getBitShift " << i << ": " << b->getBitShift(i) << "\n";
    }
}