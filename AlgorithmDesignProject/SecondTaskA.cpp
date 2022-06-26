#include <bits/stdc++.h>

using namespace std;

class node{
public:
    int vertexNumber;

    vector<pair<int,int>> transitions;

    node(int x){
        this->vertexNumber = x;
    }
    void add_transition(int a , int b){
        pair<int,int> p;
        p.first = a;
        p.second = b;
        this->transitions.push_back(p);
    }
};

vector<int> shortestPath(vector<node*> vec, int s, vector<int>& path){

    vector<int> dist(vec.size());

    vector<bool> visited(vec.size());

    for(unsigned int i=0 ; i<vec.size() ; i++){
        visited[i] = false;
        path[i] = -1;
        dist[i] = INT_MAX;
    }

    dist[s] = 0;
    int curr = s;
    path[s] = -1;

    unordered_set<int> our_set;

    while(true){
        visited[curr] = true;
        for(unsigned int i=0 ; i<vec[curr]->transitions.size() ; i++){
            int v = vec[curr]->transitions[i].first;
            if(!visited[v]){
                our_set.insert(v);

                int sum_path = dist[curr] + vec[curr]->transitions[i].second;

                if(sum_path < dist[v]){
                    dist[v] = sum_path;
                    path[v] = curr;
                }
            }
        }
        our_set.erase(curr);

        if(our_set.empty()){
            break;
        }

        int min_dist = INT_MAX;
        int position = 0;

        for(auto x : our_set){
            if(dist[x] < min_dist){
                min_dist = dist[x];
                position = x;
            }
        }

        curr = position;
    }
    return dist;
}

void printPath(vector<int> path,
               int i, int s)
{
    if (i != s){
        if (path[i] == -1) {
            cout << "Path not found!!";
            return;
        }
        printPath(path, path[i], s);
        cout << path[i] << " -> ";
    }
}

void secondTaskA(){
    int n , s , t;
    cin >> n >> s >> t;

    vector<node*> vec;
    for(int i=0 ; i<n ; i++){
        node* temp = new node(i);
        vec.push_back(temp);
    }

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            if(j > i){
                int temp;
                cin >> temp;
                if(temp != 0)
                    vec[i]->add_transition(j,temp);
            }
            else{
                int temp;
                cin >> temp;
            }
        }
    }

    vector<int> path(vec.size());
    auto x = shortestPath(vec , s , path);

    int totaldist = x[t];

    cout << "Total Dist: " << totaldist << '\n';

    cout << "Path: \n";
    printPath(path , t , s);
    cout << t << endl;

    cout << endl;
}
