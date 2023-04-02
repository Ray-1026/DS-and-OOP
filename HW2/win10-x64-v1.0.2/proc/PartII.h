#ifndef PARTII_H
#include "SolverBase.h"
#include <iostream>
#include<bits/stdc++.h>
#include <vector>
using namespace std;
class PartII : public SolverBase
{
private:
	vector<vector<int> > path;
	vector<int>dist;
	vector<int>parent;
	vector<bool>visit;
	int check = 0;
	int ver, edge;
	//bell
	vector<int>st, bk, ed;
	vector<int>dist2;
	vector<int>parent2;
	bool checkneg;
public:
    void read(std::string);
    void solve();
    void write(std::string);
	void dijkstra();
	bool bellman();
};

#define PARTII_H
#endif
