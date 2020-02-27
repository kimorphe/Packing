heap: heap.o
	g++ -o heap heap.o
heap.o: heap.cpp 
	g++ -c heap.cpp

