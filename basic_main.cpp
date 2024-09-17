#include "iostream"
#include "time.h"
#include "PriolMid.h"
#include <stdio.h>
#include <stdlib.h> 
#include "chrono"
#include "math.h"
#include <set>


int fixedQuantum(int priority, int size) {
    return ceil(priority / 2);
}

Process* generateRandomProcess() {
    Process* process = new Process();
    process->arrive = rand() % 4;
    process->id = rand() % 500;
    process->priol_mid = rand() % 9;
    process->already = false;
    process->eta = rand() % 11 + 1;
    return process;
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int SIZE;
    std::cout << "Digite o número de processos" << std::endl;
    std::cin >> SIZE;

    std::priority_queue<Process*, std::vector<Process*>, CompareByTime> processes;
    PriolMid* priority = new PriolMid(fixedQuantum);
    std::set<int> processIds;  // Conjunto para armazenar os IDs já existentes

    for (int i = 0; i < SIZE; i++) {
        Process* process = nullptr;
        do {
            process = generateRandomProcess();
        } while (processIds.find(process->id) != processIds.end());  // Verifica se o ID já existe

        processIds.insert(process->id);  // Adiciona o ID ao conjunto
        std::cout << "Processo criado com ID: " << process->id << std::endl;
        std::cout << process << std::endl << std::endl;
        processes.push(process);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::time_t lastTick = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t currentTick;
    int currentId = -1;

    while (SIZE > priority->getProcessed()) {
        Process* nextToArrive = processes.top();
        currentTick = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        if (!processes.empty()) {
            if (currentTick >= nextToArrive->arrive + current_time) {
                auto now = std::chrono::system_clock::now();
                Process* main = priority->getMainProcess();
                if (main != nullptr) {
                    if (main->burst >= main->eta) {
                        priority->deque();
                    }
                }
                priority->enqueue(nextToArrive);
                std::cout << "A new process has arrived, with ID: " << nextToArrive->id << " size: " << processes.size() << std::endl;
                processes.pop();
            }
        }
        Process* first = priority->getMainProcess();
        if (first != nullptr) {
            first->burst += currentTick - lastTick;
            lastTick = currentTick;
            if (currentId != first->id) {
                std::cout << "Current process running: " << first->id << std::endl;
                currentId = first->id;
            }

            if ((first->burst / (first->uses + 1) >= priority->getQuantum() && priority->getFirstPriolQueueSize() > 1) || first->burst >= first->eta) {
                priority->deque();
                first->uses += 1;
                if (first->burst < first->eta) {
                    std::cout << "Process: " << first->id << " was put in the end of queue with priority: " << first->priol_mid << " and run for: " << first->burst << " seconds" << std::endl;
                    priority->enqueue(first);
                } else {
                    std::cout << "Process: " << first->id << " was dequeued" << std::endl;
                    priority->addProcessed();
                }
            }
        }
    }

    std::cout << "Finishing" << std::endl;

    return 0;
}