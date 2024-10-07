#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
 
void swap(int *a, int *b) { 
  int temp = *a; 
  *a = *b; 
  *b = temp; 
} 
 
void heapify(int arr[], int N, int i) { 
  int largest = i; 
  int l = 2 * i + 1; 
  int r = 2 * i + 2; 
  if (l < N && arr[l] > arr[largest]) largest = l; 
 
  if (r < N && arr[r] > arr[largest]) largest = r; 
 
  if (largest != i) { 
    swap(&arr[i], &arr[largest]); 
 
    heapify(arr, N, largest); 
  } 
} 
 
void heapSort(int arr[], int N) { 
  for (int i = N / 2 - 1; i >= 0; i--) heapify(arr, N, i); 
  for (int i = N - 1; i > 0; i--) { 
    swap(&arr[0], &arr[i]); 
    heapify(arr, i, 0); 
  } 
} 
 
void printArray(int arr[], int size) { 
  for (int i = 0; i < size; i++) { 
    printf("%d ", arr[i]); 
  } 
  printf("\n"); 
} 
 
void Zombie() { 
  pid_t pid = fork(); 
 
  if (pid < 0) { 
    perror("fork failed"); 
    exit(1); 
  } else if (pid == 0) { 
    // Child process 
    printf("Child process (PID: %d) running...\n", getpid()); 
    printf("Child process (PPID: %d) running...\n", getppid()); 
    exit(0);  
  } else { 
    // Parent process 
    printf("Demonstrating zombie process.\n"); 
    printf("Parent process (PID: %d) running...\n", getpid()); 
    sleep(10);   
    printf("Parent process (PID: %d) finished sleeping.\n", getpid()); 
  } 
} 
 
void Orphan() { 
  pid_t pid = fork(); 
  if (pid < 0) { 
    perror("fork failed"); 
    exit(1); 
  } else if (pid == 0) { 
    // Child process 
    printf("Child process (PID: %d, PPID: %d) running...\n", getpid(), 
           getppid()); 
    sleep(5);  
    printf("Child process (PID: %d, PPID: %d) finished.\n", getpid(), 
           getppid()); 
    exit(0); 
  } else { 
    printf("Demonstrating orphan process.\n"); 
    printf("Parent process (PID: %d) exiting...\n", getpid()); 
    exit(0);  
  } 
} 
 
void SortByWaitCall(int arr[], int n) { 
  pid_t pid = fork(); 
 
  if (pid < 0) { 
    perror("fork failed"); 
    exit(1); 
  } else if (pid == 0) { 
    // Child process 
    printf("Child process sorting with Heap Sort...\n"); 
    heapSort(arr, n); 
    printf("Child process sorted array: "); 
    printArray(arr, n); 
    printf("Child process (PID: %d) finished.\n", getpid()); 
    exit(0); 
  } else { 
    // Parent process 
    printf("Parent process sorting with Heap Sort...\n"); 
    heapSort(arr, n); 
    printf("Array sorted and wait called\n "); 
 
    // Wait for the child process to finish 
    int status; 
    pid_t child_pid = wait(&status); 
 
    if (child_pid < 0) { 
      perror("wait failed"); 
    } else { 
      printf("Parent process (PID: %d) waited for child process (PID: 
%d)\n", 
             getpid(), child_pid); 
    } 
  } 
} 
 
int main() { 
  int n, i, c; 
  printf("Enter number of integers to sort: "); 
  scanf("%d", &n); 
 
  int arr[n]; 
  printf("Enter the integers:\n"); 
  for (i = 0; i < n; i++) { 
    scanf("%d", &arr[i]); 
  } 
 
  printf("Enter choice: 1. Zombie 2. Orphan 3. Using wait and sort\n"); 
  scanf("%d", &c); 
 
  switch (c) { 
    case 1: 
      Zombie(); 
      break; 
 
    case 2: 
      Orphan(); 
      break; 
 
    case 3: 
      SortByWaitCall(arr, n); 
      break; 
 
    default: 
      printf("Invalid choice\n"); 
      break; 
  } 
 
  return 0; 
} 


// Output 
 
// Enter number of integers to sort: 5 
// Enter the integers: 
// 48 79 12 23 40 
// Enter choice: 1. Zombie 2. Orphan 3. Using wait and sort 
// 1 
// Demonstrating zombie process. 
// Parent process (PID: 1016) running... 
// Child process (PID: 1074) running... 
// Child process (PPID: 1016) running... 
// Parent process (PID: 1016) finished sleeping. 
 
// Enter number of integers to sort: 5 
// Enter the integers: 
// 1 2 5 4 5 
// Enter choice: 1. Zombie 2. Orphan 3. Using wait and sort 
// 2 
// Demonstrating orphan process. 
// Parent process (PID: 1162) exiting... 
// Child process (PID: 1239, PPID: 1162) running... 
// Child process (PID: 1239, PPID: 354) finished. 
 
// Enter number of integers to sort: 5 
// Enter the integers: 
// 4 5 6 7 5 
// Enter choice: 1. Zombie 2. Orphan 3. Using wait and sort 
// 3 
// Parent process sorting with Heap Sort... 
// Array sorted and wait called 
// Child process sorting with Heap Sort... 
// Child process sorted array: 4 5 5 6 7 
// Child process (PID: 1340) finished. 
// Parent process (PID: 1308) waited for child process (PID: 1340) 