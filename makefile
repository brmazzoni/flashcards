CC=g++
#CC=x86_64-w64-mingw32-g++
#CFLAGS=-static-libstdc++ 

flashcards: main.o practice.o settings.o utils.o statistics.o
	$(CC) main.o practice.o settings.o statistics.o utils.o -o flashcards 

main.o: main.cpp
	$(CC) -c -std=c++11 main.cpp

practice.o: practice.cpp
	$(CC) -c -std=c++11 practice.cpp

settings.o: settings.cpp
	$(CC) -c -std=c++11 settings.cpp

statistics.o: statistics.cpp
	$(CC) -c -std=c++11 statistics.cpp

utils.o: utils.cpp
	$(CC) -c -std=c++11 utils.cpp

tests: tests.cpp
	$(CC) -std=c++11 tests.cpp -o tests
	./tests

clean:
	rm *.o flashcards tests
	