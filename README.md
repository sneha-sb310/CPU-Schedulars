# CPU Scheduling Algorithms

## Project Overview
This project implements various CPU Scheduling Algorithms used in Operating Systems to manage process execution efficiently.

CPU scheduling determines which process gets CPU time when multiple processes are in the ready queue. The objective is to optimize CPU utilization, minimize waiting time, and improve overall system performance.

---

## Features
- Implementation of multiple CPU scheduling algorithms
- Calculation of:
  - Waiting Time
  - Turnaround Time
  - Response Time
- Clear and structured logic
- Useful for Operating Systems lab practice and interview preparation

---

## Algorithms Implemented
- First Come First Serve (FCFS)
- Shortest Job First (SJF)
- Round Robin (RR)

---

## Technologies Used
- C / C++
- GCC Compiler
- Visual Studio Code

---

## Project Structure
```
CPU_Schedulars/
│── main.c / main.cpp
│── fcfs.c
│── sjf.c
│── rr.c
│── other source files
```

---

## How to Run

### Clone the repository
```bash
git clone https://github.com/sneha-sb310/CPU-Schedulars.git
cd CPU-Schedulars
```

### Compile
```bash
gcc main.c -o scheduler
```

### Run
```bash
./scheduler
```

---

## Sample Input
```
Enter number of processes: 3
Enter burst time: 5 3 8
Enter arrival time: 0 1 2
```

---

## Sample Output
```
Process   Waiting Time   Turnaround Time
P1        0              5
P2        4              7
P3        6              14
```

---

## Learning Outcomes
- Understanding CPU scheduling concepts
- Practical implementation of OS algorithms
- Improved problem-solving and coding skills

---

## Contributing
Contributions are welcome. You can fork the repository and submit pull requests.

---

## License
This project is intended for educational purposes.

---

## Author
Sneha Bujurke
