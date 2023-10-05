#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096  // Assume page size is 4096 bytes

typedef struct Chunk {
    int size;
    int is_allocated;
    struct Chunk* next;
} Chunk;

void allocate_chunk(Chunk* head, int requested_size) {
    Chunk* current = head;
    while (current) {
        if (!current->is_allocated && current->size >= requested_size) {
            current->is_allocated = 1;
            printf("Allocated chunk of size %d\n", requested_size);
            return;
        }
        current = current->next;
    }
    printf("Failed to allocate chunk of size %d\n", requested_size);
}
void deallocate_chunk(Chunk* head, int requested_size) {
    Chunk* current = head;
    while (current) {
        if (current->is_allocated && current->size >= requested_size) { //or ==, but with this option it was never able to find it
            current->is_allocated = 0;
            printf("Deallocated chunk of size %d\n", current->size);
            return;
        }
        current = current->next;
    }
    printf("Unable to find allocated chunk of size %d\n", requested_size);
}

int main() {
    int num_chunks = 4;
    int total_size = num_chunks * PAGE_SIZE;

    // Step 1: Open a file or use anonymous mapping
    int fd = -1;  // Anonymous mapping
    // int fd = open("file.txt", O_RDWR);  // Use a file for mapping

    // Step 2: Use mmap to map pages of memory
    void* mapped_memory = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Store the mapped memory pointer
    Chunk* head = (Chunk*)mapped_memory;
    head->size = total_size - sizeof(Chunk);
    head->is_allocated = 0;
    head->next = NULL;

    // Step 4: No need to explicitly initialize chunks for linked list-based approach

    // Step 5: Allocate a chunk
    allocate_chunk(head, 1500);

    // Step 6: Deallocate a chunk
    deallocate_chunk(head, 1500);

    // Step 7: Release the mapped memory
    munmap(mapped_memory, total_size);

    return 0;
}
