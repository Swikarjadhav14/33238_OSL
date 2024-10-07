 
RoundRobin: 
CODE: 
#include <stdio.h> 
#include <stdlib.h> 
struct Process 
{ 
 int pid; 
 int at; 
 int bt; 
 int rt; 
 int wt; 
 int tat; 
}; 
struct Node 
{ 
 struct Process *data; 
struct Node *next; 
}; 
struct Queue 
{ 
struct Node *front; 
struct Node *rear; 
int size; 
}; 
struct Process* create_process(int pid, int at, int bt) 
{ 
struct Process *p = (struct Process*)malloc(sizeof(struct 
Process)); 
p->pid = pid; 
p->at = at; 
p->bt = bt; 
p->rt = bt; 
p->wt = 0; 
p->tat = 0; 
return p; 
} 
struct Node* create_node(struct Process *p) 
{ 
struct Node *node = (struct Node*)malloc(sizeof(struct Node)); 
node->data = p; 
node->next = NULL; 
return node; 
} 
void init_queue(struct Queue *q) 
{ 
q->front = q->rear = NULL; 
q->size = 0; 
} 
int is_empty(struct Queue *q) 
{ 
return q->size == 0; 
} 
void enqueue(struct Queue *q, struct Process *p) { 
struct Node *node = create_node(p); 
if (is_empty(q)) 
{ 
q->front = q->rear = node; 
} 
else 
{ 
q->rear->next = node; 
q->rear = node; 
} 
q->size++; 
} 
struct Process* dequeue(struct Queue *q) 
{ 
if (is_empty(q)) 
{ 
return NULL; 
 } 
 struct Node *temp = q->front; 
 struct Process *p = temp->data; 
 q->front = q->front->next; 
 if (q->front == NULL) 
 { 
  q->rear = NULL; 
 } 
 free(temp); 
 q->size--; 
 return p; 
} 
void store_gantt_chart(int gantt_chart[][2], int *gantt_index, int time, 
int pid) 
{ 
 gantt_chart[*gantt_index][0] = time; 
 gantt_chart[*gantt_index][1] = pid; 
 (*gantt_index)++; 
} 
void print_gantt_chart(int gantt_chart[][2], int gantt_index) 
{ 
 printf("\nGantt Chart:\n"); 
 printf("|"); 
 for (int i = 0; i < gantt_index; i++) 
 { 
      
  printf(" P%d |", gantt_chart[i][1]); 
 } 
 printf("\n"); 
  
 printf("0 "); 
 for (int i = 0; i < gantt_index; i++) 
 { 
     
     printf("  %d  ", gantt_chart[i][0]); 
    
      
 } 
 printf("\n"); 
} 
int main() 
{ 
 int n, quant, i, time = 0, total_wt = 0, total_tat = 0; 
 printf("Total number of processes in the system: "); 
 scanf("%d", &n); 
 struct Process *processes[n]; 
 for (i = 0; i < n; i++) { 
  int at, bt; 
  printf("\nEnter the Arrival and Burst time of Process[%d]\n", 
i + 1); 
  printf("Arrival time: "); 
  scanf("%d", &at); 
  printf("Burst time: "); 
  scanf("%d", &bt); 
  processes[i] = create_process(i + 1, at, bt); 
 } 
 printf("Enter the Time Quantum for the process: "); 
 scanf("%d", &quant); 
 struct Queue q; 
 init_queue(&q); 
 for (i = 0; i < n; i++) 
 { 
  if (processes[i]->at == 0) 
  { 
   enqueue(&q, processes[i]); 
  } 
 } 
 int gantt_chart[100][2]; 
 int gantt_index = 0; 
 printf("\nProcess No\tBurst Time\tTAT\tWaiting Time\n"); 
 while (!is_empty(&q)) 
 { 
  struct Process *current = dequeue(&q); 
  if (current->rt > quant) 
  { 
   time += quant; 
   current->rt -= quant; 
   store_gantt_chart(gantt_chart, &gantt_index, time, 
current->pid); 
  } 
  else 
  { 
   time += current->rt; 
   current->rt = 0; 
   current->tat = time - current->at; 
   current->wt = current->tat - current->bt; 
   printf("%d\t\t%d\t\t%d\t%d\n", current->pid, current
>bt, current->tat, current->wt); 
   store_gantt_chart(gantt_chart, &gantt_index, time, 
current->pid); 
   total_wt += current->wt; 
   total_tat += current->tat; 
  } 
  for (i = 0; i < n; i++) 
  { 
   if (processes[i]->at <= time && processes[i]->rt > 0 && 
processes[i] != current) 
   { 
    int already_in_queue = 0; 
    struct Node *node = q.front; 
    while (node != NULL) { 
     if (node->data == processes[i]) 
     { 
      already_in_queue = 1; 
      break; 
     } 
     node = node->next; 
    } 
    if (!already_in_queue) 
    { 
     enqueue(&q, processes[i]); 
    } 
   } 
  } 
  if (current->rt > 0) 
  { 
   enqueue(&q, current); 
  } 
 } 
 print_gantt_chart(gantt_chart, gantt_index); 
 float avg_wt = (float)total_wt / n; 
 float avg_tat = (float)total_tat / n; 
 printf("\nAverage Turn Around Time: %.2f", avg_tat); 
 printf("\nAverage Waiting Time: %.2f", avg_wt); 
 return 0; 
} 
 
// OUTPUT: 
// Total number of processes in the system: 5 
 
// Enter the Arrival and Burst time of Process[1] 
// Arrival time: 2 
// Burst time: 6 
 
// Enter the Arrival and Burst time of Process[2] 
// Arrival time: 5 
// Burst time: 2 
 
// Enter the Arrival and Burst time of Process[3] 
// Arrival time: 1 
// Burst time: 8 
 
// Enter the Arrival and Burst time of Process[4] 
// Arrival time: 0 
// Burst time: 3 
 
// Enter the Arrival and Burst time of Process[5] 
// Arrival time: 4 
// Burst time: 4 
// Enter the Time Quantum for the process: 2 
 
// Process No Burst Time TAT Waiting Time 
// 4  3  7 4 
// 2  2  8 6 
// 5  4  13 9 
// 1  6  17 11 
// 3  8  22 14 
 
// Gantt Chart: 
// | P4 | P1 | P3 | P4 | P5 | P1 | P2 | P3 | P5 | P1 | P3 | P3 | 
// 0    2    4    6    7    9    11   13   15   17   19   21   23   
 
// Average Turn Around Time: 13.40 
// Average Waiting Time: 8.80