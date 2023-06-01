//
// Created by Sebastian Pondo on 01.06.2023.
//

#include <iostream>

using namespace std;

int dfsTest();
int bfsTest();

int main(int argc, char *argv[])
{

    if (argc < 2) {
        cout << "brak parametru" << endl;
    }

    string param = string(argv[1]);

    if (param == string ("dfs"))
    {
        if (dfsTest() > 0) {
            cout << "failed dsf";
            return 1;
        }
    }
    else if (param == string ("bfs"))
    {
        if (bfsTest() > 0) {
            cout << "failed bsf";
            return 1;
        }
    }

    return 0;
}