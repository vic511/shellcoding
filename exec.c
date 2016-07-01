#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){

    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_SUCCESS;
    }

    FILE* fd = fopen(argv[1], "r");
    long size;

    if(fd == NULL)
    {
        fprintf(stderr, "Error: unable to open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    void* addr = mmap(NULL, (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if(addr == MAP_FAILED)
    {
        fprintf(stderr, "Error: mmap\n");
        return EXIT_FAILURE;
    }

    int i = 0;

    while(!feof(fd))
    {
        *(char*) (addr + i) = fgetc(fd);
        i++;
    }

    (*(void(*)()) addr)();

    fclose(fd);
    return EXIT_SUCCESS;
}