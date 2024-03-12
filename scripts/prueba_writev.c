#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>

int main() {
    int fd = open("output_writev.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    const char* text1 = "Hello";
    const char* text2 = "world";
    
    struct iovec iov[2];
    iov[0].iov_base = (void*)text1;
    iov[0].iov_len = strlen(text1);
    iov[1].iov_base = (void*)text2;
    iov[1].iov_len = strlen(text2);

    ssize_t bytes_written = writev(fd, iov, 2);
    if (bytes_written == -1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

//gcc prueba_writev.c -o prueba_writev



