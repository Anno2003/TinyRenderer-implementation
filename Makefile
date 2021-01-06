all:main.o
	g++ main.o -o app.exe
main.o:main.cpp 
	g++ -c -O3 -Wall main.cpp
	
debug:main.cpp 
	g++ -g -O3 main.cpp -o a.out

profiling:main.cpp 
	g++ -gdwarf-3 -ggdb -g -pg -O0 main.cpp -o a.exe

clean:
	del *.o
