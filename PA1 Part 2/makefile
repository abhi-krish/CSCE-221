all: test

test: Collection.o main.o Stress_ball.o
	g++ -std=c++11 Stress_ball.o Collection.o main.o -o test

Collection.o: Collection.cpp Collection.h
	g++ -std=c++11 -c Collection.cpp

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	c++ -std=c++11 -c Stress_ball.cpp
	
main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm -rf *.o test
