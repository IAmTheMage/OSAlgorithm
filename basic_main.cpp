#include "iostream"
#include "time.h"
#include "PriolMid.h"
#include <stdio.h>
#include <stdlib.h> 
#include "chrono"

#define SIZE 4

Process* generateRandomProcess() {
    
    Process* process = new Process();
    process->arrive = rand() % 4;
    process->id = rand() % 151;
    process->priol_mid = rand() % 9;
    process->already = false;
    process->eta = rand() % 11 + 1;
    return process;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    std::priority_queue<Process*, std::vector<Process*>, CompareByTime> processes;
    PriolMid* priority = new PriolMid(2);
    for(int i = 0; i < SIZE; i++) {
        Process* process = generateRandomProcess();
        std::cout << process << std::endl << std::endl;
        processes.push(process);
    }

    auto now = std::chrono::system_clock::now();
    
    // Converte para tempo do sistema
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::time_t lastTick = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t currentTick;

    while(SIZE > priority->getProcessed()) {
        Process* nextToArrive = processes.top();
        currentTick = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        if(!processes.empty()) {
            if(currentTick >= nextToArrive->arrive + current_time) {
                auto now = std::chrono::system_clock::now();
                Process* main = priority->getMainProcess();
                if(main != nullptr) {
                    if(main->burst >= main->eta) {
                        priority->deque();
                    }
                }
                priority->enqueue(nextToArrive);
                //current_time = std::chrono::system_clock::to_time_t(now);
                std::cout << "A new process has enqueued, with id: " << nextToArrive->id << " size: " << processes.size() << std::endl << std::endl;
                processes.pop();
            }
        }
        Process* first = priority->getMainProcess();
        if(first != nullptr) {
            first->burst += currentTick - lastTick;
            lastTick = currentTick;

            
            if(first->burst/(first->uses+1) >= priority->getQuantum()) {
                std::cout << "Process: " << first->id << " was dequeued" << std::endl;
                priority->deque();
                first->uses += 1;
                if(first->burst < first->eta) {
                    priority->enqueue(first);
                }
                else{
                    priority->addProcessed();
                }
            }
        }
        
    }

    std::cout << "Finishing" << std::endl;

    return 0;
}
