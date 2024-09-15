#include "PriolMid.h"

PriolMid::PriolMid(int quantums) {
    this->quantum = quantums;
    this->counter = 0;
    this->processed = 0;
}

PriolMid::PriolMid() {
    std::cout << "Instancing non preemptive priority scheduling" << "\n";

}

PriolMid::~PriolMid() {
    
}

void PriolMid::enqueue(Process* process) {
    this->processes[process->priol_mid].push(process);
    this->counter += 1;
}

std::vector<int> PriolMid::getOrderedKeys() {
    std::vector<int> keys;
    for (const auto& pair : this->processes) {
        keys.push_back(pair.first);
    }
    std::sort(keys.begin(), keys.end(), std::greater<int>());
    return keys;
}

int PriolMid::findFirstPriolQueue() {
    std::vector<int> vec = this->getOrderedKeys();
    for(int i = 0; i < vec.size(); i++) {
        if(this->processes[vec[i]].empty() == false) {
            return vec[i];
        }
    }
    return -1;
}

bool PriolMid::isQueueEmpty() {
    std::vector<int> vec = this->getOrderedKeys();
    for(int i = 0; i < vec.size(); i++) {
        if(this->processes[vec[i]].empty() == false) {
            //std::cout << "Priol isn't empty because: " << vec[i] << std::endl;
            return false;
        }
    }
    return true;
}

Process* PriolMid::getMainProcess() {
    int mainQueue = this->findFirstPriolQueue();
    if(mainQueue == -1)
        return nullptr;
    Process* process = this->processes[mainQueue].top();
    return process;
}

void PriolMid::printQueue() {
    std::vector<int> vec = this->getOrderedKeys();
    for(int i = 0; i < vec.size(); i++) {
        std::cout << "Key: " << vec[i] << std::endl;
    }
    // while(!this->processes.empty()) {
    //     Process received_proc = *this->processes.top();
    //     std::cout << "  priol_mid: " << received_proc.priol_mid << std::endl;
    //     std::cout << "  arrive: " << received_proc.arrive << std::endl;
    //     std::cout << "  already: " << (received_proc.already ? "true" : "false") << std::endl;
    //     this->processes.pop();
    // }
}

int PriolMid::getProcessed() {
    return this->processed;
}

void PriolMid::deque() {
    Process* main = this->getMainProcess();

    this->processes[this->findFirstPriolQueue()].pop();
    //this->processed += 1;
    
}