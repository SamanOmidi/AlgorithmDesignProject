#include <bits/stdc++.h>
#include "FirstTask.cpp"
#include "SecondTaskA.cpp"
#include "ThirdTask.cpp"

using namespace std;


int main(){

    bool program = true;

    int action;

    while(program){
        cout << "---------------------" << endl;
        cout << "1. First Task\n"
             << "2. Second Task A\n"
             << "3. Second Task B\n"
             << "4. Third Task\n"
             << "0. Exit\n";
        cout << "Enter Your Action: ";
        cin >> action;
        switch(action){
        case 1:
            firstTask();
            break;

        case 2:
            secondTaskA();
            break;

        case 3:
            break;

        case 4:
            thirdTask();
            break;

        case 0:
            program = false;
            break;

        default:
            break;
        }
    }

    return 0;
}
