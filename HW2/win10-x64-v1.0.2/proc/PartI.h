#ifndef PARTI_H
#include "SolverBase.h"
#include <vector>
#include <map>

using namespace std;

class PartI : public SolverBase
{
private:
    int c = 0;
    int ver, edge;
    int weight;
    vector<int> ref;
    bool check = false;
    vector<int>visit;
    vector<vector<int>> reversemap;
    vector<vector<int>> sccM;
    vector<vector<bool>> sccch;
    vector<vector<int>> map;
    vector<int>order;
    vector<int>scc;
    vector<int> toposort;
    bool isAyclic = true;
    int pt1, pt2;
    int path_count=0;

public:
    void read(std::string);
    void solve();
    void write(std::string);
    void topo(int);
    void dfs(int);
    void revdfs(int,int);
    void build(ofstream& file);
};

#define PARTI_H
#endif
