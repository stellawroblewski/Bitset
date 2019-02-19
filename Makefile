CXX=g++
CXXFLAGS=-Wall -g -pedantic -Werror -std=c++11
OPTFLAGS=-O3
LDFLAGS=$(CXXFLAGS) $(OPTFLAGS)

all: bitset

tree.o: bitset.cc bitset.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c bitset.cc -o bitset.o

clean:
	rm -rf *.o bitset
