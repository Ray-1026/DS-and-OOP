#ifndef PART2_H
#include "SolverBase.h"
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class Part2 : public SolverBase
{
private:
    int num;
    vector<vector<int> > adj_matrix;
    vector<int> d, abs_d;
    vector<bool> visit;
    bool negative_Cycle;
    void Dijkstra();
    bool Bellmanford();
public:
    void read(string);
    void solve();
    void write(string);
};

#define PART2_H
#endif
