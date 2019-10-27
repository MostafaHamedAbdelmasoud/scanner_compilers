all: 
	g++ scanner.cpp -o output.exe -w
	./output.exe
clean:
	rm -rf *o output.exe output.exe