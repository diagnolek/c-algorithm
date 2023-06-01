//
// Created by Sebastian Pondo on 29.05.2023.
//

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "algorithm.h"

using namespace std;

struct edge {
    int v1;
    int v2;
};

int dfsTest()
{
    string filename = "dfs_dane.txt";
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "nie mozna otworzyc pliku." << endl;
        return 1;
    }

    vector<edge> data = {
            {6, 9},
            {0, 1},
            {0, 5},
            {5, 2},
            {5, 1},
            {4, 1},
            {4, 5},
            {3, 4},
            {2, 1},
            {2, 3}
    };

    vector<int> check = {0,1,5,2,3,4};

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i].v1 << " " << data[i].v2 << endl;
    }

    DepthPaths depthPaths(filename);

    if (check == depthPaths.path(0))
    {
        remove(filename.c_str());
        return 0;
    }
    else
    {
        remove(filename.c_str());
        return 1;
    }
}