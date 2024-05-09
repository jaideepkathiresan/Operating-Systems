#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// Function to swap two variables
void swap(int *a, int *b) 
{
	*a = *a + *b - (*b = *a);
}

// Function to calculate waiting time and turnaround time for FCFS scheduling
float fcfs(int pid[], int bt[], int n) {
    int i, wt[n];
    wt[0] = 0;

    // Calculating waiting time of each process
    for (i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    printf("\nFCFS Scheduling:\n");
    printf("Process ID     Burst Time     Waiting Time     Turnaround Time\n");
    float twt = 0.0;
    float tat = 0.0;
    for (i = 0; i < n; i++) {
        printf("%d\t\t", pid[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", wt[i]);

        // Calculating and printing turnaround time of each process
        printf("%d\t\t", bt[i] + wt[i]);
        printf("\n");

        // Calculating total waiting time
        twt += wt[i];

        // Calculating total turnaround time
        tat += (wt[i] + bt[i]);
    }

    float average_wait_time = twt / n;
    float average_turnaround_time = tat / n;
    printf("Avg. waiting time= %f\n", average_wait_time);
    printf("Avg. turnaround time= %f", average_turnaround_time);
	return average_wait_time;
}


// Function to implement Priority Scheduling
float priorityScheduling(int n, int burst_time[], int priority[]) {
    int process_sequence[n], waiting_time[n], turnaround_time[n];

    for (int i = 0; i < n; i++)
        process_sequence[i] = i + 1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                swap(&priority[j], &priority[j + 1]);
                swap(&burst_time[j], &burst_time[j + 1]);
                swap(&process_sequence[j], &process_sequence[j + 1]);
            }
        }
    }

    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("\nPriority Scheduling:\n");
    printf("Process ID     Burst Time     Waiting Time     Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i]; // calculate turnaround time
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n", process_sequence[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n; // calculate average turnaround time
    printf("Average Waiting Time: %f\n", avg_waiting_time);
    printf("Average Turnaround Time: %f\n", avg_turnaround_time); // print average turnaround time
    return avg_waiting_time;
}


// Function to implement Round Robin Scheduling
float roundRobin(int n, int arr_time[], int burst_time[], int time_quantum) {
    int wait_time = 0, ta_time = 0, remaining_burst_time[n];
    int x = n;

    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = burst_time[i];
    }

    int current_time = 0;
    printf("\nRound Robin Scheduling:\n");
    printf("Process ID       Burst Time       Turnaround Time      Waiting Time\n");
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                done = 0;
                if (remaining_burst_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                } else {
                    current_time += remaining_burst_time[i];
                    wait_time += current_time - burst_time[i] - arr_time[i];
                    ta_time += current_time - arr_time[i]; // calculate turnaround time
                    remaining_burst_time[i] = 0;
                    printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n", i + 1, burst_time[i],
                           current_time - arr_time[i], current_time - burst_time[i] - arr_time[i]);
                }
            }
        }
        if (done == 1)
            break;
    }
    float average_wait_time = (float)wait_time / n;
    float average_turnaround_time = (float)ta_time / n; // calculate average turnaround time
    printf("Average Waiting Time: %f\n", average_wait_time);
    printf("Average Turnaround Time: %f\n", average_turnaround_time); // print average turnaround time
    return average_wait_time;
}

// Function to implement Shortest Job First (SJF) Scheduling
float sjf(int burst_time[], int n) {
    int process_sequence[n], waiting_time[n], turnaround_time[n];

    for (int i = 0; i < n; i++)
        process_sequence[i] = i + 1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burst_time[j] > burst_time[j + 1]) {
                swap(&burst_time[j], &burst_time[j + 1]);
                swap(&process_sequence[j], &process_sequence[j + 1]);
            }
        }
    }

    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    int total_waiting_time = 0, total_turnaround_time = 0;
    printf("\nShortest Job First (SJF) Scheduling:\n");
    printf("Process ID     Burst Time     Waiting Time     Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i]; // calculate turnaround time
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n", process_sequence[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n; // calculate average turnaround time
    printf("Average Waiting Time: %f\n", avg_waiting_time);
    printf("Average Turnaround Time: %f\n", avg_turnaround_time); // print average turnaround time
    return avg_waiting_time;
}


// Function to print Gantt chart for FCFS scheduling
void printGanttChartFCFS(int pid[], int bt[], int n) {
    printf("\nGantt Chart for FCFS Scheduling:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n");

    int time = 0;
    printf("%d", time);
    for (i = 0; i < n; i++) {
        time += bt[i];
        printf("     %d", time);
    }
    printf("\n\n");
}

// Function to print Gantt chart for Round Robin scheduling
void printGanttChartRR(int pid[], int bt[], int n, int quantum) {
    printf("\nGantt Chart for Round Robin Scheduling:\n");
    int rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
    }

    int t = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                    printf("|  P%d  ", pid[i]);
                } else {
                    t += rem_bt[i];
                    rem_bt[i] = 0;
                    printf("|  P%d  ", pid[i]);
                }
            }
        }
        if (done == true)
            break;
    }
    printf("|\n");

    int time = 0;
    printf("%d", time);
    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("     %d", time);
    }
    printf("\n\n");
}

// Function to print Gantt chart for Priority scheduling
float printGanttChartPS(int pid[], int bt[], int n) {
    printf("\nGantt Chart for Priority Scheduling:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n");

    int time = 0;
    printf("%d", time);
    for (i = 0; i < n; i++) {
        time += bt[i];
        printf("     %d", time);
    }
    printf("\n\n");
}

// Function to print Gantt chart for SJF scheduling
void printGanttChartSJF(int pid[], int bt[], int n) {
    printf("\nGantt Chart for SJF Scheduling:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n");

    int time = 0;
    printf("%d", time);
    for (i = 0; i < n; i++) {
        time += bt[i];
        printf("     %d", time);
    }
    printf("\n\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], burst_time[n], arrival_time[n], priority[n];
    printf("Enter process ID, arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d", &pid[i], &arrival_time[i], &burst_time[i], &priority[i]);
    }
	float avg_wt_fcfs, avg_wt_ps, avg_wt_rr, avg_wt_sjf;
    // FCFS Scheduling
    avg_wt_fcfs = fcfs(pid, burst_time, n);
	printGanttChartFCFS(pid, burst_time, n);

    // Round Robin Scheduling
    int time_quantum;
    printf("\nEnter the time quantum for Round Robin Scheduling: ");
    scanf("%d", &time_quantum);
    avg_wt_rr = roundRobin(n, arrival_time, burst_time, time_quantum);
	printGanttChartRR(pid, burst_time, n, time_quantum);

    // Priority Scheduling
    avg_wt_ps = priorityScheduling(n, burst_time, priority);
	printGanttChartPS(pid, burst_time, n);

    // SJF Scheduling
    avg_wt_sjf = sjf(burst_time, n);
	printGanttChartSJF(pid, burst_time, n);

	// Compare the average waiting times and find the most efficient scheduling algorithm
    float min_avg_wt = avg_wt_fcfs;
    char* best_algorithm = "FCFS";

    if (avg_wt_rr < min_avg_wt) {
        min_avg_wt = avg_wt_rr;
        best_algorithm = "Round Robin";
    }

    if (avg_wt_ps < min_avg_wt) {
        min_avg_wt = avg_wt_ps;
        best_algorithm = "Priority Scheduling";
    }

    if (avg_wt_sjf < min_avg_wt) {
        min_avg_wt = avg_wt_sjf;
        best_algorithm = "SJF";
    }

    printf("\nThe most efficient scheduling algorithm is %s with an average waiting time of %f\n", best_algorithm, min_avg_wt);

    return 0;
}
