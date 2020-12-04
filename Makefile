CC=gcc

.PHONY: clean run

run: clean myprog.out
	./myprog.out

myprog.out: myprog.c libb.so libasm.so
	$(CC) -g -ldl myprog.c -o ${@}

%.o: %.c
	$(CC) -g -c ${^} -o ${@}

libb.so: libb.c
	$(CC) -g -shared -fPIC -Wl,-soname,${@} -o ${@} ${^}

libasm.so: libasm.o foo.o
	$(CC) -g -shared -fPIC -Wl,-soname,${@} -o ${@} ${^}


foo.o: foo.asm
	nasm -f elf64 ${^} -o ${@}

clean: 
	rm -f *.o *.so *.out

look: libb.so libasm.so myprog.out
	ldd myprog.out
	objdump -t libasm.so | grep -e "wrapper" -e "foo"
	objdump -t libb.so |  grep -e "wrapper" -e "foo"

