CXX = g++
CXXFLAGS = -Wall -g

string-hash-table: main.cpp StringHashTable.h 
	$(CXX) $(CXXFLAGS) main.cpp StringHashTable.h -o string-hash-table

StringHashTable.o: StringHashTable.h
	$(CXX) $(CXXFLAGS) -c StringHashTable.h

run:
	./string-hash-table

val:
	valgrind ./string-hash-table