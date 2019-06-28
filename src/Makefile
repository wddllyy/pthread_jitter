cc=gcc
cflags=-fPIC -c
objects = list.o thread.o tid.o timer.o switch.o

lib: $(objects)
	$(cc) -fPIC -shared -lrt -o libpthreadj.so $(objects)

list.o: list.c
	$(cc) $(cflags) list.c

thread.o: thread.c
	$(cc) $(cflags) thread.c

tid.o: tid.c
	$(cc) $(cflags) tid.c

timer.o: timer.c
	$(cc) $(cflags) timer.c

switch.o: switch.S switch.c

clean:
	rm -f $(objects) libpthreadj.so
