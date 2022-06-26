#include <bits/stdc++.h>

using namespace std;

int minPos(vector<int> key , vector<bool> our_set){

    int min = INT_MAX;

    int minPos;

    for(unsigned int i=0 ; i<key.size() ; i++){
        if(our_set[i] == false && key[i] < min){
            min = key[i];
            minPos = i;
        }
    }

    return minPos;
}

void prim(vector<vector<int>>& graph){

    vector<int> parent(graph.size());

    vector<int> key(graph.size());

    vector<bool> our_set(graph.size());

    for(unsigned int i=0 ; i<graph.size() ; i++){
        key[i] = INT_MAX;
        our_set[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for(unsigned int i=0 ; i<graph.size() - 1 ; i++){

        int x = minPos(key,our_set);

        our_set[x] = true;

        for(unsigned int j=0 ; j<graph.size() ; j++){
            if((graph[x][j] && our_set[j] == false) && (graph[x][j] < key[j])){
                parent[j] = x;
                key[j] = graph[x][j];
            }
        }
    }
    int cost = 0;
    for(unsigned int i=1 ; i<graph.size() ; i++){
        cost += graph[i][parent[i]];
        //cout << parent[i] << ' ' << i << endl;
        if(i == graph.size() - 1)
            cout << parent[i] << " -> " << i;
        else
            cout << parent[i] << " -> " << i << " | ";

    }

    cout << endl;

    cout << "COST: " << cost << endl;

}

void thirdTask(){
    /*
    int n;
    cin >> n;

    vector<vector<int>> graph(n , vector<int>(n));

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            cin >> graph[i][j];
        }
    }
    */

    int m;
    cin >> m;

    vector<pair<pair<int,int>,int>> vec;

    for(int i=0 ; i<m ; i++){
        int u , v , e;
        cin >> u >> v >> e;

        //pair u->v + weight e
        pair<pair<int,int>,int> p;
        pair<int,int> temp(u, v);
        p.first = temp;
        p.second = e;
        //adding this transition
        vec.push_back(p);
        //pair v->u + weight e
        p.first.first = v;
        p.first.second = u;
        vec.push_back(p);
    }

    //int n = 4;
    int n;
    cin >> n;

    vector<vector<int>> graph(n , vector<int>(n));

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            if(i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INT_MAX;
        }
    }

    for(unsigned int i=0 ; i<vec.size() ; i++){
        if(vec[i].second < graph[vec[i].first.first][vec[i].first.second]){
            graph[vec[i].first.first][vec[i].first.second] = vec[i].second;
            graph[vec[i].first.second][vec[i].first.first] = vec[i].second;
        }
    }

    /*
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
    */




    prim(graph);
}
