#include <stdio.h>
#define MAX 20

void fcfs(int n, int at[], int bt[]) {
    int wt[MAX], tat[MAX], ct[MAX], rt[MAX];
    int time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i];  // CPU idle until process arrives
        }
        rt[i] = time - at[i];   // Response time
        wt[i] = time - at[i];   // Waiting time
        time += bt[i];          // Process executes
        ct[i] = time;           // Completion time
        tat[i] = ct[i] - at[i]; // Turnaround time

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\n---FCFS Scheduling---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

int main() {
    int n;
    int at[MAX], bt[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &at[i]);
    }

    printf("Enter Burst Times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    fcfs(n, at, bt);

    return 0;
}
