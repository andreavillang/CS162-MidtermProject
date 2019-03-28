#include <iostream>
#include <algorithm>

using namespace std;

struct process{
	int index;
	int arrival;
	int burst;
	int priority;
};

//schedule algorithm for first come, first serve
string fcfs(process procs[],int numProcess){
	int i, j, k, min, temp, arrivalCounter;
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
		
		//since first proc[i].arrival is the smallest arrival time, initialize it to arrivalCounter
		arrivalCounter = procs[i].arrival;
		
		//Sorting Burst
		temp = procs[i].burst;
		procs[i].burst = procs[min].burst;
		procs[min].burst = temp;
		
		//Sorting Index
		temp = procs[i].index;
		procs[i].index = procs[min].index;
		procs[min].index = temp;
	}
	//prints answers
	for(k = 0; k < numProcess; k++){
		answer = answer + to_string(arrivalCounter) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
		
		//makes the time elapsed dynamically changing
		if(procs[k].arrival < procs[k+1].arrival){
			arrivalCounter = procs[k+1].arrival;
		}
		else if(procs[k].arrival == procs[k+1].arrival){
			arrivalCounter += procs[k].arrival;
		}
	}
	return answer;
}

int main(){
    int numTestCase, numProcess, a, b, p;
	int quantumTime;
	string schedule;
	
	cin >> numTestCase;
	cin >> numProcess >> schedule;
	
	process proc[numProcess];
	
	for(int i = 1; i <= numTestCase; i++){
		transform(schedule.begin(), schedule.end(), schedule.begin(), ::toupper);
		if(schedule == "FCFS"){
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> a >> b >> p;
				proc[index - 1].arrival = a;
				proc[index - 1].burst = b;
				proc[index - 1].priority = p;
			}
			cout << fcfs(proc,numProcess);
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
				//put p algorithm codes here.
			}
		}
		else if(schedule == "RR"){
			cin >> quantumTime;
			for(int index = 1; index <= numProcess; index++){
				//put rr algorithm codes here.
			}
		}
	}

    return 0;
}