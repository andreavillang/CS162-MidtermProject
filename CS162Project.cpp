#include <iostream>

using namespace std;

struct process{
	int index;
	int arrival;
	int burst;
	int priority;
	bool ran;
};

//schedule algorithm for first come, first serve
string fcfs(process procs[],int numProcess){
	int arrivalCounter = procs[0].arrival;
	int indexCounter = procs[0].index;
	int processCounter = numProcess;
	int burst;
	bool state = true;
	string answer = "";
	while(state){
		for(int i = 0; i < numProcess; i++){
			if(arrivalCounter > procs[i].arrival && procs[i].ran == false){
				arrivalCounter = procs[i].arrival;
				indexCounter = procs[i].index;
			}
			else if(arrivalCounter == procs[i].arrival && procs[i].ran == false){
				if(indexCounter > procs[i].index){
					indexCounter = procs[i].index;
				}
			}
			else{
				arrivalCounter = procs[i].arrival;
				indexCounter = procs[i].index;
			}
			procs[indexCounter].ran = true;
			burst = procs[indexCounter].burst;
		}
		processCounter -= 1;
		answer = answer + to_string(arrivalCounter) + " " + to_string(indexCounter) + " " + to_string(burst) + "X" + "\n";
		if(processCounter == 0){
			state = false;
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
				nig[index - 1].ran = false;
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
	
	/*cout << numTestCase << endl << numProcess << endl << schedule << endl;
	cout << fcfs[0].index << endl << fcfs[0].arrival << endl << fcfs[0].burst << endl << fcfs[0].priority;*/

    return 0;
}