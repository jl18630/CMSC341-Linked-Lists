CXX = g++
CXXFLAGS = -Wall

Driver.out: Driver.o Graph.o
        $(CXX) $(CXXFLAGS) Graph.o Driver.o -o Driver.out

Graph.o: Graph.cpp Graph.h
        $(CXX) $(CXXFLAGS) -c Graph.cpp

Driver.o: Driver.cpp
        $(CXX) $(CXXFLAGS) -c Driver.cpp

clean:
        rm *.o
        rm *~

run:
        ./Driver.out