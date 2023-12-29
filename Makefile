all: build
	g++ src/server.cpp src/http_tcpServer.cpp -o build/main

run: build
	g++ src/server.cpp src/http_tcpServer.cpp -o build/main
	./build/main

clean: build
	rm -rf build/

build:
	mkdir build/