#
# This Makefile is for expand bypass (syscalls interceptions) library
#

# esta linea define prefix como el directorio donde se va a instalar la libreria
prefix = /home/lab/bin/xpn
# esta linea es para definir CC como el compilador que se va a usar
CC=/home/lab/bin/mpich/bin/mpicc

# esta linea es para definir FLAGS como las banderas que se van a usar
#-I../../../mxml
#-L../../src/xpn_client -L../../../mxml
FLAGS=-Wall -Wextra -fpic -std=c11
INCLUDE=-I../../include -I../../include/base -I../../include/xpn_client -I../../include/bypass -DNOT_TO_USE_FCNTL_H -DNOT_TO_USE_STDLIB_H
LIBS=-L../../../xpn/src/xpn_client -lxpn -lmxml -lpthread -ldl

all:
	$(CC) $(FLAGS) $(INCLUDE) -c xpn_syscall_intercept_create.c
	$(CC) -shared -o xpn_syscall_intercept_create.so xpn_syscall_intercept_create.o $(LIBS)

install:
	cp -f xpn_syscall_intercept_create.so ${prefix}/lib

clean:
	rm -f *.o
	rm -f *.so