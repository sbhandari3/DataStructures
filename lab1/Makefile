#---------------------------------------------------
# Makefile for MyHello.c
# #---------------------------------------------------
MyHello : MyHello.o
	gcc -o MyHello MyHello.o
MyHello.o : MyHello.c
	gcc -c -std=c99 -Wall MyHello.c
clean :
	rm -f MyHello MyHello.o
submit : MyHello.c Makefile
	submit cse015-pt.f19 lab1 MyHello.c Makefile
check :
	ls  /afs/cats.ucsc.edu/users/n/sugbhand/cse15/lab1
