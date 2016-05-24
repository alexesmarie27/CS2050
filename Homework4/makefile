hw4: calculator.o stack.o frontend.o
	gcc calculator.o stack.o frontend.o -o hw4
calculator.o: calculator.c stack.h
	gcc -c calculator.c
stack.o: stack.c stack.h
	gcc -c stack.c
frontend.o: frontend.c calculator.h
	gcc -c frontend.c
