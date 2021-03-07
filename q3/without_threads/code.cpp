#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <time.h>
using namespace std;


int **a, **b, **c;


void initialize(int n) {

	a = (int **)malloc(n*sizeof(int *));
	b = (int **)malloc(n*sizeof(int *));
	c = (int **)malloc(n*sizeof(int *));

	for(int i = 0;i < n;i++) {
		a[i] = (int *)malloc(n*sizeof(int));
		b[i] = (int *)malloc(n*sizeof(int));
		c[i] = (int *)malloc(n*sizeof(int)); 
	}

	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++) {
			a[i][j] = rand() % 100;
			b[i][j] = rand() % 100;
			c[i][j] = 0;
		}
	}
	return;
}



void destroy(int n) {
	for(int i = 0;i < n;i++) {
	 free(a[i]);
	 free(b[i]);
	 free(c[i]);
	}
	free(a);
	free(b);
	free(c);
	return;
}

void sequential(int n, int row_start, int row_end, int column_start, int column_end) {

	
	for(int i = row_start;i <= row_end;i++) {
		for(int j = column_start;j <= column_end;j++) {
			for(int k = 0;k < n;k++) {
				::c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	return;
}


void print(int** mat, int size) {
	for(int i = 0;i < size;i++) {
		for(int j = 0;j < size;j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	return;
}



int main(int argc, char** argv) {

	
	int n = stoi(argv[1]);
	auto start = chrono::steady_clock::now();


	initialize(n);

	
	sequential(n, 0, n - 1, 0, n - 1);

	// print(a, n);
	// print(b, n);
	// print(c, n);

	destroy(n);

	auto end = chrono::steady_clock::now();
	chrono::duration<double> time = end - start;

	cout << n << ' ' << time.count() << '\n';

	return 0;
}