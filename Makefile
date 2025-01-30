.PHONY: all clean

build:
	mkdir -p build && cd build && cmake .. && make

run:
	mkdir -p build && cd build && cmake .. && make && ./main

clean:
	rm -rf build
