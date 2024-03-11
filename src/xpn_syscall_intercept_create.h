
/*
 *  Copyright 2020-2024 Felix Garcia Carballeira, Diego Camarmas Alonso, Alejandro Calderon Mateos
 *
 *  This file is part of Expand.
 *
 *  Expand is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Expand is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Expand.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef _XPN_SYS_CALL_INTERCEPT_CREATE_H_
#define _XPN_SYS_CALL_INTERCEPT_CREATE_H_

  /* ... Include / Inclusion ........................................... */

  #define _GNU_SOURCE

  #include "config.h"

  #include <dlfcn.h>
  #include <sys/stat.h>
  #include <stdarg.h>

  #include "xpn.h"
//   #include "syscall_proxies.h"

  #include <dirent.h>
  #include <string.h>
  #include "mpi.h"

  //#include<pthread.h> //Mutex


  /* ... Const / Const ................................................. */

  #ifndef _STAT_VER
  #define _STAT_VER 0
  #endif


  //#define RTLD_NEXT ((void *) -1l)
  #define MAX_FDS   10000
  #define MAX_DIRS  10000
  #define PLUSXPN   1000

  #undef __USE_FILE_OFFSET64
  #undef __USE_LARGEFILE64


  #define FD_FREE 0
  #define FD_SYS  1
  #define FD_XPN  2


  // Types
  #define O_ACCMODE 00000003
  #define O_RDONLY  00000000
  #define O_WRONLY  00000001
  #define O_RDWR    00000002
  #ifndef O_CREAT
  #define O_CREAT   00000100  // not fcntl
  #endif
  #ifndef O_EXCL
  #define O_EXCL    00000200  // not fcntl
  #endif
  #ifndef O_NOCTTY
  #define O_NOCTTY  00000400  // not fcntl
  #endif
  #ifndef O_TRUNC
  #define O_TRUNC   00001000  // not fcntl
  #endif
  #ifndef O_APPEND
  #define O_APPEND  00002000
  #endif
  #ifndef O_NONBLOCK
  #define O_NONBLOCK  00004000
  #endif
  #ifndef O_DSYNC
  #define O_DSYNC   00010000  // used to be O_SYNC, see below
  #endif
  #ifndef FASYNC
  #define FASYNC    00020000  // fcntl, for BSD compatibility
  #endif
  #ifndef O_DIRECT
  #define O_DIRECT  00040000  // direct disk access hint
  #endif
  #ifndef O_LARGEFILE
  #define O_LARGEFILE 00100000
  #endif
  #ifndef O_DIRECTORY
  #define O_DIRECTORY 00200000  // must be a directory
  #endif
  #ifndef O_NOFOLLOW
  #define O_NOFOLLOW  00400000  // don't follow links
  #endif
  #ifndef O_NOATIME
  #define O_NOATIME 01000000
  #endif
  #ifndef O_CLOEXEC
  #define O_CLOEXEC 02000000  // set close_on_exec */
  #endif


  /* ... Data structures / Estructuras de datos ........................ */

  struct __dirstream
  {
    int fd;                       // File descriptor.
    //__libc_lock_define (, lock) // Mutex lock for this structure. //TODO
    size_t allocation;            // Space allocated for the block.
    size_t size;                  // Total valid data in the block.
    size_t offset;                // Current offset into the block.
    off_t  filepos;               // Position of next entry to read.
    // Directory block.
    char data[0] __attribute__ ((aligned (__alignof__ (void*))));

    char * path;
  };

  struct generic_fd
  {
    int type;
    int real_fd;
    int is_file;
  };


  /* ... Functions / Funciones ......................................... */

  // File API


#endif
