#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct process{
	int index;
	int arrival;
	int burst;
	int priority;
};

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

string srtf(process procs[],int numProcess){
	int min, temp, timeElapsed;
	int allDone = 0;
	string answer = "";
	queue <process> qOut;
	queue <process> qTemp;
	
	//This one sorts the from least to greatest
	//The least will be stored in min
	for(int i = 0; i < numProcess - 1; i++){
		min = i;
		for(int j = i + 1; j < numProcess; j++){
			//Sorts via arrival then burst then index
			if(procs[j].arrival < procs[min].arrival){
				min = j;
			}
			else if(procs[j].arrival == procs[min].arrival){
				if(procs[j].burst < procs[min].burst){
					min = j;
				}
				else if(procs[j].burst == procs[min].burst){
					if(procs[j].index < procs[min].index){
						min = j;
					}
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
	while(allDone != numProcess){
		/*
		if arrival p1 + burst p1 > arrival p2
		out cputime p1 == arrival p2 - arrival p1
		*/
		for(int i = 0; i < numProcess; i++){
			if(procs[i].arrival + procs[i].burst > procs[i+1].arrival){
				//If arrival p1 + burst p1 > arrival p2
				//Then update burst p1 and push it into qTemp
				procs[i].burst = procs[i].burst - procs[i+1].arrival;
				qTemp.push(procs[i]);
				answer = answer + to_string(timeElapsed) + " " + to_string(procs[i].index) + " " + to_string(procs[i+1].arrival - procs[i].arrival) + "\n";											
			}
			else if(!qTemp.empty() && procs[i].burst > qTemp.first().burst){
				if(procs[i].arrival + procs[i].burst > procs[i+1].arrival){
					//If arrival p1 + burst p1 > arrival p2
					//Then update burst p1 and push it into qTemp
					procs[i].burst = procs[i].burst - procs[i+1].arrival;
					qTemp.push(procs[i]);
					answer = answer + to_string(timeElapsed) + " " + to_string(procs[i].index) + " " + to_string(procs[i+1].arrival - procs[i].arrival) + "\n";											
				}
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(procs[i].index) + " " + to_string(procs[i].burst) + "X" + "\n";
				}
			}
			else{
				answer = answer + to_string(timeElapsed) + " " + to_string(procs[i].index) + " " + to_string(procs[i].burst) + "X" + "\n";
			}
		}
	}
	
	//since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	
	//prints answers
	for(int i = 0; i < numProcess; i++){
		//print answer first then add the burst to the timeElapsed
		answer = answer + to_string(timeElapsed) + " " + to_string(procs[i].index) + " " + to_string(procs[i].burst) + "X" + "\n";
		timeElapsed += procs[i].burst;
		
		//makes the timeElapsed dynamically changing
		if(timeElapsed < procs[i+1].arrival){
			timeElapsed = procs[i+1].arrival;
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
				//put fcfs algorithm codes here.
			}
		}
		else if(schedule == "SRTF"){
			for(int index = 1; index <= numProcess; index++){
				nig[index - 1].index = index;
				cin >> a >> b >> p;
				nig[index - 1].arrival = a;
				nig[index - 1].burst = b;
				nig[index - 1].priority = p;
			}
			cout << srtf(nig,numProcess);
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