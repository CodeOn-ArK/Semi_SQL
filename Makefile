CXXFLAGS=-Wall -Wextra -pedantic -std=c++11

all: SemiSQL.o
	$(CXX) SemiSQL.o -o SemiSQL

SemiSQL.o: SemiSQL.cpp
	$(CXX) $(CXXFLAGS) -c SemiSQL.cpp
