/*
Should run with 2 MPI tasks with the following loop. Task 0 sends a message (its rank) to task 1 (tag: 0) 
(MPI_Ssend) After task 1 receives the message it sends a message (its rank) to task 0 (tag: 1) (MPI_Recv)
The loop should be repeated 100 times The program should abort if it is run with the wrong number of MPI 
tasks and should issue a corresponding error message
*/
#include<iostream>
#include "mpi.h"
using namespace std;
int main(int args, char *argv[])
{
	setlocale(LC_CTYPE, 0);
	int rank, size, recvrank;
	int pingpong[100];
	int tags[100];
	int NUM_ping = 100;
	MPI_Init(&args, &argv);
	MPI_Status stat;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(size != 2){
		printf("Process sany 2 bolu kerek!");
		return -1;
	}

	int counter = 0;
	int pp_rank = (rank + 1)%2;
	int tag;

	while(counter <= NUM_ping){
		if(counter%2 == 0) 	tag = 0;
		else 	tag = 1;
		if(rank == counter%2){
			MPI_Ssend(&rank, 1, MPI_INT, pp_rank, tag, MPI_COMM_WORLD);
			pingpong[counter] = rank;
			tags[counter] = tag;
	}
	else{
	MPI_Recv(&recvrank, 1, MPI_INT, pp_rank, tag, MPI_COMM_WORLD, &stat);
			pingpong[counter] = recvrank;
			tags[counter] = tag;
	} counter++;
	}
	if(rank == 0)
	{
		for(int i = 0; i< NUM_ping; i++)
	printf("%d) Habarlama almasy %d - dan %d-ga jasaldy, TAG = %d\n", i, pingpong[i], (pingpong[i] + 1)%2, tags[i]);
	}
	MPI_Finalize();
	return 0;
}
