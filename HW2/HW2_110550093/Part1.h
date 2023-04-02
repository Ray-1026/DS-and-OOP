#ifndef PART1_H
#include "SolverBase.h"
#include <bits/stdc++.h>

using namespace std;

class Part1 : public SolverBase
{
private:
    int n, m, scc_count, scc_path_count;
    vector<vector<int> > graph, t_graph, scc;
    vector<pair<pair<int, int>, int> > path;
    vector<int> visit, order, predecessor;
    bool isAcyclic = true;

public:
    void read(std::string);
    void solve();
    void write(std::string);
    void dfs(int start);
    void scc_dfs(int start);
    void build();
};

#define PART1_H
#endif
