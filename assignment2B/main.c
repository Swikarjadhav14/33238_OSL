#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
 
 
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
 
int main(){ 
    printf("Fork initialising\n"); 
    int n; 
     
    printf("Enter number of integers to sort: "); 
    scanf("%d", &n); 
 
    int arr[n]; 
    printf("Enter the integers:\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &arr[i]); 
    } 
     
    heapSort(arr, n); 
    printf("Array sorted: "); 
    for (int i = 0; i < n; i++) { 
        printf("%d ", arr[i]); 
    } 
    printf("\n"); 
     
    pid_t pid = fork(); 
     
    if (pid < 0) { 
        printf("Error occurred\n"); 
    } else if (pid == 0) { 
        printf("Inside child process\n"); 
 
        char *argv[n + 2];  
        argv[0] = (char *)"./hello"; 
 
        // Convert integers to strings 
        for (int i = 0; i < n; i++) { 
            argv[i + 1] = (char *)malloc(20 * sizeof(char)); // allocate 
memory for each argument 
            snprintf(argv[i + 1], 20, "%d", arr[i]); 
        } 
        argv[n + 1] = NULL; 
        execv(argv[0], argv); 
    } else { 
        sleep(10); 
        printf("Inside parent process\n"); 
    } 
    return 0; 
}