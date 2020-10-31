// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_
#define MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_

#include <vector>
#include <string>

typedef double(*function)(double);

double f(double x);
double integral(function f, double a, double b, unsigned step_count);
double integration(function f, double a, double b, int n);

std::vector<int> getRandomVector(int  sz);
int getParallelOperations(std::vector<int> global_vec,
                          int count_size_vector, std::string ops);
int getSequentialOperations(std::vector<int> vec, std::string ops);

#endif  // MODULES_TEST_TASKS_TEST_MPI_OPS_MPI_H_
