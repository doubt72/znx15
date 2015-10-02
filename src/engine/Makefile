all: run_check

run_check: build_check
	./znx_check

build_check: znx_check.o znx_register.o
	g++ znx_check.o znx_register.o -o znx_check

znx_check.o: znx_check.cc
	g++ -c znx_check.cc

znx_register.o: znx_register.cc znx_register.h
	g++ -c znx_register.cc

clean:
	rm *.o znx_check
