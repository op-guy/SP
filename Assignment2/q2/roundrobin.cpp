#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include <numeric>
#include <algorithm>

#define vi vector <int>
#define pb push_back
#define ll long long
#define vll vector <ll>
#define ii pair<int,int>
#define Test int t; cin>>t; while(t--)
#define endl '\n';
using namespace std;

// const burst -> never altering burst time list. pe_burst -> a (pre-emptive-ish) copy that will get updated with algorithm

void getWaitTime(const int arrival[], int start[], const int burst[], int wait[], int complete[], bool responseflags[], int resp[], int n, int qt, int *ctxSwitches){

	int *pe_burst = new int[n];
	for(int i=0; i<n; i++) pe_burst[i]=burst[i];

	int t=0;

	while(true){
		bool flag = true;
		for(int i=0; i<n; i++){
			if(arrival[i]<=t){

				// check if process is responded for the first time
				if(!responseflags[i]){
					responseflags[i]=true;
					start[i]=t;
				}

				if(pe_burst[i]>0){
					flag = false; // pending process

					// case 1: pending process will take up full quantum and still not complete
					if(pe_burst[i]>qt){ // run it
						t+=qt;
						pe_burst[i]-=qt;
					}
					// case 2: pending process will either take up full quantum and complete or complete in lesser time than quantum
					else{
						t+=pe_burst[i];
						complete[i]=t;
						// wait[i] = t-burst[i];
						pe_burst[i]=0;
					}
					(*ctxSwitches)++;
				}
			}
			// flag is false if all pe_burst[i] are = 0
		}
		int min_burst=*min_element(pe_burst, pe_burst+n);
		if(min_burst>0){
			t=min_burst;
			continue;
		}
		if(flag) break;
	}
}

void robin (const int arrival[], const int burst[], int n, int qt){
	int *wait = new int[n];
	int *turnard = new int[n];
	int *complete = new int[n];
	int *resp = new int[n];
	int *start = new int[n];

	bool *responseflags = new bool[n];
	int ctxSwithces=0;

	for(int i=0; i<n; i++) responseflags[i]=false;

	getWaitTime(arrival, start, burst, wait, complete, responseflags, resp, n, qt, &ctxSwithces);

	// calculate turnard
	for(int i=0; i<n; i++){
		turnard[i] = complete[i] - arrival[i];
	}
	for(int i=0; i<n; i++){
		wait[i]=turnard[i]-burst[i];
		resp[i]=start[i]-arrival[i];
	}

	cout<<"Process # \t Start \t Complete \t Turnaround \t Waiting \t Response\n";
	for(int i=0; i<n; i++){
		printf("%d \t\t %d \t %d \t\t %d \t\t %d \t\t %d\n", i+1, start[i], complete[i], turnard[i], wait[i], resp[i]);
	}

	int ATT=0, AWT=0, ART=0;

	cout<<"ATT: "<<accumulate(turnard, turnard+n, ATT)/(float)n<<endl;
	cout<<"AWT: "<<accumulate(wait, wait+n, AWT)/(float)n<<endl;
	cout<<"ART: "<<accumulate(resp, resp+n, ART)/(float)n<<endl;
	cout<<"Context Switches: "<<ctxSwithces<<endl;
}

int main(){
	int n, qt;
	cout<<"n: ";
	cin>>n;
	cout<<"arrival: ";
	int *arrival = new int [n];
	for(int i=0; i<n; i++) cin>> arrival[i];
	cout<<"burst: ";
	int *burst   = new int [n];
	for(int i=0; i<n; i++) cin>> burst[i];
	cout<<"quatum: ";
	cin>>qt;

	robin(arrival, burst, n, qt);

	return 0;
}

// int main(){
// 	int n=6, qt;
// 	int arrival[10] = {5,4,3,1,2,6};
// 	int burst[10] = {5,6,7,9,2,3};
// 	// cout<<"quatum: ";
// 	// cin>>qt;

// 	for(qt=1;qt<=10;qt++){
// 		robin(arrival, burst, n, qt);
// 		cout<<"__________________________________________________________________________________________________\n";
// 	}

// 	return 0;
// }