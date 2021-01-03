all:main.o
	g++ main.o -o app.exe
main.o:main.cpp formatting.h mesh.h
	g++ -c -O3 -Wall main.cpp
	
debug:main.cpp formatting.h mesh.h
	g++ -g -O3 main.cpp -o a.out

profiling:main.cpp formatting.h mesh.h
	g++ -gdwarf-3 -ggdb -g -pg -O0 main.cpp -o a.exe

clean:
	del *.o
