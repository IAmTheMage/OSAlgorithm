#include "iostream"
#include <queue>
#include "Process.h"
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

        
        
        bool empty() {
            return this->processes.empty();
        }
        
        int getQuantum() {
            return this->quantum;
        }

        int getCounter() {
            return this->counter;
        }

        int getProcessed();
        void deque();

        void addProcessed() {
            this->processed += 1;
        };

        int getFirstPriolQueueSize();
        
    private:
        std::map<int, std::priority_queue<Process*, std::vector<Process*>, Compare>> processes;
        std::map<int, double> lastTimeByProcess;
        int quantum;
        int counter;
        double lastProcesedTime;
        int processed;

        std::vector<int> getOrderedKeys();
        int findFirstPriolQueue();
};

#endif