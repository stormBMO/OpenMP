#include <iostream>
#include <omp.h>
#include <time.h>
#include <math.h>
using namespace std;

#define N 1500

void multiplyMatrix(float** A, float** B, float** C) {
#pragma omp parallel for shared(A, B, C)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				C[i][j] = A[i][k] * B[k][j];
			}
		}
	}
}

int main() {
	int procsCount = omp_get_num_procs();
	double timeStart;
	double timeEnd;
	float** a = new float* [N], ** b = new float* [N], ** c = new float* [N];

	for (int i = 0; i < N; i++) {
		b[i] = new float[N];
		a[i] = new float[N];
		c[i] = new float[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = rand() / 10.0;
			b[i][j] = rand() / 10.0;
		}
	}

	for (int procsI = 1; procsI < procsCount + 1; procsI++) {
		timeStart = omp_get_wtime();
		omp_set_num_threads(procsI);
		multiplyMatrix(a, b, c);
		timeEnd = omp_get_wtime();
		cout << "Result for " << procsI << " thread(s): " << timeEnd - timeStart << endl;
	}
}

