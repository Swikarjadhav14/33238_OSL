#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
 
int main(int argc, char *argv[]) { 
    printf("exec executed\n"); 
    printf("The PID of this process is: %d\n", getpid()); 
 
    if (argc > 1) { 
        printf("Arguments received in reverse order: "); 
        for (int i = argc - 1; i > 0; --i) { 
            printf("%s ", argv[i]); 
        } 
        printf("\n"); 
    } else { 
        printf("No arguments received.\n"); 
    } 
 
    return 0; 
} 
 
// Output 
// swikar@LAPTOP-3VLQDHIH:~$ g++ hello.c -o hello 
// swikar@LAPTOP-3VLQDHIH:~$ ./hello 
// exec executed 
// The PID of this process is: 2207 
// No arguments received. 
 
// swikar@LAPTOP-3VLQDHIH:~$ g++ a2b.c 
// swikar@LAPTOP-3VLQDHIH:~$ ./a.out 
// Fork initialising 
// Enter number of integers to sort: 5 
// Enter the integers: 
// 2 1 4 5 7 
// Array sorted: 1 2 4 5 7 
// Inside child process 
// exec executed 
// The PID of this process is: 2336 
// Arguments received in reverse order: 7 5 4 2 1 
// Inside parent process