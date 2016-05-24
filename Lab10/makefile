lab10: frontend.o parser.o
	gcc frontend.o parser.o -o lab10
parser.o: parser.c parser.h
	gcc -c parser.c
frontend.o: frontend.c parser.c
	gcc -c frontend.c
