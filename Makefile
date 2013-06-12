all: handle_input.o main.o compile

compile:
	gcc main.o handle_input.o -o t2-engseg
main.o:
	gcc -c main.c

handle_input.o:
	gcc -c handle_input.c
clean:
	find -name '*~' | xargs rm -rf {}
	find -name '*.o' | xargs rm -rf {}

targz:
	tar cvzf t2-engseg.tar.gz *.c *.h Makefile
