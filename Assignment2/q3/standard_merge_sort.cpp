#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <chrono>
using namespace std;

void merge(int* arr, int l, int mid, int r) {
	int tmp[r - l + 1];
	int i = l, j = mid + 1, k = 0;
	while(i <= mid && j <= r) {
		if(arr[i] <= arr[j]) {
			tmp[k++] = arr[i++];
		}
		else {
			tmp[k++] = arr[j++];
		}
	}
	while(i <= mid) {
		tmp[k++] = arr[i++];
	}
	while(j <= r) {
		tmp[k++] = arr[j++];
	}
	for(int itr = l, k = 0;itr <= r;itr++,k++) {
		arr[itr] = tmp[k];
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