#include <stdio.h>

void RoundRobin(int id[], int at[], int bt[], int n, int tq)
{
    int rt[n], ct[n], tat[n], wt[n], start[n];
    int visited[n]; // to track first time added to queue

    int queue[200], front = 0, rear = 0;

    int time = 0, completed = 0;

    float sumTAT = 0, sumWT = 0, sumRT = 0;

    int ganttP[200], ganttT[200], g = 0;

    for(int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
        ct[i] = tat[i] = wt[i] = -1;
        start[i] = -1;
        visited[i] = 0;
    }

    printf("\n--- Round Robin Scheduling (Corrected) ---");

    // Add first arriving process
    for(int i = 0; i < n; i++)
    {
        if(at[i] == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n)
    {
        if(front == rear)
        {
            time++;

            for(int i = 0; i < n; i++)
            {
                if(at[i] <= time && visited[i] == 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        if(start[i] == -1)
            start[i] = time;

        ganttP[g] = id[i];
        ganttT[g] = time;
        g++;

        int exec_time = (rt[i] > tq) ? tq : rt[i];

        rt[i] -= exec_time;
        time += exec_time;

        // Add newly arrived processes during execution
        for(int j = 0; j < n; j++)
        {
            if(at[j] <= time && visited[j] == 0)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(rt[i] > 0)
        {
            queue[rear++] = i; // re-add to queue
        }
        else
        {
            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            int response = start[i] - at[i];

            sumTAT += tat[i];
            sumWT += wt[i];
            sumRT += response;

            completed++;
        }
    }

    ganttT[g] = time;

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < g; i++)
        printf(" P%d |", ganttP[i]);

    printf("\n%d", ganttT[0]);
    for(int i = 1; i <= g; i++)
        printf("   %d", ganttT[i]);

    // Table
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");

    for(int i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i], at[i], bt[i], ct[i], tat[i], wt[i], start[i] - at[i]);
    }

    printf("\n\nAverage TAT: %.2f", sumTAT/n);
    printf("\nAverage WT: %.2f", sumWT/n);
    printf("\nAverage RT: %.2f\n", sumRT/n);
}

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int id[n], at[n], bt[n];

    for(int i = 0; i < n; i++)
    {
        id[i] = i + 1;

        printf("\nArrival Time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    RoundRobin(id, at, bt, n, tq);

    return 0;
}
