#include "PriolMid.h"

PriolMid::PriolMid(int quantums) {
    
}

PriolMid::PriolMid() {
    std::cout << "Instancing non preemptive priority scheduling" << "\n";
}

PriolMid::~PriolMid() {
    
}

void PriolMid::enqueue(Process* process) {
    this->processes.push(process);
}

void PriolMid::printQueue() {
    while(!this->processes.empty()) {
        Process received_proc = *this->processes.top();
        std::cout << "  priol_mid: " << received_proc.priol_mid << std::endl;
        std::cout << "  arrive: " << received_proc.arrive << std::endl;
        std::cout << "  already: " << (received_proc.already ? "true" : "false") << std::endl;
        this->processes.pop();
    }
}