
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "./integral_trap.h"


using namespace std;

 typedef double(*function)(double); 


double f(double x){

	return 7 / (x + 1);
}


double integral(function f, double a, double b, unsigned step_count){

	double q_local = 0, step;
	size_t i;
	if ((0 == step_count) && (a > b))  throw "Error"; 
	else {
		step = (b - a) / (1.0 * step_count);
		for (i = 1; i < step_count; ++i) {

			q_local += f(a + i * step);

		}
		q_local += (f(a) + f(b)) / 2;
		q_local *= step;
	}
		return q_local;
	
}

double integration(function f, double a, double b, int n) {
	
		int rank;
		int size;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		double q_local = 0;

		double step = (b - a) / size;

		if (n < size) {

			q_local = integral(f, a + rank * step, a + (rank + 1) * step, 1);

		}
		else {

			if (n % size == 0) {

				q_local = integral(f, a + rank * step, a + (rank + 1) * step, n / size);

			}

			else {

				if (rank != size - 1)
					q_local = integral(f, a + rank * step, a + (rank + 1) * step, n / size);
				else
					q_local = integral(f, a + rank * step, b, n - (n / size) * (size - 1));
			}

		}
		double q_global = 0;
		MPI_Reduce(&q_local, &q_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		
		return q_global;
	
}

double f1(double x){

	return  7 * (x*x+1);

}

