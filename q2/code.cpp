#include <iostream> 
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>
#include <mutex>
using namespace std;


sem_t spoons[5];
thread threads[5];
int status[5];
const char** action;
mutex mtx;


void fill_action() {
	action = (const char **)malloc(4 * sizeof(const char *));
	action[0] = ": Waiting for both spoons.\n";
	action[1] = ": One spoon acquired.\n";
	action[2] = ": Both spoons acquired and eating.\n";
	action[3] = ": Thinking.\n";
	return;
}

void state_log() {
	cout << '\n';
	for(int i = 0;i < 5;i++) {
		printf("S%d%s", i + 1, action[status[i]]);
	}
	cout << '\n';
	return;
}

void update(int pID, int state) {
	if(status[pID] != state) {
		mtx.lock();
		status[pID] = state;
		state_log();
		mtx.unlock();
	}
	return;
}


void eating(int pID) {
	update(pID, 2);
	sleep(20);
	return;
}


void thinking(int pID) {
	update(pID, 3);
	sleep(2);
	return;
}



void proceed(int pID) {

	int s1 = pID, s2 = (pID + 1) % 5;
	if(pID & 1) swap(s1, s2); 

	while(1) {

	update(pID, 0);
	sem_wait(&spoons[s1]);
	update(pID, 1);
	sem_wait(&spoons[s2]);

	eating(pID);

	sem_post(&spoons[s2]);
	sem_post(&spoons[s1]);

	thinking(pID);

	}

	return;
}



void simulate() {


	for(int i = 0;i < 5;i++) {
		sem_init(&spoons[i], 0, 1); 
	}
	fill_action();

	state_log();
	for(int i = 0;i < 5;i++) {
		threads[i] = thread(proceed, i); 
	}

	sleep(30*60);

	// for(int i = 0;i < 5;i++) {
	// 	threads[i].join();
	// }

	return;
}




int main() {

	simulate();

    return 0;
}
