#include <bits/stdc++.h>

using namespace std;

void firstTask(){

    int EMPTY_PLACE = -1;
    int FORBIDDEN_PLACE = -2;

    int m , n; cin >> m >> n;

    int empty_place_row, empty_place_col;

    vector<vector<int>> parking(m , vector<int>(n));

    vector<vector<bool>> used(m , vector<bool>(n));

    for(int i=0 ; i<m ; i++){
        for(int j=0 ; j<n ; j++){
            int temp;
            cin >> temp;
            parking[i][j] = temp;
            if(parking[i][j] == EMPTY_PLACE){
                empty_place_row = i;
                empty_place_col = j;
            }
            used[i][j] = false;
        }
    }

    int row , col;
    cin >> row >> col;
    row -= 1;
    col -= 1;

    vector<int> moveOrder(m * n);

    int moves = 0;

    bool check = true;

    while(check){
        if(row < 0 || row >= m || col < 0 || col >= n)
            check = false;
        else if(parking[row][col] == FORBIDDEN_PLACE)
            check = false;
        else if(used[row][col] == true)
            check = false;
        else if(row == empty_place_row && col == empty_place_col)
            break;
        else{
            used[row][col] = true;

            int car_number = parking[row][col];

            moveOrder[moves++] = parking[row][col];

            if(row > 0 && parking[row-1][col] == car_number) //above
                row -= 2;
            else if(row < m-1 && parking[row+1][col] == car_number) //below
                row += 2;
            else if(col > 0 && parking[row][col-1] == car_number) // left
                col -= 2;
            else
                col += 2; // right

        }
    }

    if(check == false)
        cout << "This Can't Be Done!" << endl;
    else{
        cout << moveOrder[moves - 1];
        for(int i=moves - 2 ; i>=0 ; i--){
            cout << ' ' << moveOrder[i];
        }
        cout << endl;
    }

    return;
}
