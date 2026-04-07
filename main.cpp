#include <bits/stdc++.h>
#include "process.h"

using namespace std;
int main()
{
    int n, ch;
    cout << "Enter number of Process : " << endl;
    cin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process " << i << " Arrival Time : ";
        cin >> p[i].at;
        p[i].pid = i;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Process " << i << " Burst Time : ";
        cin >> p[i].bt;
    }

    while (true)
    {
        cout << "\n----- CPU Scheduling Menu -----" << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF (Non-Preemptive)" << endl;
        cout << "3. Priority (Non-Preemptive)" << endl;
        cout << "4. Priority (Preemptive)" << endl;
        cout << "5. Round Robin" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 0)
            break;

        switch (ch)
        {
        case 1:
            FCFS(p, n);
            break;

        case 2:
            SJF(p, n);
            break;

        case 3:
            for (int i = 0; i < n; i++)
            {
                cout << "Enter Process " << i << " Priority : ";
                cin >> p[i].pri;
            }
            PriorityNP(p, n);
            break;

        case 4:
            for (int i = 0; i < n; i++)
            {
                cout << "Enter Process " << i << " Priority : ";
                cin >> p[i].pri;
            }
            PriorityP(p, n);
            break;

        case 5:
        {
            int tq;
            cout << "Enter Time Quantum: ";
            cin >> tq;
            ROUND_ROBIN(p, n, tq);
            break;
        }

        default:
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
