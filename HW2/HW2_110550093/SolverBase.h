#ifndef SOLVERBASE_H
#include <string>
using namespace std;

class SolverBase
{
public:
    virtual void read(string) = 0;
    virtual void solve() = 0;
    virtual void write(string) = 0;
};

#define SOLVERBASE_H
#endif
