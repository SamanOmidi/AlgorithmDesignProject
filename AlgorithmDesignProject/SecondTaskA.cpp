#include <bits/stdc++.h>
using namespace std;

#define INF 99999

vector<vector<int>> totalDist;

stack<int> ans;

vector<vector<set<int>>> floydWarshall(int n , vector<pair<pair<int,int>,int>> vec)
{
    vector<vector<int>> cost(n , vector<int>(n));

    for(int i=0 ; i<n ; i++)
        for(int j=0 ; j<n ; j++){
            if(i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = INF;
        }

    vector<vector<set<int>>> next_node(n , vector<set<int>>(n));

    for(unsigned int i=0 ; i<vec.size() ; i++){
        if(vec[i].second < cost[vec[i].first.first][vec[i].first.second]){
            cost[vec[i].first.first][vec[i].first.second] = vec[i].second;
            next_node[vec[i].first.first][vec[i].first.second].insert(vec[i].first.second);
        }
        else if(vec[i].second == cost[vec[i].first.first][vec[i].first.second] && vec[i].second < INF){
            next_node[vec[i].first.first][vec[i].first.second].insert(vec[i].first.second);
        }
    }

    for(int k=0 ; k<n ; k++){
        for(int i=0 ; i<n ; i++){
            for(int j=0 ; j<n ; j++){
                int cost_ik_kj = cost[i][k] + cost[k][j];
                if(cost_ik_kj < cost[i][j]){
                    cost[i][j] = cost_ik_kj;
                    next_node[i][j] = next_node[i][k];
                }
                else if(cost_ik_kj == cost[i][j] && cost_ik_kj < INF){
                    next_node[i][j].insert(next_node[i][k].begin(),next_node[i][k].end());
                }
            }
        }
    }

    totalDist = cost;

    return next_node;

}

int start;

void print_paths(vector<vector<set<int>>> next_node, int i , int j){
    if(next_node[i][j].empty()){
        if(i == j){
            string s;
            stack<int> temp = ans;
            if(temp.size() == 1){
                cout << start << " -> " << temp.top();
                temp.pop();
                cout << endl;
            }
            else{
                while(!temp.empty()){
                    s += to_string(temp.top());
                    temp.pop();
                }
                reverse(s.begin() , s.end());
                for(unsigned int k=0 ; k<s.size() ; k++){
                    if(k == 0){
                        cout << start << " -> " << s[k] << " -> ";
                    }
                    else if(k == s.size() - 1){
                        cout << s[k];
                    }
                    else{
                        cout << s[k] << " -> ";
                    }
                }
                cout << endl;
            }
        }

    }
    else{
        for(auto k : next_node[i][j]){
            ans.push(k);
            print_paths(next_node , k , j);
            ans.pop();
        }
    }
}


void secondTaskA()
{
    //number of u v e give to program
    int m;
    cin >> m;

    vector<pair<pair<int,int>,int>> vec;

    //enter u(start node) v(end node) e(weight)
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

    //enter number of nodes in the graph
    int n;
    cin >> n;


    //doing floydwarshall on the graph
    /*
     * we have global totalDist variable that saves the all-shortest pairs in
     * the graph using floydwarshall algorithm
     *
     * we also have next_node vector for each node from 0 to n that have a set,
     * that set shows the path we want to reach to destination
     * we used set because we want to get all shortest paths possible from start to end
     */
    vector<vector<set<int>>> next_node = floydWarshall(n , vec);

    //entering start and end node
    int end;
    cin >> start >> end;

    //printing MIN_LENGTH for start -> end using totalDist vector we got from
    //floydwarshall algorithm
    cout << "MIN LENGTH = " << totalDist[start][end] << endl;

    //printing all possible paths from start -> end
    print_paths(next_node, start, end);

}

