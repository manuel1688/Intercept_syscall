#include <libsyscall_intercept_hook_point.h>
#include <syscall.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/uio.h>

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

	// creat(argv[1], 00777);
	if (syscall_number == SYS_create) {
		*result = syscall_no_intercept(SYS_write, arg0, arg1);
		return 0;
	}
	return 1;
}

static __attribute__((constructor)) void
init(void)
{
	intercept_hook_point = hook;
}