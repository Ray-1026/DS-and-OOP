#include "Part2.h"

void Part2::read(string file) {
    cout << "Part 2 reading...\n" ;
    ifstream input(file);
    int m, from, to, weight;
    input>>num>>m;
    adj_matrix.resize(num, vector<int>(num, 1e9));
    for(int i=0;i<m;i++){
        input>>from>>to>>weight;
        adj_matrix[from][to]=weight;
    }
    input.close();
}

void Part2::solve() {
    std::cout << "Part 2 solving...\n";
    Dijkstra();
    negative_Cycle=Bellmanford();
}

void Part2::Dijkstra(){
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    visit.resize(num, 0);
    abs_d.resize(num, 1e9);
    abs_d[0]=0;
    pq.push({0, 0});
    for(int i=0;i<num;i++){
        int point=-1;
        while(!pq.empty()&&visit[point=pq.top().second])
            pq.pop();
        if(point==-1)
            break;
        visit[point]=1;
        for(int j=0;j<num;j++){
            if(!visit[j]&&abs_d[point]+abs(adj_matrix[point][j])<abs_d[j]){
                abs_d[j]=abs_d[point]+abs(adj_matrix[point][j]);
                pq.push({abs_d[j], j});
            }
        }
    }
}

bool Part2::Bellmanford(){
    d.resize(num, 1e9);
    d[0]=0;
    for(int i=0;i<num-1;i++){
        for(int a=0;a<num;a++){
            for(int b=0;b<num;b++){
                if(d[a]+adj_matrix[a][b]<d[b])
                    d[b]=d[a]+adj_matrix[a][b];
            }
        }
    }
    for(int a=0;a<num;a++){
        for(int b=0;b<num;b++){
            if(d[a]!=1e9&&adj_matrix[a][b]!=1e9){
                if(d[a]+adj_matrix[a][b]<d[b])
                    return true;
            }
        }
    }
    return false;
}

void Part2::write(std::string file) {
    std::cout << "Part 2 writing...\n";
    ofstream output(file, ios::trunc);
    output<<abs_d[num-1]<<"\n";
    if(negative_Cycle)
        output<<"Negative loop detected!\n";
    else
        output<<d[num-1]<<"\n";
    output.close();
}
