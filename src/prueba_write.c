#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // El file descriptor es un entero que identifica un archivo 
    //abierto dentro de un proceso que esta corriendo en el sistema operativo
    int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    const char* text = "iiiiiii";
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}
//gcc prueba_write.c -o prueba_write



