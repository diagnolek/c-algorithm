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

int bfsTest()
{
    string filename = "bfs_dane.txt";
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "nie mozna otworzyc pliku." << endl;
        return 1;
    }

    vector<edge> data = {
            {14, 21},
            {0, 1},
            {0, 2},
            {0, 8},
            {1, 4},
            {1, 5},
            {1, 7},
            {2, 9},
            {3, 0},
            {3, 10},
            {3, 11},
            {4, 13},
            {5, 6},
            {5, 7},
            {5, 13},
            {7, 8},
            {8, 9},
            {10, 9},
            {10, 11},
            {12, 0},
            {12, 3},
            {13, 12}
    };

    vector<int> check = {0,  1,  2,  8,  4,  5,  7,  9, 13,  6, 12,  3, 10, 11};

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i].v1 << " " << data[i].v2 << endl;
    }

    BreathPaths breathPaths(filename);

    if (check == breathPaths.path(0))
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