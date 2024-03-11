#include <libsyscall_intercept_hook_point.h>
#include <syscall.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/uio.h> 

#include "xpn_syscall_intercept_create.h"

static int xpn_adaptor_initCalled = 0;
static int xpn_adaptor_initCalled_getenv = 0; 

char *xpn_adaptor_partition_prefix = "/tmp/expand/"; // Original --> xpn:// 
int   xpn_prefix_change_verified = 0;

int is_xpn_prefix   ( const char * path ) // valida si el path contiene el prefijo de XPN 
{
  if (0 == xpn_prefix_change_verified)
  {
    xpn_prefix_change_verified = 1;

    char * env_prefix = getenv("XPN_MOUNT_POINT");
    if (env_prefix != NULL)
    {
      xpn_adaptor_partition_prefix = env_prefix;
    }
  }
  
  const char *prefix = (const char *)xpn_adaptor_partition_prefix;

  return ( !strncmp(prefix, path, strlen(prefix)) && strlen(path) > strlen(prefix) );
}

const char * skip_xpn_prefix ( const char * path ) // esta funcion se encarga de saltar el prefijo de XPN con el fin de obtener el path real para el sistema de archivos que se esta utilizando
{
  return (const char *)(path + strlen(xpn_adaptor_partition_prefix));
}

static int
hook(long syscall_number,
			long arg0, long arg1,
			long arg2, long arg3,
			long arg4, long arg5,
			long *result)
{
	(void) arg2;
	(void) arg3;
	(void) arg4;
	(void) arg5;

	// fd1 = creat(argv[1], 00777);
	// /tmp/expand/P1/demo.txt  1
	// cuando llama la localidad, el path cambia por lo tanto entraria en syscall_no_intercept
	if (syscall_number == SYS_creat) {
		/*
		creat recibe 2 argumentos, el primer argumento es el path y el segundo es el modo
		los valores de modo puede ser: 00777, 00700, 00666, 00600
		00777: todos los permisos
		arg0 ES EL PATH 
		*/
		char *path = (char *)arg0;
		mode_t mode = (mode_t)arg1; 
		int fd,ret;
		debug_info("[bypass] >> Before creat....\n");
		// This if checks if variable path passed as argument starts with the expand prefix.
		if (is_xpn_prefix(path))
		{
			// We must initialize expand if it has not been initialized yet.
			xpn_adaptor_keepInit ();
			// It is an XPN partition, so we redirect the syscall to expand syscall
			debug_info("[bypass]\t try to creat %s", skip_xpn_prefix(path));

			fd  = xpn_creat((const char *)skip_xpn_prefix(path),mode);
			ret = add_xpn_file_to_fdstable(fd);
			debug_info("[bypass]\t creat %s -> %d", skip_xpn_prefix(path), ret);
		}
		// Not an XPN partition. We must link with the standard library
		else
		{
			// debug_info("[bypass]\t try to dlsym_creat %s\n", path);
			// ret = dlsym_creat(path, mode);
			// debug_info("[bypass]\t dlsym_creat %s -> %d\n", path, ret);
			*result = syscall_no_intercept(SYS_creat, arg0, arg1);
			return 0;
		}

		debug_info("[bypass] << After creat....\n");
		return ret;
	} 
	
	return 1;
}

static __attribute__((constructor)) void
init(void)
{
	// Set up the callback function
	intercept_hook_point = hook;
}


