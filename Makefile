all: clean handle_input.o algorithm1.o main.o compile

compile:
	gcc main.o algorithm1.o handle_input.o -o t2-engseg -g
main.o:
	gcc -c main.c -g

handle_input.o:
	gcc -c handle_input.c -g

algorithm1.o:
	gcc -c algorithm1.c -g
clean:
	@find -name '*~' | xargs rm -rf {}
	@find -name '*.o' | xargs rm -rf {}

targz:
	tar cvzf t2-engseg.tar.gz *.c *.h Makefile
