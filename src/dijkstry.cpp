//
// Created by Sebastian Pondo on 27.05.2023.
//

#include <iostream>
#include "algorithm.h"

using namespace std;



int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "brak nazwy pliku z danymi" << endl;
        return 1;
    }

    try {

        DijkstraSP dijkstraSp(argv[1]);
        dijkstraSp.sp();

    } catch (const char* msg) {
        cout << msg << endl;
        return 1;
    } catch (...) {
        cout << "niepoprawne parametry" << endl;
        return 1;
    }

    return 0;
}