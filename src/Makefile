#
# This Makefile is for expand bypass (syscalls interceptions) library
#

prefix = /home/lab/bin/xpn
CC=/home/lab/bin/mpich/bin/mpicc

#-I../../../mxml
#-L../../src/xpn_client -L../../../mxml
# cc xpn_syscall_intercept_create.c -lsyscall_intercept -fpic -shared -o xpn_syscall_intercept_create.so
FLAGS=-Wall -Wextra -fpic -std=c11
INCLUDE=-I../../include -I../../include/base -I../../include/xpn_client -I../../include/bypass -I../../../mxml -DNOT_TO_USE_FCNTL_H -DNOT_TO_USE_STDLIB_H
LIBS=-L../../../xpn/src/xpn_client -lxpn -lmxml -lpthread -ldl -lsyscall_intercept -fpic

all:
	$(CC) $(FLAGS) $(INCLUDE) -c xpn_syscall_intercept_create.c
	$(CC) -shared -o xpn_syscall_intercept_create.so xpn_syscall_intercept_create.o $(LIBS)
	
install:
	cp -f xpn_syscall_intercept_create.so ${prefix}/lib

clean:
	rm -f *.o
	rm -f *.so
