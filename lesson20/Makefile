.PHONY:all
all: mytest myprocess

mytest:mytest.cpp
	g++ -o $@ $^ -std=c++11


myprocess:myprocess.c
	gcc -o $@ $^ -std=c99

.PHONY:clean
clean:
	rm -f myprocess mytest
