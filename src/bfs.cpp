//
// Created by Sebastian Pondo on 27.05.2023.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "algorithm.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "brak nazwy pliku z danymi" << endl;
        return 1;
    }

    if (argc < 3)
    {
        cout << "brak pozycji start" << endl;
        return 1;
    }

    try {

        int start = stoi(argv[2]);
        BreathPaths breathPaths(argv[1]);

        for(int v : breathPaths.path(start))
            cout << v << setw ( 3 );

    } catch (const char* msg) {
        cout << msg << endl;
        return 1;
    } catch (...) {
        cout << "niepoprawne parametry" << endl;
        return 1;
    }

    return 0;
}