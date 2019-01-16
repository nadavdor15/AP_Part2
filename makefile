all1: clean clear compile run1
all2: clean clear compile run2
all3: clean clear compile run3

clean:
	rm -f *.gch
compile: clean clear
	g++ *.cpp *.h -std=c++14 -Wall -pthread
clear:
	clear
run1:
	./a.out 12345
run2:
	./a.out 12346
run3:
	./a.out 12347
valgrind1:
	valgrind --leak-check=full ./a.out 12345
valgrind2:
	valgrind --leak-check=full ./a.out 12346
valgrind3:
	valgrind --leak-check=full ./a.out 12347
