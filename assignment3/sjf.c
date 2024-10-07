#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Structure to hold process information
struct Process
{
    int process_id;      // Process ID
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time
    int waiting_time;    // Waiting time
    int remaining_time;  // Remaining burst time for preemption
    int is_completed;    // Flag to check if process is completed
};

// SJF scheduling (Non-Preemptive)
void sjf_schedule(struct Process processes[], int n)
{
    int current_time = 0; // Current time
    int completed = 0;    // Number of processes completed
    int arr[n];           // To store Order of processes executed
    int i = 0;
    while (completed < n)
    {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;

        // Find the shortest job that has arrived
        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrival_time <= current_time &&
                processes[i].is_completed == 0 &&
                processes[i].burst_time < shortest_burst)
            {
                shortest_index = i;
                shortest_burst = processes[i].burst_time;
            }
        }

        if (shortest_index == -1)
        {
            // If no process is available to execute, move to next moment
            current_time++;
        }
        else
        {
            // Execute the shortest job
            processes[shortest_index].completion_time = current_time +
                                                        processes[shortest_index].burst_time;
            processes[shortest_index].turnaround_time =
                processes[shortest_index].completion_time -
                processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time =
                processes[shortest_index].turnaround_time -
                processes[shortest_index].burst_time;
            processes[shortest_index].is_completed = 1;
            current_time = processes[shortest_index].completion_time;
            arr[i] = shortest_index + 1;
            completed++;
            i++;
        }
    }

    // Calculate total waiting time and turnaround time
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; ++i)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %f\n", total_turnaround_time / n);

    printf("\n");

    printf("Gantt chart: \n\n");
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            printf("| P%d |", arr[i]);
        }
        else
        {
            printf(" P%d |", arr[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            printf("0    %d    ", processes[arr[i] - 1].completion_time);
        }
        else
        {
            printf("%d    ", processes[arr[i] - 1].completion_time);
        }
    }
    printf("\n\n");
}

// SJF scheduling (Preemptive)
void srtf_schedule(struct Process proc[], int n)
{
    int rt[n];
    int arr[1000];        // To store the order of execution
    int gantt_time[1000]; // To store the time at each switch
    int exec_idx = 0;     // Index to track gantt chart entries

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].burst_time;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    // Process until all processes get completed
    while (complete != n)
    {
        // Find process with minimum remaining time among the processes
        that arrive till the current time for (int j = 0; j < n; j++)
        {
            if ((proc[j].arrival_time <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        // Track the process execution in Gantt chart
        arr[exec_idx] = proc[shortest].process_id;
        gantt_time[exec_idx] = t;
        exec_idx++;

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if (rt[shortest] == 0)
        {
            complete++;
            check = 0;

            // Find finish time of current process
            finish_time = t + 1;

            // Calculate waiting time
            proc[shortest].waiting_time = finish_time -
                                          proc[shortest].burst_time - proc[shortest].arrival_time;

            if (proc[shortest].waiting_time < 0)
                proc[shortest].waiting_time = 0;

            // Calculate turnaround time
            proc[shortest].turnaround_time = proc[shortest].burst_time +
                                             proc[shortest].waiting_time;

            // Store the completion time
            proc[shortest].completion_time = finish_time;
        }
        // Increment time
        t++;
    }

    // Calculate total waiting time and turnaround time
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; ++i)
    {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %f\n", total_turnaround_time / n);

    // Print Gantt chart for SRTF
    printf("\nGantt chart: \n\n");
    for (int i = 0; i < exec_idx; i++)
    {
        if (i == 0 || arr[i] != arr[i - 1])
        {
            printf("| P%d ", arr[i]);
        }
    }
    printf("|\n");

    for (int i = 0; i < exec_idx; i++)
    {
        if (i == 0 || arr[i] != arr[i - 1])
        {
            printf("%d   ", gantt_time[i]);
        }
    }
    printf("%d\n\n", t);
}

int main()
{
    int n;
    int choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; ++i)
    {
        processes[i].process_id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i +
                                                                         1);
        scanf("%d %d", &processes[i].arrival_time,
              &processes[i].burst_time);
        processes[i].is_completed = 0;
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time for SRTF
    }

    printf("Choose the scheduling algorithm:\n");
    printf("1. Shortest Job First (Non-Preemptive)\n");
    printf("2. Shortest Remaining Time First (Preemptive)\n");

    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Perform the chosen scheduling algorithm
    if (choice == 1)
    {
        sjf_schedule(processes, n);
    }
    else if (choice == 2)
    {
        srtf_schedule(processes, n);
    }
    else
    {
        printf("Invalid choice!\n");
        return 1;
    }

    // Display process details along with completion time
    printf("Process-ID\tArrival-Time\tBurst-Time\tTurnaround
Time\tWaiting-Time\n"); 
 
    for (int i = 0; i < n; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].turnaround_time,
               processes[i].waiting_time); 
    } 
 
    return 0;
}

// OUTPUT:

// SJF(non-preemptive):

// Enter the number of processes: 5
// Enter arrival time and burst time for process 1: 2 6
// Enter arrival time and burst time for process 2: 5 2
// Enter arrival time and burst time for process 3: 1 8
// Enter arrival time and burst time for process 4: 0 3
// Enter arrival time and burst time for process 5: 4 4

// Choose the scheduling algorithm:
// 1. Shortest Job First (Non-Preemptive)
// 2. Shortest Remaining Time First (Preemptive)
// Enter your choice (1 or 2): 1
// Average Waiting Time: 5.200000
// Average Turnaround Time: 9.800000

// Gannt chart:

// | P4 | P1 | P2 | P5 | P3 |
// 0    3    9    11   15   23

// Process-ID Arrival-Time Burst-Time Turnaround-Time Waiting-Time
// 1  2  6  7  1
// 2  5  2  6  4
// 3  1  8  22  14
// 4  0  3  3  0
// 5  4  4  11  7

// SJF(preemptive):

// Enter the number of processes: 5
// Enter arrival time and burst time for process 1: 2 6
// Enter arrival time and burst time for process 2: 5 2
// Enter arrival time and burst time for process 3: 1 8
// Enter arrival time and burst time for process 4: 0 3
// Enter arrival time and burst time for process 5: 4 4

// Choose the scheduling algorithm:
// 1. Shortest Job First (Non-Preemptive)
// 2. Shortest Remaining Time First (Preemptive)
// Enter your choice (1 or 2): 2

// Average Waiting Time: 4.600000
// Average Turnaround Time: 9.200000

// Gantt chart:

// | P4 | P1 | P5 | P2 | P5 | P1 | P3 |
// 0    3    4    5    7    10   15   23

// Process-ID Arrival-Time Burst-Time Turnaround-Time Waiting-Time
// 1  2  6  13  7
// 2  5  2  2  0
// 3  1  8  22  14
// 4  0  3  3  0
// 5  4  4  6  2