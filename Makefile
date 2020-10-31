.PHONY: all
all: format build run

.PHONY: format
format:
	find src/ -name '*.cpp' | xargs clang-format-10 -i -style=file
	find include/ -name '*.h' | xargs clang-format-10 -i -style=file

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: run
run:
	cd build && ./catch_game
