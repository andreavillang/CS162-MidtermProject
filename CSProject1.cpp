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
		/*
		else if(timeElapsed == procs[k+1].arrival){
			timeElapsed += 1;
		}
		*/
	}
	return answer;
}
string sjf(process procs[],int numProcess){
	int i, j, k, min, temp, timeElapsed;
	string answer = "";
	
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].burst < procs[min].burst){
				min = j;
			}
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
		/*
		else if(timeElapsed == procs[k+1].arrival){
			timeElapsed += 1;
		}
		*/
		}
	}
	return answer;
}
string prio(process procs[],int numProcess){
	int i, j, k, min, temp, timeElapsed, minPrio;
	string answer = "";
	queue <process> q;
	queue <process> qTemp;
	
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].arrival < procs[min].arrival){
				min = j;
			}
			//This takes into account when there are similar arrival, choose smallest index
			else if(procs[j].arrival == procs[min].arrival){
				if(procs[j].priority < procs[min].priority){
					min = j;
				}
				else if(procs[j].priority == procs[min].priority){
					if(procs[j].index < procs[min].index){
						min = j;
					}
					else{
						min = min;
					}
				}
			}
		}
		//Sorting Priority
		temp = procs[i].priority;
		procs[i].priority = procs[min].priority;
		procs[min].priority = temp;
		
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
		
	//push the sorted process array into a queue for an easier time in traversing
	for(int l = 0; l < numProcess; l++){
		q.push(procs[l]);
	}
	//since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	minPrio = procs[0].priority;
	}
	return answer;
}

string rr(process procs[], int numProcess, int quantumTime){
	int i, j, k, l, min, temp, timeElapsed;
	string answer = "";
	queue <process> q;
	queue <process> qTemp;
	
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
	
	//push the sorted process array into a queue for an easier time in traversing
	for(l = 0; l < numProcess; l++){
		q.push(procs[l]);
	}
	
	//since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	
	//prints answers
	while(!q.empty()){
		
		//precaution in case we did the temp and will probably need to do qTemp again instead of q
		if(qTemp.empty() || q.front().arrival <= timeElapsed){
			//print answer first then add the burst to the timeElapsed depending if they exceeded the quantumTime or not
			if(q.front().burst <= quantumTime){
				answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(q.front().burst) + "X" + "\n";
				timeElapsed += q.front().burst;
			}
			//if quantumTime exceeded then push the first element of q into a temporary qTemp that will be used later
			else if(q.front().burst > quantumTime){
				q.front().burst -= quantumTime;
				answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(quantumTime) + "\n";
				timeElapsed += quantumTime;
				qTemp.push(q.front());
			}
			
			//pops elements from the q after adding burst to the timeElapsed.
			q.pop();
		}
		
		//if the arrival of q is less than or equal to timeElapsed then do that instead of the element inside qTemp
		if(q.front().arrival <= timeElapsed){
			if(timeElapsed < q.front().arrival){
				timeElapsed = q.front().arrival;
			}
		}
		
		//else then use qTemp so that CPU does not waste any clock cycles
		else if(qTemp.front().arrival < q.front().arrival){
			//does the process same with q except this time with qTemp
			if(qTemp.front().burst <= quantumTime){
				answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(qTemp.front().burst) + "X" + "\n";
				timeElapsed += qTemp.front().burst;
			}
			else if(qTemp.front().burst > quantumTime){
				qTemp.front().burst -= quantumTime;
				answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(quantumTime) + "\n";
				timeElapsed += quantumTime;
				qTemp.push(qTemp.front());
			}
			//don't forget to pop after
			qTemp.pop();
		}
		/*
		else{
			if(timeElapsed < q.front().arrival){
				timeElapsed = q.front().arrival;
			}
		}
		*/
	}
	return answer;
}

int main(){
    int numTestCase, numProcess, a, b, p, quantumTime;
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
				nig[index - 1].index = index;
				cin >> a >> b >> p;
				nig[index - 1].arrival = a;
				nig[index - 1].burst = b;
				nig[index - 1].priority = p;
			}
			cout << prio(nig,numProcess);
		}
		else if(schedule == "RR"){
			cin >> quantumTime;
			for(int index = 1; index <= numProcess; index++){
				nig[index - 1].index = index;
				cin >> nig[index - 1].arrival >> nig[index - 1].burst >> nig[index - 1].priority;
			}
			cout << i << endl << rr(nig,numProcess,quantumTime) << endl;
		}
	}

    return 0;
}