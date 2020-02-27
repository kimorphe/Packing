all: heap grain
heap: heap.o
	g++ -o heap heap.o
heap.o: heap.cpp 
	g++ -c heap.cpp

grain: grain.o
	g++ -o grain grain.o
grain.o: grain.cpp
	g++ -c grain.cpp

