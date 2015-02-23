family.out : familyRunner.o QuadraticProbing.o familytree.o  
	g++ -ansi -Wall -g -o family.out familyRunner.o QuadraticProbing.o familytree.o  

familyRunner.o : familyRunner.cpp familyRunner.h CPUTimer.h familytree.h 
	g++ -ansi -Wall -g -c familyRunner.cpp

familytree.o : familytree.cpp familytree.h 
	g++ -ansi -Wall -g -c familytree.cpp 

QuadraticProbing.o: QuadraticProbing.cpp QuadraticProbing.h
	g++ -ansi -Wall -g -c QuadraticProbing.cpp
clean : 
	rm -f family.out familyRunner.o QuadraticProbing.o familytree.o   
