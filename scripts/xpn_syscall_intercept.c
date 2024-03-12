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
	(void) arg3;
	(void) arg4;
	(void) arg5;

	// write(fd, text, strlen(text));
	if (syscall_number == SYS_write) {
		char buf_copy[0x1000];
		size_t size = (size_t)arg2;

		if (size > sizeof(buf_copy))
			size = sizeof(buf_copy);

		memcpy(buf_copy, (char *)arg1, size);

		for (size_t i = 0; i < size; ++i) {
			if (buf_copy[i] == 'i')
				buf_copy[i] = 'I';
		}
		*result = syscall_no_intercept(SYS_write, arg0, buf_copy, size);
		return 0;
	} else if (syscall_number == SYS_writev) {
		
		struct iovec *iov = (struct iovec *)arg1;
		size_t iovcnt = (int)arg2;

		for (size_t i = 0; i < iovcnt; ++i) {
			char buf_copy[0x1000];
			size_t size = iov[i].iov_len;

			if (size > sizeof(buf_copy))
				size = sizeof(buf_copy);

			memcpy(buf_copy, iov[i].iov_base, size);

			for (size_t j = 0; j < size; ++j) {
				if (buf_copy[j] == 'l')
					buf_copy[j] = 'L';
			}

			iov[i].iov_base = buf_copy;
		} 

		*result = syscall_no_intercept(SYS_writev, arg0, iov, iovcnt);
		return 0;
	}
	
	return 1;
}

static __attribute__((constructor)) void
init(void)
{
	// Set up the callback function
	intercept_hook_point = hook;
}