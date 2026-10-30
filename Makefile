CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2

.PHONY: test clean

test: build/test_classifier
	./build/test_classifier

build/test_classifier: tests/test_classifier.c src/dt_classifier.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ tests/test_classifier.c

clean:
	rm -rf build
