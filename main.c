#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>

extern void getAcc(int n, double* velocities, int* results);

void printMatrix(double* matrix, int n) {
	printf("Confirming inputs: \n");
	for (int i = 0; i < n; i++) {
		printf("%.1f, %.1f, %.1f\n", matrix[i * 3], matrix[i * 3 + 1], matrix[i * 3 + 2]);
	}
}

double measureExecutionTime(int n, double* velocities, int* results, int iterations) {
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);

	double total_us = 0.0;

	for (int i = 0; i < iterations; i++) {
		QueryPerformanceCounter(&start);

		getAcc(n, velocities, results);

		QueryPerformanceCounter(&end);

		double microseconds =
			(double)(end.QuadPart - start.QuadPart) * 1000000.0 / freq.QuadPart;

		total_us += microseconds;
	}

	return total_us / iterations;  // Average in microseconds
}


int main(int argc, char* argv[]) {
	int n;
	scanf_s("%d", &n);

	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	if (n <= 0) {
		printf("Error");
		return 1;
	}

	char line[256];

	double* velocities = (double*)malloc(n * 3 * sizeof(double));
	if (velocities == NULL) {
		printf("Memory Allocation Failiure");
		return 1;
	}

	int* results = (int*)malloc(n * sizeof(int));
	if (results == NULL) {
		printf("MALLOC FAILED");
		free(velocities);
		return 1;
	}

	for (int i = 0; i < n; i++) {
		fgets(line, sizeof(line), stdin);

		for (char* p = line; *p; p++) {
			if (*p == ',')
				*p = ' ';
		}

		if (sscanf_s(line, "%lf %lf %lf",
			&velocities[i * 3],
			&velocities[i * 3 + 1],
			&velocities[i * 3 + 2]) != 3)
		{
			printf("Invalid format on line %d\n", i + 1);
			return 1;
		}
	}

	printMatrix(velocities, n);

	int iterations = 30;
	double avgTime = measureExecutionTime(n, velocities, results, iterations); //get results and execution time


	for (int i = 0; i < n; i++) {
		printf("%d\n", results[i]);
	}
	printf("Average Execution Time: %.10f microseconds\n", avgTime);
	free(velocities);
	free(results);

	return 0;
}