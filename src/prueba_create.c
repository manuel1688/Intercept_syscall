#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
   
    int fd = open("example.txt", O_CREAT, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    close(fd);
    return 0;
    
}
//gcc prueba_create.c -o prueba_write



