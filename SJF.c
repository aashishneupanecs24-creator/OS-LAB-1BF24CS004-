#include <stdio.h>
#define MAX 20


void sjf_nonpreemptive(int n, int at[], int bt[]) {
    int wt[MAX] = {0}, tat[MAX] = {0}, ct[MAX], rt[MAX] = {0};
    int completed[MAX] = {0};
    int time = 0, count = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    while (count < n) {
        int min = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !completed[i]) {
                if (bt[i] < min) {
                    min = bt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            rt[idx] = time - at[idx];
            wt[idx] = rt[idx];
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            completed[idx] = 1;
            count++;
        } else {
            time++;
        }
    }

    printf("\n--- SJF Non-Preemptive ---");
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}


void sjf_preemptive(int n, int at[], int bt[]) {
    int rt[MAX], wt[MAX], tat[MAX], ct[MAX];
    int completed[MAX] = {0};
    int time = 0, count = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) rt[i] = bt[i];

    while (count < n) {
        int min = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (rt[i] < min) {
                    min = rt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            rt[idx]--;
            time++;

            if (rt[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                total_wt += wt[idx];
                total_tat += tat[idx];
                total_rt += (tat[idx] - bt[idx]);
                completed[idx] = 1;
                count++;
            }
        } else {
            time++;
        }
    }

    printf("\n--- SJF Preemptive (SRTF) ---");
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);
}

int main() {
    int n, choice;
    int at[MAX], bt[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time of P%d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. SJF Non-Preemptive\n");
    printf("2. SJF Preemptive (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sjf_nonpreemptive(n, at, bt);
            break;
        case 2:
            sjf_preemptive(n, at, bt);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
