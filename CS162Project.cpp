#include <iostream>
#include <algorithm>
#include <queue>

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
	int i, j, k, min, timeElapsed;
	process temp;
	string answer = "";
	
	//This one sorts the from smalles to biggest arrival time
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
			}
		}
		temp = procs[i];
		procs[i] = procs[min];
		procs[min] = temp;
	}
	
	//Since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	
	//Actual Algorithm
	for(k = 0; k < numProcess; k++){
		//Print answer first then add the burst to the timeElapsed
		answer = answer + to_string(timeElapsed) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
		timeElapsed += procs[k].burst;
		
		//Makes the timeElapsed dynamically changing
		if(timeElapsed < procs[k+1].arrival){
			timeElapsed = procs[k+1].arrival;
		}
	}
	
	//Print Answer
	return answer;
}

//Schedule algorithm for Shortest Job First
string sjf(process procs[],int numProcess){
	int i, j, k, min, timeElapsed = 0, done = 0;
	process temp;
	string answer = "";
	
	//This one sorts the from smallest to biggest burst time
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].burst < procs[min].burst){
				min = j;
			}
			//This takes into account when there are similar burst, choose smallest index
			else if(procs[j].burst == procs[min].burst){
				if(procs[j].index < procs[min].index){
					min = j;
				}
			}
		}
		temp = procs[i];
		procs[i] = procs[min];
		procs[min] = temp;
	}
	
	//Actual Algorithm
	while(done != numProcess){
		for(int k = 0; k < numProcess; k++){
			//Check if arrival time is less than or equal to timeElapsed while also checking if already scheduled
			if(procs[k].arrival <= timeElapsed && procs[k].scheduled == false){
				answer = answer + to_string(timeElapsed) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
				timeElapsed += procs[k].burst;
				procs[k].scheduled = true;
				done++;
				timeElapsed--;
				break;
			}
		}
		//After every iteration increment timeElapsed
		timeElapsed++;
	}
	
	//Print Answer
	return answer;
}

//Schedule algorithm for Round Robin
string rr(process procs[], int numProcess, int quantumTime){
	int i, j, k, min, timeElapsed, done = 0;
	string answer = "";
	process temp;
	queue <process> q;
	queue <process> qTemp;
	
	//This one sorts the from smallest to biggest arrival time
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
			}
		}
		temp = procs[i];
		procs[i] = procs[min];
		procs[min] = temp;
	}
	
	//Pushes all the elements into a queue
	for(k = 0; k < numProcess; k++){
		q.push(procs[k]);
	}
	
	//Since first proc[0].arrival is the smallest arrival time, initialize it to timeElapsed
	timeElapsed = procs[0].arrival;
	
	//Actual algorithm
	while(done != numProcess){
		//If the temporary queue is empty, no interrupt, then keep doing the original queue
		if(qTemp.empty()){
			//Traverses the regular queue
			if(q.front().arrival <= timeElapsed){
				//If less than quantumTime then finish it, update timeElapsed, then pop
				if(q.front().burst < quantumTime){
					answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(q.front().burst) + "X" + "\n";
					timeElapsed += q.front().burst;
					q.pop();
					done++;
				}
				//Else update timeElapsed, push into qTemp, then pop
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(quantumTime) + "\n";
					timeElapsed += quantumTime;
					q.front().burst -= quantumTime;
					qTemp.push(q.front());
					q.pop();
				}
			}
			//Increment timeElapsed so that it doesn't become an infinite loop
			else{
				timeElapsed++;
			}
		}
		//If temporary queue is not empty, there's an interrupt, then check both the original and temporary queue to see which one goes first
		else if(!qTemp.empty()){
			//Checks to see if original queue will run
			if(q.front().arrival <= timeElapsed){
				//Same one as above
				if(q.front().burst < quantumTime){
					answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(q.front().burst) + "X" + "\n";
					timeElapsed += q.front().burst;
					q.pop();
					done++;
				}
				//Same one as above
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(q.front().index) + " " + to_string(quantumTime) + "\n";
					timeElapsed += quantumTime;
					q.front().burst -= quantumTime;
					qTemp.push(q.front());
					q.pop();
				}
			}
			//Else continue the interrupted process
			else{
				//Same one as above only this time with the qTemp
				if(qTemp.front().burst < quantumTime){
					answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(qTemp.front().burst) + "X" + "\n";
					timeElapsed += qTemp.front().burst;
					qTemp.pop();
					done++;
				}
				//Same one as above only this time with the qTemp
				else{
					answer = answer + to_string(timeElapsed) + " " + to_string(qTemp.front().index) + " " + to_string(quantumTime) + "\n";
					timeElapsed += quantumTime;
					qTemp.front().burst -= quantumTime;
					qTemp.push(qTemp.front());
					qTemp.pop();
				}
			}
		}
	}
	
	//Print Answer
	return answer;
}

string priorityP(process procs[],int numProcess){
	int timeElapsed = 0;
	bool allDone = false;
	bool allDoneChecker = false;
	process procsTemp;
	string answer = "";

	//sorts the array of processes by shortest priority times
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

string priorityNP(process procs[],int numProcess){
	int i, j, k, min, timeElapsed = 0, done = 0;
	process temp;
	string answer = "";
	
	//This one sorts the from smallest to biggest priority time
	for(i = 0; i < numProcess - 1; i++){
		min = i;
		for(j = i + 1; j < numProcess; j++){
			if(procs[j].priority < procs[min].priority){
				min = j;
			}
			//This takes into account when there are similar priority, choose smallest index
			else if(procs[j].priority == procs[min].priority){
				if(procs[j].index < procs[min].index){
					min = j;
				}
			}
		}
		temp = procs[i];
		procs[i] = procs[min];
		procs[min] = temp;
	}
	
	//Actual Algorithm
	while(done != numProcess){
		for(int k = 0; k < numProcess; k++){
			//Check if arrival time is less than or equal to timeElapsed while also checking if already scheduled
			if(procs[k].arrival <= timeElapsed && procs[k].scheduled == false){
				answer = answer + to_string(timeElapsed) + " " + to_string(procs[k].index) + " " + to_string(procs[k].burst) + "X" + "\n";
				timeElapsed += procs[k].burst;
				procs[k].scheduled = true;
				done++;
				timeElapsed--;
				break;
			}
		}
		//After every iteration increment timeElapsed
		timeElapsed++;
	}
	
	//Print Answer
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
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
				proc[index-1].scheduled = false;
			}
			cout << i << endl << sjf(proc,numProcess) << endl;
		}
		else if(schedule == "SRTF"){
			for(int index = 1; index <= numProcess; index++){
				//put SRTF algorithm codes here.
			}
		}
		else if(schedule == "P"){
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << priorityP(proc,numProcess) << endl;
		}
		else if(schedule == "PNP"){
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << priorityNP(proc,numProcess) << endl;
		}
		else if(schedule == "RR"){
			cin >> quantumTime;
			for(int index = 1; index <= numProcess; index++){
				proc[index - 1].index = index;
				cin >> proc[index - 1].arrival >> proc[index - 1].burst >> proc[index - 1].priority;
			}
			cout << i << endl << rr(proc,numProcess,quantumTime) << endl;
		}
	}
    return 0;
}