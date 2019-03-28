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
	int i, j, k, min, temp;
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
		
		//Printing the answer
		for(k = 0; k < numProcess; k++){
			answer = answer + to_string(procs[k].arrival) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
		}
	}
	return answer;
}
string sjf(process procs[],int numProcess){
	int i, j, k, min, temp;
	string answer = "";
	
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].burst < procs[min].burst){
				min = j;
			}
			//This takes into account when there are similar arrival, choose smallest index
			else if(procs[j].burst == procs[min].burst){
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
		
		//Printing the answer
		for(k = 0; k < numProcess; k++){
			answer = answer + to_string(procs[k].arrival) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
		}
	}
	return answer;
}

int main(){
    int numTestCase, numProcess, a, b, p;
	string schedule;
	
	cin >> numTestCase;
	cin >> numProcess >> schedule;
	
	process nig[numProcess];
	
	for(int i = 1; i <= numTestCase; i++){
		transform(schedule.begin(), schedule.end(), schedule.begin(), ::toupper);
		if(schedule == "FCFS"){
			for(int index = 1; index <= numProcess; index++){
				nig[index - 1].index = index;
				cin >> a >> b >> p;
				nig[index - 1].arrival = a;
				nig[index - 1].burst = b;
				nig[index - 1].priority = p;
			}
			cout << fcfs(nig,numProcess);
		}
		else if(schedule == "SJF"){
			for(int index = 1; index <= numProcess; index++){
				nig[index - 1].index = index;
				cin >> a >> b >> p;
				nig[index - 1].arrival = a;
				nig[index - 1].burst = b;
				nig[index - 1].priority = p;
			}
			cout << sjf(nig,numProcess);
		}
		else if(schedule == "SRTF"){
			for(int index = 1; index <= numProcess; index++){
				//put fcfs algorithm codes here.
			}
		}
		else if(schedule == "P"){
			for(int index = 1; index <= numProcess; index++){
				//put fcfs algorithm codes here.
			}
		}
		else if(schedule == "RR"){
			for(int index = 1; index <= numProcess; index++){
				//put fcfs algorithm codes here.
			}
		}
	}

    return 0;
}
