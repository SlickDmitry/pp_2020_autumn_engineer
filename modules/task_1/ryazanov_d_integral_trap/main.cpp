
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./integral_trap.h"



TEST(Function_Test, f_Return_1_From_6) {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank==0)
  EXPECT_EQ(f(6), 1);
}

TEST(Local_Integration_Test, Integral_Dont_Throws_Exceptions) {
	std::vector<double> result{2.84722};
	EXPECT_NO_THROW(integral(f, 1, 2, 3), result);
} 


TEST(Local_Integration_Test, Integral_Return_Error_When_B_Less_A) {
	
	EXPECT_NO_THROW(integral(f, 5, 4, 3));
} 

TEST(Integration_Test, Integration_Dont_Throws_Exceptions) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0 )
  EXPECT_NO_THROW(integration(f, 1, 3, 2));
}

TEST(Integration_Test, Integration_Return_Value) {
  int rank;
  double result = integral(f, 1, 3, 2);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0 )	  
  EXPECT_EQ(integration(f, 1, 3, 2), result);
}

TEST(Integration_Test, Integration_Return_Value_2) {
  int rank;
  double result = integral(f, 1, 4, 3);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0)
  EXPECT_EQ(integration(f, 1, 4, 3), result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}