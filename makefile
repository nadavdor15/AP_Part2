all: removeTrash clear compile run

removeTrash:
	rm -f *.gch a.out
compile:
	g++ *.cpp *.h -std=c++14 -Wall -pthread
clear:
	clear
run:
	./a.out

