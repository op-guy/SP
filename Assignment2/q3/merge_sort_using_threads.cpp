#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include <vector>
using namespace std;


int f(int a, int b) {
	return a/b - (a % b == 0);
}


void merge(int* arr, int l, int mid, int r) {
	int p1 = l, p2 = mid + 1;
	while(p1 <= mid && p2 <= r) {
		if(arr[p1] <= arr[p2]) {
			p1++;
		}
		else {
			int i = p2;
			while(i > p1) {
				swap(arr[i], arr[i - 1]);
				i--;
			}  
			mid++;
			p2++;
			p1++;
		}
	}
	return;
}


void merge_sort(int* arr, int l, int r) {
	if(l >= r) return;
	int mid = l + (r - l)/ 2;
	merge_sort(arr, l, mid);
	merge_sort(arr, mid + 1, r);
	merge(arr, l, mid, r);
	return;
}

string sorted(int* arr, int n) {

	int i = 0;
	while(i < n - 1) {
		if(arr[i] < arr[i - 1]) {
			return "No";
		}
		i++;
	}
	return "Yes";
}



int main(int argc, char* argv[]) {
	int m = stoi(argv[1]) ,n = stoi(argv[2]);
	m = pow(2, (int)(log(m)/ log(2)));
	int* arr = (int *)malloc(sizeof(int)*n);
	for(int i = 0;i < n;i++) {
		arr[i] = ((double)rand()/ RAND_MAX) * 10000;
	}
	
	printf("Array before: \n");
	for(int i = 0;i < n;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	auto start = chrono::steady_clock::now();

	//merge-sort with threads
	vector<pair<int,int>> intervals;
	thread mthreads[m];
	int s = 0, e = f(n, m);
	intervals.push_back(make_pair(s,e));
	for(int i = 0;i < m;i++) {
		mthreads[i] = thread(merge_sort, arr, s, e);
		s = e + 1;
		e = min(s + f(n, m), n - 1);
		if(i < m - 1) intervals.push_back(make_pair(s,e));
	}
	for(int i = 0;i < m;i++) {
		mthreads[i].join();
	}

	
	while(m != 1) {
		m /= 2;
		thread m1threads[m];

		vector<pair<int,int>> intervals1;	

		for(int i = 0, j = 0;i < intervals.size();i += 2, j++) {
			int start = intervals[i].first, mid = intervals[i].second, end = intervals[i + 1].second;
			m1threads[j] = thread(merge, arr, start, mid, end);
			intervals1.push_back(make_pair(start, end)); 
		}

		intervals = intervals1;

		for(int i = 0;i < m;i++) {
		     m1threads[i].join();
		}		
	}

	auto end = chrono::steady_clock::now();

	printf("Array after: \n");
	for(int i = 0;i < n;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	// cout << "Sorted? " << sorted(arr, n) << '\n';
	chrono::duration<double> elapsed = end - start;
	cout << "Time taken: " << elapsed.count() << " s\n";
	free(arr);
	return 0;
}