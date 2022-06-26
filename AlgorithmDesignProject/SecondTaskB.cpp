#include <bits/stdc++.h>
using namespace std;


#define INF 99999


vector<vector<int>> floydWarshall2(int n , vector<pair<pair<int,int>,int>> vec)
{
    vector<vector<int>> cost(n , vector<int>(n));

    for(int i=0 ; i<n ; i++)
        for(int j=0 ; j<n ; j++){
            if(i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = INF;
        }


    for(unsigned int i=0 ; i<vec.size() ; i++){
        if(vec[i].second < cost[vec[i].first.first][vec[i].first.second]){
            cost[vec[i].first.first][vec[i].first.second] = vec[i].second;
            cost[vec[i].first.second][vec[i].first.first] = vec[i].second;
        }
    }

    for(int k=0 ; k<n ; k++){
        for(int i=0 ; i<n ; i++){
            for(int j=0 ; j<n ; j++){
                int cost_ik_kj = cost[i][k] + cost[k][j];
                if(cost_ik_kj < cost[i][j]){
                    cost[i][j] = cost_ik_kj;
                    cost[j][i] = cost_ik_kj;
                }
            }
        }
    }

    return cost;

}

int MIN_COST = 0;


int least(int c , vector<int> completed , vector<vector<int>> new_graph)
{
    int nc=999;
    int min=999,kmin;

    for(unsigned int i=0 ; i<new_graph.size() ; i++)
    {
        if((new_graph[c][i]!=0)&&(completed[i]==0))
            if(new_graph[c][i]+new_graph[i][c] < min)
            {
                min=new_graph[i][c]+new_graph[c][i];
                kmin=new_graph[c][i];
                nc=i;
            }
    }

    if(min!=999)
        MIN_COST+=kmin;

    return nc;
}

void mincost(int city , vector<int> completed , vector<vector<int>> new_graph)
{
    int ncity;

    completed[city]=1;

    cout<<city+1<<"--->";
    ncity=least(city , completed , new_graph);

    if(ncity==999)
    {
        ncity=0;
        cout<<ncity+1;
        MIN_COST += new_graph[city][ncity];

        return;
    }

    mincost(ncity, completed , new_graph);
}

void secondTaskB()
{

    int m;
    cin >> m;

    vector<pair<pair<int,int>,int>> vec;

    for(int i=0 ; i<m ; i++){
        int u , v , e;
        cin >> u >> v >> e;

        pair<pair<int,int>,int> p;

        pair<int,int> temp(u, v);
        p.first = temp;

        p.second = e;

        vec.push_back(p);
    }

    //int n = 4;
    int n;
    cin >> n;

    vector<vector<int>> ans = floydWarshall2(n , vec);

    cout << "Enter Starting Point: ";
    int start;
    cin >> start;

    cout << "Enter Number Of Must Visit Nodes: ";
    int number;
    cin >> number;
    cout << "Enter Must Visit Nodes: ";
    vector<int> mustVisit;
    mustVisit.push_back(start);
    for(int i=0 ; i<number ; i++){
        int temp;
        cin >> temp;
        mustVisit.push_back(temp);
    }

    vector<vector<int>> new_graph(mustVisit.size(), vector<int>(mustVisit.size()));

    int new_graph_size = new_graph.size();

    for(int i=0 ; i<new_graph_size ; i++){
        for(int j=0 ; j<new_graph_size ; j++){
            if(i == j)
                new_graph[i][j] = 0;
            else{
                new_graph[i][j] = ans[mustVisit[i]][mustVisit[j]];
                new_graph[j][i] = ans[mustVisit[i]][mustVisit[j]];
            }
        }
    }

    for(int i=0 ; i<new_graph_size ; i++){
        for(int j=0 ; j<new_graph_size ; j++){
            cout << new_graph[i][j] << ' ';
        }
        cout << endl;
    }

    vector<int> completed(new_graph_size);

    cout<<"\n\nThe Path is:\n";
    mincost(0 , completed , new_graph); //passing 0 because starting vertex

    cout<<"\n\nMinimum cost is "<<MIN_COST << endl;

}

