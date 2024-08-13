#include "PriolMid.h"
#include <mpi.h>
#include <iostream>

void createMPIStruct(MPI_Datatype* mpi_process_type) {
    Process process;

   
    int count = 7;

    
    int blocklengths[7] = {1, 1, 1, 1, 1, 1, 1};

    
    MPI_Datatype types[7] = {MPI_INT, MPI_INT, MPI_C_BOOL, MPI_INT, MPI_INT, MPI_INT, MPI_INT};

    
    MPI_Aint offsets[7];
    offsets[0] = offsetof(Process, priol_mid);
    offsets[1] = offsetof(Process, arrive);
    offsets[2] = offsetof(Process, already);
    offsets[3] = offsetof(Process, eta);
    offsets[4] = offsetof(Process, id);
    offsets[5] = offsetof(Process, uses);
    offsets[6] = offsetof(Process, burst);

    
    MPI_Type_create_struct(count, blocklengths, offsets, types, mpi_process_type);
    MPI_Type_commit(mpi_process_type);
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype mpi_process_type;
    createMPIStruct(&mpi_process_type);

    if(rank == 0) {
        PriolMid* priol = new PriolMid(2);
        std::vector<MPI_Request> requests(size);
        std::vector<Process> processes(size);
        double lastTime = priol->getQuantum();
        int i = 0;
        double startTime = MPI_Wtime();
        
        while(true) {
            
            if(i < size - 1) {
                MPI_Request recv_request;
            
                MPI_Irecv(&processes[i], 1, mpi_process_type, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &requests[i]);

                
                int recv_completed = 0;
                MPI_Status status;
                while (!recv_completed) {
                    MPI_Test(&requests[i], &recv_completed, &status);
                    
                }

                std::cout << "A new process has arrived" << std::endl;
                priol->enqueue(&processes[i]);
                i += 1;
            }
           

            if(priol->getSize() >= 1) {
                if(MPI_Wtime() - lastTime >= startTime) {
                    Process* process = priol->getMainProcess();
                    std::cout << "Allowing process to execute: " << process->id << std::endl;
                    int eta = process->eta;
                    int id = process->id;
                    process->uses += 1;
                    int nextQuantum = (process->burst + priol->getQuantum()) < process->eta ? priol->getQuantum() : process->eta - process->burst;
                    std::cout << "Next quantum: " << nextQuantum << std::endl;
                    process->burst += nextQuantum;
                    MPI_Send(&nextQuantum, 1, MPI_INT, process->id, 0, MPI_COMM_WORLD);
                    if(process->burst < process->eta)
                    priol->enqueue(process);
                    int c = 0;
                    MPI_Status procces_status;
                    MPI_Recv(&c, 1, MPI_INT, id, 0, MPI_COMM_WORLD, &procces_status);
                    std::cout << "Status: " << id << " finished" << std::endl;
                    startTime = MPI_Wtime();
                }
            }

        }
    }
    else {
        double startTime = MPI_Wtime();
        Process send_proc;
        send_proc.priol_mid = 10*rank;
        send_proc.arrive = 2*rank;
        send_proc.already = true;
        send_proc.id = rank;
        send_proc.eta = 5*rank;
        int counter = 0;

        double currentTime = MPI_Wtime();
        while(currentTime - startTime <= send_proc.arrive) {
            currentTime = MPI_Wtime();
        }
        MPI_Send(&send_proc, 1, mpi_process_type, 0, 0, MPI_COMM_WORLD);
        while(send_proc.eta - counter > 0) {
            int number;
            MPI_Status _status;
            MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &_status);
            counter += number;
            //std::cout << "Executing process: " << rank << std::endl;
            currentTime = MPI_Wtime();
            while(currentTime - (double)number > MPI_Wtime()) {
                
            }
            MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            
        }
    }

    MPI_Type_free(&mpi_process_type);
    MPI_Finalize();
    return 0;
}
