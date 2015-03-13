p5.out: ProjectRunner.o scheduler.o VertexQueue.o
	g++ -Wall -ansi -g -o p5.out ProjectRunner.o scheduler.o VertexQueue.o


ProjectRunner.o: ProjectRunner.cpp ProjectRunner.h scheduler.h CPUTimer.h 
	g++ -Wall -ansi -g -c ProjectRunner.cpp

scheduler.o: scheduler.cpp scheduler.h 
	g++ -Wall -ansi -g -c scheduler.cpp

VertexQueue.o: VertexQueue.cpp VertexQueue.h
	g++ -Wall -ansi -g -c VertexQueue.cpp

clean:
	rm -f p5.out ProjectRunner.o scheduler.o VertexQueue.o
