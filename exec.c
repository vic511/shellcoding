#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <libgen.h>

int main(int argc, char *argv[]){

    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_SUCCESS;
    }

    FILE* fd = fopen(argv[1], "r");
    if(fd == NULL)
    {
        fprintf(stderr, "Error: unable to open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    long size;
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    fprintf(stderr, "[+] %s - %ld bytes\n", basename(argv[1]), size);

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

    fprintf(stderr, "[+] Executing...\n");
    (*(void(*)()) addr)();

    fclose(fd);
    return EXIT_SUCCESS;
}