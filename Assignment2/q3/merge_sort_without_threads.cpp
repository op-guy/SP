#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <chrono>
using namespace std;

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
	int n = stoi(argv[1]);
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

	merge_sort(arr,0,n - 1);
	
	printf("Array after: \n");
	for(int i = 0;i < n;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - start;
	
	cout << "Time taken: " << (float)elapsed.count() << " s\n";
	
	// cout << "Sorted? " << sorted(arr, n) << '\n';;
	return 0;
}