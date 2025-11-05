CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: myprogram

myprogram: main.o
	$(CXX) $(CXXFLAGS) main.o -o myprogram

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o myprogram
