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
	int vi = 0;
	string answer = "";
	queue <process> qTemp;
	vector <process> v;
	
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

	//everything in procs pushed to vector v
	for(int i = 0; i < numProcess; i++){
		v.push_back(procs[i]);
	}
	
	//prints answers
	while(vi != numProcess){
		/*
		if timeElapsed + burst p1 > arrival p2
		out cputime p1 == arrival p2 - timeElapsed
		*/
		if(vi == numProcess - 1){
			if(!qTemp.empty()){
				if(v.at(vi).burst > qTemp.front().burst){
					answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(qTemp.front().burst) + "X" + "\n";										
					timeElapsed += qTemp.front().burst;
					qTemp.pop();
				}
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi).burst) + "X" + "\n";
					timeElapsed += v.at(vi).burst;
					vi++;
				}
			}
			else{
				answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi).burst) + "X" + "\n";
				timeElapsed += v.at(vi).burst;
				vi++;
			}
		}
		else{
			if(timeElapsed + v.at(vi).burst > v.at(vi+1).arrival){
				v.at(vi).burst = v.at(vi).burst - v.at(vi+1).arrival;
				qTemp.push(v.at(vi));
				answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi+1).arrival - timeElapsed) + "\n";
				timeElapsed += v.at(vi+1).arrival - v.at(vi).arrival;
			}
			else if(!qTemp.empty() && v.at(vi).burst > qTemp.front().burst){
				if(timeElapsed + qTemp.front().burst > v.at(vi+1).arrival){
					qTemp.front().burst = qTemp.front().burst - v.at(vi+1).arrival;
					answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(v.at(vi+1).arrival - timeElapsed) + "\n";											
					timeElapsed += v.at(vi+1).arrival - qTemp.front().arrival;
					qTemp.push(v.at(vi));
				}
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(qTemp.front().burst) + "X" + "\n";
					timeElapsed += qTemp.front().burst;
					qTemp.pop();
					vi++;
				}
			}
			else if(!qTemp.empty() && v.at(vi).burst < qTemp.front().burst){
				if(timeElapsed + v.at(vi).burst > v.at(vi+1).arrival){
					v.at(vi).burst = v.at(vi).burst - v.at(vi+1).arrival;
					qTemp.push(v.at(vi));
					answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi+1).arrival - timeElapsed) + "\n";											
					timeElapsed += v.at(vi+1).arrival - v.at(vi).arrival;
				}
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi).burst) + "X" + "\n";
					timeElapsed += v.at(vi).burst;
					qTemp.pop();
					vi++;
				}
			}
			else{
				answer = answer + to_string(timeElapsed) + " " + to_string(v.at(vi).index) + " " + to_string(v.at(vi).burst) + "X" + "\n";
				timeElapsed += v.at(vi).burst;
				vi++;
			}
		}
		
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
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << srtf(proc,numProcess) << endl;
		}
		else if(schedule == "P"){
			for(int index = 1; index <= numProcess; index++){
				//put p algorithm codes here.
			}
		}
		else if(schedule == "RR"){
			for(int index = 1; index <= numProcess; index++){
				//put rr algorithm codes here.
			}
		}
	}
    return 0;
}