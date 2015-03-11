p5.out: ProjectRunner.o scheduler.o Queue.o
	g++ -Wall -ansi -g -o p5.out ProjectRunner.o scheduler.o Queue.o


ProjectRunner.o: ProjectRunner.cpp ProjectRunner.h scheduler.h CPUTimer.h 
	g++ -Wall -ansi -g -c ProjectRunner.cpp

scheduler.o: scheduler.cpp scheduler.h 
	g++ -Wall -ansi -g -c scheduler.cpp

Queue.o: Queue.cpp Queue.h
	g++ -Wall -ansi -g -c Queue.cpp
clean:
	rm -f p5.out ProjectRunner.o scheduler.o Queue.o
