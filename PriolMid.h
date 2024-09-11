#include "iostream"
#include <queue>
#include "process.h"
#include "vector"
#include "map"
#include <algorithm>

#ifndef PRIOL_MID_H
#define PRIOL_MID_H

class PriolMid {
    public:
        PriolMid(int quantums);
        PriolMid();
        ~PriolMid();
        void enqueue(Process* process);
        void printQueue();
        int getSize() {
            return this->processes.size();
        };
        
        Process* getMainProcess();
        bool isQueueEmpty();

        std::vector<int> getOrderedKeys();
        int findFirstPriolQueue();
        
        bool empty() {
            return this->processes.empty();
        }
        
        int getQuantum() {
            return this->quantum;
        }

        int getCounter() {
            return this->counter;
        }
        
    private:
        std::map<int, std::priority_queue<Process*, std::vector<Process*>, Compare>> processes;
        int quantum;
        int counter;
};

#endif