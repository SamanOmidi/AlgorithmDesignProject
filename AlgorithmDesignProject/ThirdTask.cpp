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

    for(unsigned int i=1 ; i<graph.size() ; i++){
        //cout << parent[i] << ' ' << i << endl;

        if(i == graph.size() - 1)
            cout << parent[i] << " -> " << i;
        else
            cout << parent[i] << " -> " << i << " | ";

    }

    cout << endl;

}

void thirdTask(){
    int n;
    cin >> n;

    vector<vector<int>> graph(n , vector<int>(n));

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            cin >> graph[i][j];
        }
    }

    prim(graph);
}
