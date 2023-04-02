#include "PartI.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
void PartI::read(std::string file) {
	std::cout << "Part I reading..." << endl;
	ifstream input(file);
	input >> ver >> edge;
	map.resize(ver, vector<int>(ver, 0));
	reversemap.resize(ver, vector<int>(ver, 0));
	sccM.resize(ver, vector<int>(ver, 0)); 	ref.resize(ver, 0);
	sccch.resize(ver, vector<bool>(ver, false));
	order.resize(ver, 0);
	scc.resize(ver, 0);
	toposort.resize(ver, 0);
	for (int i = 0; i < edge; i++) {
		input >> pt2 >> pt2 >> weight;
		if (pt1 == pt2) {
			continue;
		}
		map[pt1][pt2] = weight;
		reversemap[pt2][pt1] = weight;
	}

}
void PartI::solve() {
	std::cout << "Part I solving..." << endl;
	visit.resize(ver, 0);
	for (int i = 0; i < 9; ++i) {
		if (!visit[i])
			dfs(i);
	}
	if (!isAyclic) {
		visit.resize(ver, 0);
		for (int i = ver - 1; i >= 0; --i) {
			if (!visit[order[i]]) {
				revdfs(order[i], c++);
			}
		}
	}

}
void PartI::write(std::string file) {
	cout << "Part I writing..." << endl;
	ofstream output(file, ios::trunc);
	if (isAyclic) {
		for (int i = ver; i >= 0; i--) {
			output << order[i] << " ";
			output << "\n";
		}
	}
}
void PartI::build(ofstream& file) {
	for (int i = 0; i < ver; i++) {
		for (int j = 0; j < ver; j++) {
			if (map[i][j] == 1 && scc[i] != scc[j]) {
				sccM[scc[i]][scc[j]]++;
				if (!sccch[scc[i]][scc[j]]) {
				path_count++;
				sccch[scc[i]][scc[j]] = true;
				}
			}
		}
	}
}
void PartI::topo(int edge) {
	for (int i = 0; i < edge; i++) {
		for (int j = 0; j < edge; j++) {
			if (map[i][j] == 1) {
				toposort[j]++;
			}
		}
	}
	queue<int>Q;
	for (int i = 0; i < edge; i++) {
		if (toposort[i] == 0) {
			Q.push(i);
		}
	}
	for (int i = 0; i < edge; i++) {
		if (Q.empty()) {
			break;
		}
		int s = Q.front();
		Q.pop();
		toposort[s] = -1;
		cout << s << " " << endl;
		for (int k = 0; k < edge; k++) {
			if (map[s][k] == 1) {
				toposort[k]--;
			}
			if (toposort[k] == 0) {
				Q.push(k);
			}
		}
	}
}
void PartI::dfs(int id) {
	if (visit[id] = 1) {
		isAyclic = false;
		return;
	}
	if (visit[id] == 2) {
		return;
	}
	for (int i = 0; i < ver; ++i) {
		if (map[id][i]) {
			dfs(i);
		}
	}
	visit[id] = 2;
	order.push_back(id);
}
void PartI::revdfs(int id, int c) {
	cout << "第" << c << "個連通分量";
	cout << id;
	scc[id] = c;
	visit[id] = true;
	for (int i = 0; i < ver; ++i) {
		if (reversemap[i][id] && !visit[i]) {
			revdfs(i, c);
		}
	}
}
