cc=gcc
cflags=-fPIC -c
objects = list.o thread.o tid.o timer.o switch.o

lib: $(objects)
	$(cc) -fPIC -shared -lrt -g -o libpthreadj.so $(objects)
	cp ./libpthreadj.so ../tests/libpthreadj.so

list.o: list.c
	$(cc) $(cflags) list.c

thread.o: thread.c
	$(cc) $(cflags) thread.c

tid.o: tid.c
	$(cc) $(cflags) tid.c

timer.o: timer.c
	$(cc) $(cflags) timer.c

switch.o: switch.S 
	$(cc) $(cflags) switch.S

clean:
	rm -f $(objects) libpthreadj.so
