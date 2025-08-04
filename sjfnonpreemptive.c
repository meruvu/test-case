#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid, arrival_time, burst_time;
} Process;

void sjf_non_preemptive(Process p[], int n) {
    int wait_time[MAX_PROCESSES], turnaround_time[MAX_PROCESSES], completion_time[MAX_PROCESSES];
    int total_wait = 0, total_turnaround = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    completion_time[0] = p[0].arrival_time + p[0].burst_time;
    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i - 1] + p[i].burst_time;
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - p[i].arrival_time;
        wait_time[i] = turnaround_time[i] - p[i].burst_time;
        total_wait += wait_time[i];
        total_turnaround += turnaround_time[i];
    }

    printf("\nSJF Non-Preemptive Scheduling\n");
    printf("Process\tArrival\tBurst\tWait\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, wait_time[i], turnaround_time[i]);
}

int main() {
    Process p[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process details (PID Arrival Burst):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time);
    }

    sjf_non_preemptive(p, n);
    return 0;
}
