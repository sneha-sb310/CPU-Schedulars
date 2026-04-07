#include <bits/stdc++.h>
#include "process.h"

using namespace std;

bool compareAT(Process a, Process b)
{
    return a.at < b.at;
}
bool comparePID(Process a, Process b)
{
    return a.pid < b.pid;
}
void FCFS(vector<Process> &p, int n)
{
    float sumTAT = 0, sumWT = 0, sumRT = 0;
    int idleTime = 0;

    sort(p.begin(), p.end(), compareAT);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            p[i].startTime = p[i].at;
        else
            p[i].startTime = max(p[i].at, p[i - 1].ct);

        p[i].ct = p[i].startTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;

        sumTAT += p[i].tat;
        sumWT += p[i].wt;
        sumRT += p[i].rt;

        if (i != 0)
            idleTime = idleTime + (p[i].startTime - p[i - 1].ct);
    }

    int cycleLength = p[n - 1].ct - p[0].startTime;
    float CPU_utilize = (float)(cycleLength - idleTime) / cycleLength;

    sort(p.begin(), p.end(), comparePID);
    cout << "----------------------------------------------------" << endl;
    cout << "                   FCFS Schedular                   " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }
    cout << "----------------------------------------------------" << endl;
    cout << "Average TAT = " << sumTAT / n << endl;
    cout << "Average WT = " << sumWT / n << endl;
    cout << "Average RT = " << sumRT / n << endl;
    cout << "Throughput = " << (float)n / cycleLength << endl;
    cout << "CPU Utilization = " << CPU_utilize * 100 << endl;
    cout << "----------------------------------------------------" << endl;
}
void SJF(vector<Process> &p, int n)
{
    int currTime = 0;
    int completed = 0;
    bool isCompleted[100] = {false};
    bool isFirstProcess = true;
    int prev = 0;
    float sumTAT = 0, sumWT = 0, sumRT = 0;
    int idleTime = 0;

    while (completed != n)
    {
        int minIndex = -1;
        int minimumBT = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && isCompleted[i] == false)
            {
                if (p[i].bt < minimumBT)
                {
                    minimumBT = p[i].bt;
                    minIndex = i;
                }
                if (p[i].bt == minimumBT)
                {
                    if (p[i].at < p[minIndex].at)
                    {
                        minimumBT = p[i].bt;
                        minIndex = i;
                    }
                }
            }
        }
        if (minIndex == -1)
        {
            currTime++;
        }
        else
        {
            p[minIndex].startTime = currTime;
            p[minIndex].ct = p[minIndex].startTime + p[minIndex].bt;
            p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
            p[minIndex].wt = p[minIndex].tat - p[minIndex].bt;
            p[minIndex].rt = p[minIndex].wt;

            sumTAT += p[minIndex].tat;
            sumWT += p[minIndex].wt;
            sumRT += p[minIndex].rt;

            if (isFirstProcess != true)
                idleTime = idleTime + (p[minIndex].startTime - prev);

            completed++;
            isCompleted[minIndex] = true;
            currTime = p[minIndex].ct;
            prev = currTime;
            isFirstProcess = false;
        }
    }

    int maxCompTime = INT_MIN;
    int minArrTime = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        maxCompTime = max(maxCompTime, p[i].ct);
        minArrTime = min(minArrTime, p[i].at);
    }

    int cycleLength = maxCompTime - minArrTime;
    float CPU_utilize = (float)(cycleLength - idleTime) / cycleLength;

    cout << "----------------------------------------------------" << endl;
    cout << "                   SJF Schedular                    " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }
    cout << "----------------------------------------------------" << endl;
    cout << "Average TAT = " << sumTAT / n << endl;
    cout << "Average WT = " << sumWT / n << endl;
    cout << "Average RT = " << sumRT / n << endl;
    cout << "Throughput = " << (float)n / cycleLength << endl;
    cout << "CPU Utilization = " << CPU_utilize * 100 << "%" << endl;
    cout << "----------------------------------------------------" << endl;
}
void PriorityNP(vector<Process> &p, int n)
{
    int currTime = 0;
    int completed = 0;
    bool isCompleted[100] = {false};
    bool isFirstProcess = true;
    int prev = 0;
    float sumTAT = 0, sumWT = 0, sumRT = 0;
    int idleTime = 0;

    while (completed != n)
    {
        int maxIndex = -1;
        int maximum = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && isCompleted[i] == false)
            {
                if (p[i].pri > maximum)
                {
                    maximum = p[i].pri;
                    maxIndex = i;
                }
                if (p[i].pri == maximum)
                {
                    if (p[i].at < p[maxIndex].at)
                    {
                        maximum = p[i].pri;
                        maxIndex = i;
                    }
                }
            }
        }
        if (maxIndex == -1)
        {
            currTime++;
        }
        else
        {
            p[maxIndex].startTime = currTime;
            p[maxIndex].ct = p[maxIndex].startTime + p[maxIndex].bt;
            p[maxIndex].tat = p[maxIndex].ct - p[maxIndex].at;
            p[maxIndex].wt = p[maxIndex].tat - p[maxIndex].bt;
            p[maxIndex].rt = p[maxIndex].wt;

            sumTAT += p[maxIndex].tat;
            sumWT += p[maxIndex].wt;
            sumRT += p[maxIndex].rt;

            if (isFirstProcess != true)
                idleTime = idleTime + (p[maxIndex].startTime - prev);

            completed++;
            isCompleted[maxIndex] = true;
            currTime = p[maxIndex].ct;
            prev = currTime;
            isFirstProcess = false;
        }
    }

    int maxCompTime = INT_MIN;
    int minArrTime = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        maxCompTime = max(maxCompTime, p[i].ct);
        minArrTime = min(minArrTime, p[i].at);
    }

    int cycleLength = maxCompTime - minArrTime;
    float CPU_utilize = (float)(cycleLength - idleTime) / cycleLength;

    cout << "----------------------------------------------------" << endl;
    cout << "          Priority Non-Preemptive Schedular         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "PID\tPri\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].pri << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }
    cout << "----------------------------------------------------" << endl;
    cout << "Average TAT = " << sumTAT / n << endl;
    cout << "Average WT = " << sumWT / n << endl;
    cout << "Average RT = " << sumRT / n << endl;
    cout << "Throughput = " << (float)n / cycleLength << endl;
    cout << "CPU Utilization = " << CPU_utilize * 100 << "%" << endl;
    cout << "----------------------------------------------------" << endl;
}
void PriorityP(vector<Process> &p, int n)
{
    int currTime = 0;
    int completed = 0;
    vector<int> gantt;
    int remBT[100];
    float sumTAT = 0, sumWT = 0, sumRT = 0;
    int idleTime = 0;

    bool isCompleted[100] = {false};

    for (int i = 0; i < n; i++)
        remBT[i] = p[i].bt;

    while (completed != n)
    {
        int maxIndex = -1;
        int maxPri = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && !isCompleted[i])
            {
                if (p[i].pri > maxPri)
                {
                    maxPri = p[i].pri;
                    maxIndex = i;
                }
                else if (p[i].pri == maxPri)
                {
                    if (p[i].at < p[maxIndex].at)
                        maxIndex = i;
                }
            }
        }
        if (maxIndex == -1)
        {
            gantt.push_back(-1);
            currTime++;
            idleTime++;
        }
        else
        {
            if (remBT[maxIndex] == p[maxIndex].bt)
                p[maxIndex].startTime = currTime;

            gantt.push_back(p[maxIndex].pid);
            remBT[maxIndex]--;
            currTime++;

            if (remBT[maxIndex] == 0)
            {
                p[maxIndex].ct = currTime;
                p[maxIndex].tat = p[maxIndex].ct - p[maxIndex].at;
                p[maxIndex].wt = p[maxIndex].tat - p[maxIndex].bt;
                p[maxIndex].rt = p[maxIndex].startTime - p[maxIndex].at;

                sumTAT += p[maxIndex].tat;
                sumWT += p[maxIndex].wt;
                sumRT += p[maxIndex].rt;

                isCompleted[maxIndex] = true;
                completed++;
            }
        }
    }

    int maxCompTime = INT_MIN;
    int minArrTime = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        maxCompTime = max(maxCompTime, p[i].ct);
        minArrTime = min(minArrTime, p[i].at);
    }

    int cycleLength = maxCompTime - minArrTime;
    float CPU_utilize = (float)(cycleLength - idleTime) / cycleLength;

    cout << "----------------------------------------------------------" << endl;
    cout << "              Priority Preemptive Schedular               " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "PID\tPri\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].pri << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }
    cout << "----------------------------------------------------------" << endl;

    cout << "Gantt Chart : " << endl;
    cout << "|";
    for (int i = 0; i < gantt.size(); i++)
    {
        if (gantt[i] == -1)
            cout << " IDLE |";
        else
            cout << " P" << gantt[i] << " |";
    }
    cout << endl;
    cout << "0    ";
    for (int i = 1; i <= gantt.size(); i++)
    {
        cout << i << setw(5);
    }
    cout << endl;

    cout << "----------------------------------------------------------" << endl;
    cout << "Average TAT = " << sumTAT / n << endl;
    cout << "Average WT = " << sumWT / n << endl;
    cout << "Average RT = " << sumRT / n << endl;
    cout << "Throughput = " << (float)n / cycleLength << endl;
    cout << "CPU Utilization = " << CPU_utilize * 100 << "%" << endl;
    cout << "----------------------------------------------------" << endl;
}
void ROUND_ROBIN(vector<Process> &p, int n, int tq)
{

    int currTime = 0;
    int completed = 0;
    int index = 0;
    vector<int> gantt;
    queue<int> q;
    float sumTAT = 0, sumWT = 0, sumRT = 0;
    int idleTime = 0;

    bool visited[100] = {false};
    bool isFirstProcess = true;

    for (int i = 0; i < n; i++)
        p[i].bt_rem = p[i].bt;

    sort(p.begin(), p.end(), compareAT);
    q.push(0);
    visited[0] = true;

    while (completed != n)
    {
        index = q.front();
        q.pop();
        if (p[index].bt_rem == p[index].bt)
        {
            p[index].startTime = max(currTime, p[index].at);
            if (isFirstProcess != true)
                idleTime = idleTime + (p[index].startTime - currTime);

            currTime = p[index].startTime;
            isFirstProcess = false;
        }

        if (p[index].bt_rem - tq > 0)
        {
            for (int t = 0; t < tq; t++)
                gantt.push_back(p[index].pid);

            p[index].bt_rem -= tq;
            currTime += tq;
        }
        else
        {
            for (int t = 0; t < p[index].bt_rem; t++)
                gantt.push_back(p[index].pid);

            currTime += p[index].bt_rem;
            p[index].bt_rem = 0;
            completed++;

            p[index].ct = currTime;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].rt = p[index].startTime - p[index].at;

            sumTAT += p[index].tat;
            sumWT += p[index].wt;
            sumRT += p[index].rt;
        }

        for (int i = 1; i < n; i++)
        {
            if (p[i].bt_rem > 0 && p[i].at <= currTime && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }

        if (p[index].bt_rem > 0)
            q.push(index);

        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (p[i].bt_rem > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    int maxCompTime = INT_MIN;

    for (int i = 0; i < n; i++)
        maxCompTime = max(maxCompTime, p[i].ct);

    int cycleLength = maxCompTime - p[0].at;
    float CPU_utilize = (float)(cycleLength - idleTime) / cycleLength;

    sort(p.begin(), p.end(), comparePID);

    cout << "----------------------------------------------------" << endl;
    cout << "                     Round Robin                    " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].rt << endl;
    }
    cout << "----------------------------------------------------------" << endl;

    cout << "Gantt Chart : " << endl;
    cout << endl;
    cout << "|";
    for (int i = 0; i < gantt.size(); i++)
    {
        if (gantt[i] == -1)
            cout << " IDLE |";
        else
            cout << " P" << gantt[i] << " |";
    }
    cout << endl;
    cout << "0    ";
    for (int i = 1; i <= gantt.size(); i++)
    {
        cout << i << setw(5);
    }
    cout << endl;

    cout << "----------------------------------------------------" << endl;
    cout << "Average TAT = " << sumTAT / n << endl;
    cout << "Average WT = " << sumWT / n << endl;
    cout << "Average RT = " << sumRT / n << endl;
    cout << "Throughput = " << (float)n / cycleLength << endl;
    cout << "CPU Utilization = " << CPU_utilize * 100 << "%" << endl;
    cout << "----------------------------------------------------" << endl;
}