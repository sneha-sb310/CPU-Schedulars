#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
using namespace std;

class Process
{
public:
    int pid;
    int at;
    int bt;
    int pri;

    int ct;
    int tat;
    int wt;
    int rt;
    int startTime;
    int bt_rem;
};

void FCFS(vector<Process> &p,int n);
void SJF(vector<Process> &p,int n);
void PriorityNP(vector<Process> &p,int n);
void PriorityP(vector<Process> &p,int n);
void ROUND_ROBIN(vector<Process> &p,int n, int tq);

#endif
