#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <libgen.h>
#include <string.h>

#define MAX_SIZE 0xffff
#define log(...) fprintf(stderr, __VA_ARGS__);

typedef char bool;

void* allocate();

int main(int argc, char *argv[])
{
    unsigned char c = 0;
    unsigned short int size = 0;
    bool warn = 0;
    FILE *fd;

    if(argc < 2)
    {
        fd = stdin;
    }
    else
    {
        fd = fopen(argv[1], "r");
        if(fd == NULL)
        {
            log("[-] Error: cannot open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    char *addr;
    if( (addr = (char*) allocate()) == NULL )
    {
        return EXIT_FAILURE;
    }

    while(1){
        if(size >= MAX_SIZE)
        {
            log("[-] Error: max size is %d\n", MAX_SIZE);
            return EXIT_FAILURE;
        }
        c = fgetc(fd);
        if(feof(fd))
            break;
        warn |= !c;
        addr[size++] = c;
    }

    fclose(fd);

    if(size == 0){
        log("[-] Error: empty file\n");
        return EXIT_FAILURE;
    }

    log("[+] Size: %d bytes\n", size);
    
    if(warn)
        log("[!] Warning: detected null bytes !\n");

    log("[+] Executing...\n");
    (*(void(*)()) addr)();
    log("[+] Executed!\n");

    return EXIT_SUCCESS;    
}

void* allocate()
{
    void* addr = mmap(NULL, (size_t) MAX_SIZE, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(addr == MAP_FAILED)
    {
        log("[-] Error: mmap\n");
        return NULL;
    }
    return addr;
}
