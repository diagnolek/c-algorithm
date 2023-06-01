//
// Created by Sebastian Pondo on 27.05.2023.
//

#ifndef C_ALGORITHM_ALGORITHM_H
#define C_ALGORITHM_ALGORITHM_H

#include <vector>
#include <string>

using namespace std;

struct Edge
{
    int v1, v2, weight;
};

class Queue
{
private:
    Edge * Heap;
    int hpos;
public:
    Queue ( int n );
    ~Queue( );
    Edge front( );
    void push ( Edge e );
    void pop( );
};

struct DSNode
{
    int up, rank;
};

class DSStruct
{
private:
    DSNode * Z;
public:
    DSStruct ( int n );
    ~DSStruct( );
    void MakeSet ( int v );
    int FindSet ( int v );
    void UnionSets ( Edge e );
};

struct TNode
{
    TNode * next;
    int v, weight;
};

class MSTree
{
private:
    TNode ** A;
    int Alen;
    int weight;
public:
    MSTree ( int n );
    ~MSTree( );
    void addEdge ( Edge e );
    TNode * getAList ( int n );
    void print( );
};

struct slistEl
{
    slistEl * next;
    int v, w;
};

class Stack
{
private:
    slistEl * S;

public:
    Stack( );
    ~Stack( );
    bool empty ( void );
    int  top ( void );
    void push ( int v );
    void pop ( void );
};

class Paths
{
protected:
    string filename;
    int n;
    char ** A;
    bool * visited;
    std::vector<int> result;
    void init();
    void end();
public:
    Paths(string filename);
    ~Paths();
    virtual std::vector<int> path(int start) = 0;
};

class DepthPaths : Paths
{
private:
    void dfs(int v);
public:
    DepthPaths(string filename);
    ~DepthPaths();
    std::vector<int> path(int start) override;
};

class BreathPaths : Paths
{
private:
    void bfs(int v);
public:
    BreathPaths(string filename);
    ~BreathPaths();
    std::vector<int> path(int start) override;
};

class MST
{
protected:
    string filename;
    int n, m;
    vector<Edge> init();
public:
    MST(string filename);
    ~MST();
    virtual MSTree mst() = 0;

};

class PrimMST : MST
{
public:
    PrimMST(string filename);
    ~PrimMST();
    MSTree mst() override;
};

class KruskalMST : MST
{
public:
    KruskalMST(string filename);
    ~KruskalMST();
    MSTree mst() override;
};

class DijkstraSP
{
private:
    string filename;
    const int MAXINT = 2147483647;
public:
    DijkstraSP(string filename);
    ~DijkstraSP();
    void sp();
};

class BFordaSP
{
private:
    string filename;
    const int MAXINT = 2147483647;
    int n, m;
    slistEl ** A;
    long long * d;
    int * p;
    bool bf(int v);
public:
    BFordaSP(string filename);
    ~BFordaSP();
    void sp();
};

class Cycle
{
private:
    string filename;
    bool dfsFindCycle(slistEl ** graf, int v, int w, Stack & S, bool * visited);
public:
    Cycle(string filename);
    ~Cycle();
    void find();
};


#endif //C_ALGORITHM_ALGORITHM_H
