#include "iostream"
#include <queue>
#include "process.h"
#include "vector"

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
        Process* getMainProcess() {
            Process* process = processes.top();
            processes.pop();
            return process;
        }
        bool empty() {
            return this->processes.empty();
        }
        
    private:
        std::priority_queue<Process*, std::vector<Process*>, Compare> processes;
        int current;
        int size;
};

#endif