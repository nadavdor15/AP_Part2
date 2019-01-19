all1: clean compile run1
all2: clean compile run2
all3: clean compile run3

clean1: 
	rm -f *.gch
clean: clean1 clear
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
