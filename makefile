all1: clean clear compile run1
all2: clean clear compile run2
all3: clean clear compile run3

clean:
	rm -f *.gch a.out
compile: clean
	g++ *.cpp *.h -std=c++14 -Wall -pthread
clear:
	clear
run1:
	./a.out 12345
run2:
	./a.out 12346
run3:
	./a.out 12347
valgrind: clean clear compile
	valgrind --leak-check=full ./a.out 12345
