CS162 - Process Scheduling
160096 Andrea Ang
155498 Genesis Gaspar


I. Description
This project replicates different types of CPU scheduling functions such as:
* First Come First Serve (FCFS)
* Shortest Job First (SJF)
* Shortest Remaining Time First (SRTF)
* Round Robin (RR)
* Priority Preemptive (P)
* Priority Non-Preemptive (PNP)
The Input starts with the number of test cases, which is then followed by blocks of n test cases. The output prints out the blocks for each test case starting with the test case number.


Example Input:
2
4 FCFS
0 50 2
40 2 3
20 3 1
30 55 1
4 SRTF
0 50 2
40 2 3
20 3 1
30 55 1

Example Output:
1
0 1 50X
50 3 3X
53 4 55X
108 2 2X
2
0 1 20
20 3 3X
23 1 17
40 2 2X
42 1 13X
55 4 55X


struct process{
        int index;
        int arrival;
        int burst;
        int priority;
        bool scheduled = false;
};


This struct is used to indicate the, index, arrival, burst and priority of each process. In addition, a boolean called scheduled is added to indicated whether or not a process has completely ran or not.


II. Methods


1. getSmallestArrival(process procs[], int timeElapsed, int numProcess)
   * This method will take in the process array, time that has passed, and the number of processes.
   * It first checks if the process has not been scheduled to start yet.
   * After that it checks for the smallest arrival time whilst taking into consideration the processes that have already been ran.
   * It then returns the index of the process that hasn’t run yet and has the smallest arrival time.


2. getNextArrival(process procs[], int bound)
   * This method will take in the process array and the bound, which is the index returned by getSmallestArrival.
   * It gets the next process with the smallest arrival time that might interrupt the current running process fetched by the previous method.
   * If it returns the same index as the previous method, the process will not be interrupted.


3. fcfs(process procs[], int numProcess)
   * This method will take in the process array and the number of individual processes.
   * Processes are sorted by smallest arrival time then index if the arrival times are the same.
   * timeElapsed starts at the first process’ arrival time.
   * Processes are then printed out in order.


4. sjf(process procs[], int numProcess)
   * This method takes in the process array and the number of processes.
   * It will first sort the process array from smallest to biggest burst time.
   * If there are similar burst times then it will be sorted by smallest index.
   * After that it will run in a while loop that first checks if the process has been scheduled and then checks if the arrival time of that process is less than or equal to the time that has elapsed so far.
   * If it hits it will print out the answer, update the timeElapsed, update the scheduling to true, update the number of processes done, decrement the timeElapsed, and then will break from there.
   * After every iteration or when the iteration breaks, it will increment the timeElapsed so as not to cause an infinite loop.
   * Returns the answer after running the while loop.

5. srtf(process procs[], int numProcess)
   * This method will take in the process array and the number of individual processes.
   * Processes are sorted by smallest burst time.
   * A boolean called allDone is set to false and will cause a loop to keep going as long as not all processes have been scheduled
   * startIndex uses the method getSmallestArrival to get the process (that hasn’t been scheduled) with the smallest arrival time.
   * nextIndex uses the method getNextArrival to get the process (that hasn’t been scheduled) with the smallest arrival time that will most likely interrupt the startIndex process.
   * If nextIndex and startIndex are the same, the current process will not be interrupted.
   * timeElapsed is set to the arrival time of the current running process + 1.
   * If a process is interrupted, timeElapsed, burst and arrival are all updated accordingly.
   * If a process is not interrupted, timeElapsed is updated and its scheduled boolean will be set to true to avoid repitition.
   * A smaller loop within the while loop will check if any single process has not been scheduled yet to continue the algorithm.


6. p(process procs[], int numProcess)
   * The method runs the same as srtf except the processes are sorted by smallest priority then index if priorities are the same.


7. pnp(process procs[], int numProcess)
   * The method runs the same as sjf except the processes are sorted by smallest priority then index if the priorities are the same.


8. rr(process procs[], int numProcess, int quantumTime)
   * This method will take in the process array, number of processes and the quantum time.
   * It will then sort the process array from smallest to biggest arrival time.
   * Then it will push all the elements of the array into a queue.
   * The time elapsed is set to the arrival time of the first processes so as not to delay things.
   * It will be ran into a while loop where first it will check if another queue called qTemp is empty or not.
   * If qTemp is empty then there are no interrupted processes so we continue on by checking if arrival time of the first element in the original queue called q will have less than or equal to the timeElapsed.
   * If it hits then it prints the answer, updates the timeElapsed by adding its burst time, pops it from the queue since it is no longer needed, then finally updates that a process has been completed.
   * Otherwise, prints the answer, updates timeElapsed by adding the quantum time instead, updates the burst time of that element by subtracting it from the quantum time, pushes it into qTemp, then pops it from q.
   * Finally it increments timeElapsed if  the arrival time of the original queue is not less than or equal to the timeElapsed.
   * On the other hand if qTemp is not empty then it first checks the original queue if something can be ran from there by still doing the same check from above.
   * If it hits then it will also do the same methods as previously stated.
   * Otherwise it will do the processes instead from qTemp and does the same job again this time it will do things from the qTemp instead of q.
   * Returns the answer after running the while loop.