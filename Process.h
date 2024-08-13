#include "iostream"

#ifndef PROCESS_H
#define PROCESS_H

typedef struct _Process {
    int priol_mid;
    int arrive;
    int eta = 10;
    bool already = false;
    int id;
    int uses = 0;
    int burst = 0;
} Process;

class Compare {
public:
    bool operator()(const Process* a, const Process* b) const {
        
        if(a->uses != b->uses) {
            return a->uses > b->uses;
        }
        return a->priol_mid < b->priol_mid;
    }
};


#endif