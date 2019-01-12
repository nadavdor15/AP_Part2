all: clean clear compile run

clean:
	rm -f *.gch a.out
compile:
	g++ *.cpp *.h -std=c++14 -Wall -pthread
clear:
	clear
run:
	./a.out
valgrind: clean clear compile
	valgrind --leak-check=full ./a.out
