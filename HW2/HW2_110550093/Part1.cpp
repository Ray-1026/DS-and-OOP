#include "Part1.h"

void Part1::read(std::string file) {
    std::cout << "Part 1 reading...\n";
    ifstream input(file);
    int from, to, weight;
    input>>n>>m;
    graph.resize(n, vector<int>(n, 0));
    t_graph.resize(n, vector<int>(n, 0));
    path.reserve(m);
    for(int i=0;i<m;i++){
        input>>from>>to>>weight;
        if(from==to)
            continue;
        path.push_back({{from, to}, weight});
        graph[from][to]=weight;
        t_graph[to][from]=weight;
    }
    input.close();
}

void Part1::solve() {
    std::cout << "Part 1 solving...\n";
    visit.resize(n, 0);
    order.reserve(n);
    for(int i=0;i<n;i++){
        if(!visit[i])
            dfs(i);
    }
   if(!isAcyclic){
        scc_count=0;
        visit.clear();
        visit.resize(n, 0);
        predecessor.resize(n, -1);
        for(int i=n-1;i>=0;i--){
            if(!visit[order[i]]){
                visit[order[i]]=1;
                predecessor[order[i]]=scc_count;
                scc_dfs(order[i]);
                scc_count++;
            }
        }
    }
}

void Part1::write(std::string file) {
    std::cout << "Part 1 writing...\n";
    ofstream output(file, ios::trunc);
    if(isAcyclic){
       for(int i=n-1;i>=0;i--)
            output<<order[i]<<" ";
        output<<"\n";
    }
    else{
        build();
        output<<scc_count<<" "<<scc_path_count<<"\n";
        for(int i=0;i<scc_count;i++){
            for(int j=0;j<scc_count;j++){
                if(scc[i][j])
                    output<<i<<" "<<j<<" "<<scc[i][j]<<"\n";
            }
        }
    }
    output.close();
}

void Part1::dfs(int start){
    if(visit[start]==1){
        isAcyclic=false;
        return;
    }
    if(visit[start]==2)
        return;
    visit[start]=1;
    for(int i=0;i<n;i++){
        if(graph[start][i])
            dfs(i);
    }
    visit[start]=2;
    order.push_back(start);
}

void Part1::scc_dfs(int start){
    for(int i=0;i<n;i++){
        if(!visit[i]&&t_graph[start][i]){
            visit[i]=1;
            predecessor[i]=scc_count;
            scc_dfs(i);
        }
    }
}

void Part1::build(){
    scc_path_count=0;
    scc.resize(scc_count, vector<int>(scc_count, 0));
    for(auto it:path){
        int from=predecessor[it.first.first], to=predecessor[it.first.second];
        if(from!=to){
            if(!scc[from][to])
                scc_path_count++;
            scc[from][to]+=it.second;
        }
    }
}
