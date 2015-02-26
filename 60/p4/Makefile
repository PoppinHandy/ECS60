family.out : familyRunner.o QuadraticProbing.o PersonQueue.o familytree.o  
	g++ -ansi -Wall -g -o family.out familyRunner.o QuadraticProbing.o PersonQueue.o familytree.o  

familyRunner.o : familyRunner.cpp familyRunner.h CPUTimer.h familytree.h 
	g++ -ansi -Wall -g -c familyRunner.cpp

familytree.o : familytree.cpp familytree.h 
	g++ -ansi -Wall -g -c familytree.cpp 

QuadraticProbing.o: QuadraticProbing.cpp QuadraticProbing.h
	g++ -ansi -Wall -g -c QuadraticProbing.cpp

PersonQueue.o: PersonQueue.cpp PersonQueue.h
	g++ -ansi -Wall -g -c PersonQueue.cpp
	
clean : 
	rm -f family.out PersonQueue.o familyRunner.o QuadraticProbing.o familytree.o   
