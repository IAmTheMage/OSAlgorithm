#include "iostream"
#include <queue>
#include "Process.h"
#include "vector"
#include "map"
#include <algorithm>
#include <functional> 

#ifndef PRIOL_MID_H
#define PRIOL_MID_H

class PriolMid {
    public:
        PriolMid(std::function<int(int, int)> newQuantumDef);
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
            return this->quantumDef(this->getMainProcess()->priol_mid, this->getFirstPriolQueueSize());
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
        void setQuantumDef(std::function<int(int, int)> newQuantumDef) {
            this->quantumDef = newQuantumDef;
        }
        
    private:
        std::map<int, std::priority_queue<Process*, std::vector<Process*>, Compare>> processes;
        std::map<int, double> lastTimeByProcess;
        int quantum;
        int counter;
        double lastProcesedTime;
        int processed;

        std::vector<int> getOrderedKeys();
        int findFirstPriolQueue();
        std::function<int(int, int)> quantumDef; 
};

#endif