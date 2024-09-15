#include "Process.h"

std::ostream& operator<<(std::ostream& os, const Process& p) {
    os << "Process ID: " << p.id << "\n"
       << "Priority/Mid: " << p.priol_mid << "\n"
       << "Arrival Time: " << p.arrive << "\n"
       << "ETA: " << p.eta << "\n"
       << "Already: " << (p.already ? "true" : "false") << "\n"
       << "Uses: " << p.uses << "\n"
       << "Burst: " << p.burst;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Process* p) {
    if (p) {
        os << *p;
    } else {
        os << "Null pointer";
    }
    return os;
}

bool Compare::operator()(const Process* a, const Process* b) const {
    if (a->uses != b->uses) {
        return a->uses > b->uses;
    }
    return a->priol_mid < b->priol_mid;
}

bool CompareByTime::operator()(const Process* a, const Process* b) const {
    return a->arrive >= b->arrive;
}
