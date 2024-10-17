prog: mass.o main.o malloc.o
	wg++ mass.o main.o malloc.o -o prog.exe && del malloc.o main.o mass.o && prog.exe
mass.o: mass.cpp
	wg++ -c mass.cpp
main.o: main.cpp
	wg++ -c main.cpp
malloc.o: malloc.cpp
	wg++ -c malloc.cpp