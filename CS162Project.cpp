#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct process{
	int index;
	int arrival;
	int burst;
	int priority;
	bool scheduled = false;
};

//gets the smallest arrival from the processes and returns its index
int getSmallestArrival(process procs[],int timeElapsed,int numProcess) {
    int min;
    for(int i = 0; i < numProcess; i++){
        if(procs[i].scheduled == false) {
            min = i;
            break;
        }
    }
    for(int i = 0; i < numProcess; i++){
        if(procs[i].scheduled == false){
            if(procs[i].arrival <= timeElapsed){
                min = i;
                break;
            }
            if(procs[i].arrival < procs[min].arrival){
                min = i;
            }
        }
    }
    return min;
}

//gets the next smallest arrival that might
//...interrupt the current process and returns its index
int getNextArrival(process procs[],int bound){
    int min;
    for(int i = 0; i < bound; i++) {
        if(procs[i].scheduled == false){
            min = i;
            break;
        }
    }
    for(int i = 0; i < bound; i++){
        if(procs[i].scheduled == false && procs[i].arrival < procs[min].arrival){
        	//arrival of procs[i] must be smaller than arrival of current process
            min = i;
        }
    }
    return min;
}

//schedule algorithm for first come, first serve
string fcfs(process procs[],int numProcess){
	int i, j, k, min, temp, timeElapsed;
	string answer = "";
	
	//This one sorts the from least to greatest
	//The least will be stored in min
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].arrival < procs[min].arrival){
				min = j;
			}
			//This takes into account when there are similar arrival, choose smallest index
			else if(procs[j].arrival == procs[min].arrival){
				if(procs[j].index < procs[min].index){
					min = j;
				}
				else{
					min = min;
				}
			}
		}
		//Sorting Arrival
		temp = procs[i].arrival;
		procs[i].arrival = procs[min].arrival;
		procs[min].arrival = temp;
		
		//Sorting Burst
		temp = procs[i].burst;
		procs[i].burst = procs[min].burst;
		procs[min].burst = temp;
		
		//Sorting Index
		temp = procs[i].index;
		procs[i].index = procs[min].index;
		procs[min].index = temp;
	}
	
	//since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	
	//prints answers
	for(k = 0; k < numProcess; k++){
		//print answer first then add the burst to the timeElapsed
		answer = answer + to_string(timeElapsed) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
		timeElapsed += procs[k].burst;
		
		//makes the timeElapsed dynamically changing
		if(timeElapsed < procs[k+1].arrival){
			timeElapsed = procs[k+1].arrival;
		}
	}
	return answer;
}

string priorityP(process procs[],int numProcess){
	int timeElapsed = 0;
	bool allDone = false;
	bool allDoneChecker = false;
	process procsTemp;
	string answer = "";

	//sorts the array of processes by shortest burst times
	for(int i = 0; i < numProcess-1; i++){
		for(int j = 0; j < numProcess-i-1; j++){
			if(procs[j].priority > procs[j+1].priority) {
				procsTemp = procs[j];
				procs[j] = procs[j+1];
				procs[j+1] = procsTemp;
			}
			else if(procs[j].priority == procs[j+1].priority){
				if(procs[j].index > procs[j+1].index){
					procsTemp = procs[j];
					procs[j] = procs[j+1];
					procs[j+1] = procsTemp;
				}
			}
		}
	}
    
    //while not all the processes are done, loop
    while(!allDone){
    	//first gets the starting index of the process with the smallest arrival
        int startIndex = getSmallestArrival(procs, timeElapsed, numProcess);
        //then gets the index of the next process with the smallest arrival
        //...that might interrupt the current process
        int nextIndex = getNextArrival(procs, startIndex);
        //set timeElapsed to the current running time
        if(timeElapsed < procs[startIndex].arrival){
            timeElapsed = procs[startIndex].arrival + 1;
        }
        //this will run if a process is interrupted
        if(startIndex != nextIndex && procs[startIndex].burst+timeElapsed - 1 > procs[nextIndex].arrival){
            answer += to_string(timeElapsed) + " " + to_string(procs[startIndex].index) + " " + to_string(procs[nextIndex].arrival - procs[startIndex].arrival)  + "\n";
            
			timeElapsed = procs[nextIndex].arrival;
            procs[startIndex].burst -= (timeElapsed-procs[startIndex].arrival);
            procs[startIndex].arrival = procs[nextIndex].arrival + procs[nextIndex].burst;
        }
        //this will run if a process will complete
        else{
            answer += to_string(timeElapsed) + " " + to_string(procs[startIndex].index) + " " + to_string(procs[startIndex].burst) + "X" + "\n";
            timeElapsed += procs[startIndex].burst;
            procs[startIndex].scheduled = true;
        }

        //checks if all processes have been scheduled which means they are all done
        allDoneChecker = true;
		for(int i = 0; i < numProcess; i++){
			if(procs[i].scheduled == false){
				allDoneChecker = false;
				break;
			}
		}
		allDone = allDoneChecker;
    }
    return answer;
}

int main(){
    int numTestCase, numProcess;
	int quantumTime;
	string schedule;
	
	cin >> numTestCase;
	
	for(int i = 1; i <= numTestCase; i++){
		cin >> numProcess >> schedule;
		process proc[numProcess];
		transform(schedule.begin(), schedule.end(), schedule.begin(), ::toupper);
		
		if(schedule == "FCFS"){
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << fcfs(proc,numProcess) << endl;
		}
		else if(schedule == "SJF"){
			for(int index = 1; index <= numProcess; index++){
				//put sjf algorithm codes here.
			}
		}
		else if(schedule == "SRTF"){
			for(int index = 1; index <= numProcess; index++){
				//put srtf algorithm codes here.
			}
		}
		else if(schedule == "P"){
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << priorityP(proc,numProcess) << endl;
		}
		else if(schedule == "RR"){
			for(int index = 1; index <= numProcess; index++){
				//put rr algorithm codes here.
			}
		}
	}
    return 0;
}