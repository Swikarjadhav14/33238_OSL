#include <stdio.h> 
void fcfs(int arr[][5], int n) { 
    int i, j, temp; 
    int current_time = 0; 
    int total_wt = 0, total_tat = 0; 
    float avg_wt, avg_tat; 
 
    // Bubble sort based on Arrival Time 
    for(i = 0; i < n-1; i++) { 
        for(j = 0; j < n-i-1; j++) { 
            if (arr[j][0] > arr[j+1][0]) { 
                // Swap Arrival Time 
                temp = arr[j][0]; 
                arr[j][0] = arr[j+1][0]; 
                arr[j+1][0] = temp; 
 
                // Swap Burst Time 
                temp = arr[j][1]; 
                arr[j][1] = arr[j+1][1]; 
                arr[j+1][1] = temp; 
                 
                //Swap process number 
                temp = arr[j][4]; 
                arr[j][4] = arr[j+1][4]; 
                arr[j+1][4] = temp; 
            } 
        } 
    } 
 
    // Calculate Turnaround Time and Waiting Time 
    for(i = 0; i < n; i++) { 
        if(current_time < arr[i][0]) { 
            current_time = arr[i][0];  
        } 
 
        current_time += arr[i][1];  
 
        // TAT=CT-AT 
        arr[i][2] = current_time - arr[i][0]; 
 
        // WT=TAT-BT 
        arr[i][3] = arr[i][2] - arr[i][1]; 
 
        total_wt += arr[i][3];  
        total_tat += arr[i][2];  
    } 
 
    avg_wt = (float)total_wt / n;  
    avg_tat = (float)total_tat / n;  
 
    // Print results 
    printf("\nProcess\t Arrival Time \tBurst Time \tTurnaround Time 
\tWaiting Time\n"); 
    for(i = 0; i < n; i++) { 
        printf("%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t\n", arr[i][4], 
arr[i][0], arr[i][1], arr[i][2], arr[i][3]); 
    } 
 
    printf("\nAverage Waiting Time = %f", avg_wt); 
    printf("\nAverage Turnaround Time = %f", avg_tat); 
    printf("\n"); 
} 
     
 
 
int main() { 
    int n, i; 
     
 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
 
    
    int arr[n][5];  
    int arr1[n+1];// used for gannt chart 
     
 
    
    printf("\nEnter Arrival Time and Burst Time:\n"); 
    for(i = 0; i < n; i++) { 
        printf("Process %d:\n", i + 1); 
        arr[i][4]=i+1;  //process number array initialisation 
        printf("Arrival Time: "); 
        scanf("%d", &arr[i][0]); 
        printf("Burst Time: "); 
        scanf("%d",&arr[i][1]); 
    } 
 
    fcfs(arr, n); 
    int sum=0; 
    for(int i=0; i<=n; i++){ 
        if(i==0){ 
           arr1[i]=0;  
           sum+=arr[i][1]; 
        } 
        else{ 
             
      arr1[i]=sum; 
      sum+=arr[i][1]; 
        } 
      
  
    } 
     
    for(int i=0; i<n; i++){ 
     if(i==0){ 
      printf("| P%d |",arr[i][4]); 
     } 
     else{ 
  printf(" P%d |",arr[i][4]); 
 } 
      
      
    } 
    printf("\n"); 
     
    for(int i=0; i<=n; i++){ 
         
        if(i==0){ 
            printf("%d    ", arr1[i]); 
        } 
     else{ 
        printf("%d    ",arr1[i]); 
    
     } 
   
  
      
      
    } 
    printf("\n"); 
 
    return 0; 
} 
 
 
     
// OUTPUT: 
// Enter number of processes: 5 
 
// Enter Arrival Time and Burst Time: 
// Process 1: 
// Arrival Time: 2 
// Burst Time: 6 
// Process 2: 
// Arrival Time: 5 
// Burst Time: 2 
// Process 3: 
// Arrival Time: 1 
// Burst Time: 8 
// Process 4: 
// Arrival Time: 0 
// Burst Time: 3 
// Process 5: 
// Arrival Time: 4 
// Burst Time: 4 
// Process  
// 4   
// 3   
// 1   
// 5   
// 2   
// Arrival Time  
// 0   
// 1   
// 2   
// 4   
// 5   
// 3   
// 8   
// 6   
// 4   
// 2   
// Burst Time  Turnaround Time  Waiting Time 
// 3    
// 0    
// 10    
// 15    
// 17    
// 18    
// Average Waiting Time = 8.000000 
// Average Turnaround Time = 12.600000 
// | P4 | P3 | P1 | P5 | P2 | 
// 0    
// 3    
// 11   17   21   23  