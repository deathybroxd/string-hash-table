CXX = g++
CXXFLAGS = -Wall -g

hash-table: main.cpp HashTable.h 
	$(CXX) $(CXXFLAGS) main.cpp HashTable.h -o hash-table

HashTable.o: HashTable.h
	$(CXX) $(CXXFLAGS) -c HashTable.h

run:
	./hash-table

val:
	valgrind ./hash-table