//C code to explain functionalities of mmap() and munmap()
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main() {
    // The size of the memory region in bytes
    size_t size = 4096;

    // Allocate a memory region using mmap()
    void* address = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (address == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Access and modify the memory region
    int* data = (int*)address;
    *data = 42;

    // Print the value before unmapping
    printf("Value before unmapping: %d\n", *data);

    // Unmap the memory region using munmap()
    if (munmap(address, size) == -1) {
        perror("munmap");
        exit(1);
    }

    // Accessing the unmapped memory will result in a segmentation fault (SIGSEGV)
    printf("Value after unmapping: %d\n", *data); // This line will not be reached

    return 0;
}

/*Here's what is going on in the code: 

1. We used mmap() to allocate a memory region.
-NULL is passed as the first argument, indicating that the kernel should choose the address for the mapping. 
-The size argument specifies the size of the mapping, PROT_READ | PROT_WRITE sets the memory region to be readable and writable, and MAP_PRIVATE | MAP_ANONYMOUS indicates that the mapping is private and not associated with a file. 
-The fd and offset are set to -1 and 0.
-Then it will check if mmap() was successful by comparing the returned address with MAP_FAILED. If mmap() fails, it returns MAP_FAILED, and an error message is printed using perror(). The program exits with an error status.
2. Then we assigned a value of 42 to the memory location pointed by data and printed the value stored in the memory region before unmapping.
3. We used munmap() to release the memory region and passed the address and size arguments. If munmap() fails, it returns -1, and an error message is printed using perror(). The program exits with an error status.
4.If you attempt to print the value stored in the memory region after it has been unmapped taht won't happen because it will not be possible to reach this  line and it will result in  a segmentation fault (SIGSEGV).
5. And return 0 to indicate successful execution of the program.

*/
