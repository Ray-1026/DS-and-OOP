#include "PartII.h"
#include <iostream>
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
void PartII::read(std::string file) {
	std::cout << "Part II reading..." << endl;
	ifstream input(file);
	input >> ver >> edge;
	path.resize(ver, vector<int>(ver, 0));
	dist.resize(ver, 0);
	parent.resize(ver, 0);
	dist2.resize(ver, 0);
	parent2.resize(ver, 0);
	visit.resize(ver, 0);

	for (int i = 0; i < edge; i++) {
		input >> st[i] >> bk[i] >> ed[i];
		path[st[i]][bk[i]] = ed[i];
	}
}
void PartII::solve() { std::cout << "Part II solving..." << std::endl;
dijkstra();
bool checkneg = false;
checkneg=bellman();
}
void PartII::write(std::string file) {
	std::cout << "Part II writing..." << std::endl;
		ofstream output(file, ios::trunc);
		output << dist[ver - 1] << "\n";
		if (checkneg) {
			output << "Negative loop dected!\n";
		}
		else {
			output << dist2[ver - 1] << "\n";
		}
		output.close();
}
void PartII::dijkstra() {
	int min;
	int min_idx;
	for (int i = 0; i < edge; i++) {
		path[st[i]][bk[i]] = abs(ed[i]);
	}
	while (check < ver) {
		min = 1e9;
		min_idx = -1;
		for (int i = 0; i < ver; i++) {
			if (visit[i] == 1) {
				continue;
			}
			if (dist[i] < min) {
				min = dist[i];
				min_idx = i;
			}
		}
		if (min_idx == -1) {
			break;
		}
		visit[min_idx] = 1;
		check++;

		for (int i = 0; i < ver; i++) {
			if (path[min_idx][i] != 0 && dist[min_idx] + path[min_idx][i] < dist[i]) {
				parent[i] = min_idx;
				dist[i] = dist[min_idx] + path[min_idx][i];
			}
		}
	}
}
bool PartII::bellman() {
	for(int i = 0; i < ver; i++) {
		dist2[i] = 1e9;
	}
	dist2[0] = 0;
	for (int i = 0; i < ver; i++) {
		for (int a = 0; a < ver; ++a) {
			for (int b=0; b < ver; ++b) {
				if (dist2[a] != 9 && path[a][b] != 1e9) {
					if (dist2[a] + path[a][b] < dist2[b]) {
						dist2[b] = dist2[a] + path[a][b];
						parent2[b] = a;
					}
				}
			}
		}
	}
	for (int a = 0; a < ver; ++a) {
		for (int b = 0; b < ver; ++b) {
			if (dist2[a] != 9 && path[a][b] != 1e9) {
				return true;
			}
		}
	}
	return false;
}
