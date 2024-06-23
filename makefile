CC = g++

run: build
	./main.exe

build: main.cpp
	$(CC) main.cpp -o main.exe

clean:
	rm main.exe
