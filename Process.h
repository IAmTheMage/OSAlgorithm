#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

typedef struct _Process {
    int priol_mid;
    int arrive;
    double eta = 10;
    bool already = false;
    int id;
    int uses = 0;
    int burst = 0;
} Process;

std::ostream& operator<<(std::ostream& os, const Process& p);
std::ostream& operator<<(std::ostream& os, const Process* p);

class Compare {
public:
    bool operator()(const Process* a, const Process* b) const;
};

class CompareByTime {
public:
    bool operator()(const Process* a, const Process* b) const;
};

#endif
