#---------------------------------------------------
# Makefile for Subset.c
#---------------------------------------------------
Subset : Subset.o
	gcc -o Subset Subset.o
Subset.o : Subset.c
	gcc -c -std=c99 -Wall Subset.c
clean :
	rm -f Subset Subset.o
submit : Subset.c Makefile
	submit cse015-pt.f19 pa1 Subset.c Makefile 
check :
	ls  /afs/cats.ucsc.edu/users/n/sugbhand/cse15/pa1                                 
