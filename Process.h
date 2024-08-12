#include "iostream"

#ifndef PROCESS_H
#define PROCESS_H



typedef struct _Process {
    int priol_mid;
    int arrive;
    int eta = 10;
    bool already = false;
    int id;
} Process;

class Compare {
public:
    bool operator()(const Process* a, const Process* b) const {
        // Comparação personalizada (menor prioridade para números maiores)
        return a->priol_mid < b->priol_mid;
    }
};


#endif