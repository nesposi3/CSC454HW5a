CC=g++
FLAG=-c

all:	main.o VendingMachine.o TimePair.o
	$(CC) main.o VendingMachine.o TimePair.o -o out
main.o:
	$(CC) $(FLAG) main.cpp
VendingMachine.o:
	$(CC) $(FLAG) VendingMachine.cpp VendingMachine.h
TimePair.o:
	$(CC) $(FLAG) TimePair.cpp TimePair.h
clean:
	rm *.o out *.gch	
	
