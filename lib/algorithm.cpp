//
// Created by Sebastian Pondo on 27.05.2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "algorithm.h"

using namespace std;

Queue::Queue ( int n )
{
    Heap = new Edge [ n ];
    hpos = 0;
}

Queue::~Queue( )
{
    delete [ ] Heap;
}

Edge Queue::front( )
{
    return Heap [ 0 ];
}

void Queue::push ( Edge e )
{
    int i, j;

    i = hpos++;
    j = ( i - 1 ) >> 1;

    while( i && ( Heap [ j ].weight > e.weight ) )
    {
        Heap [ i ] = Heap [ j ];
        i = j;
        j = ( i - 1 ) >> 1;
    }

    Heap [ i ] = e;
}

void Queue::pop( )
{
    int i, j;
    Edge e;

    if( hpos )
    {
        e = Heap [ --hpos ];

        i = 0;
        j = 1;

        while( j < hpos )
        {
            if( ( j + 1 < hpos ) && ( Heap [ j + 1 ].weight < Heap [ j ].weight ) ) j++;
            if( e.weight <= Heap [ j ].weight ) break;
            Heap [ i ] = Heap [ j ];
            i = j;
            j = ( j << 1 ) + 1;
        }

        Heap [ i ] = e;
    }
}

DSStruct::DSStruct ( int n )
{
    Z = new DSNode [ n ];
}

DSStruct::~DSStruct( )
{
    delete [ ] Z;
}

void DSStruct::MakeSet ( int v )
{
    Z [ v ].up   = v;
    Z [ v ].rank = 0;
}

int DSStruct::FindSet ( int v )
{
    if( Z [ v ].up != v ) Z [ v ].up = FindSet ( Z [ v ].up );
    return Z [ v ].up;
}

void DSStruct::UnionSets ( Edge e )
{
    int ru, rv;

    ru = FindSet ( e.v1 );
    rv = FindSet ( e.v2 );
    if( ru != rv )
    {
        if( Z [ ru ].rank > Z [ rv ].rank )
            Z [ rv ].up = ru;
        else
        {
            Z [ ru ].up = rv;
            if( Z [ ru ].rank == Z [ rv ].rank ) Z [ rv ].rank++;
        }
    }
}

MSTree::MSTree ( int n )
{
    int i;

    A = new TNode * [ n ];
    for( i = 0; i < n; i++ ) A [ i ] = NULL;
    Alen = n - 1;
    weight = 0;
}

MSTree::~MSTree( )
{
    int i;
    TNode *p, *r;

    for( i = 0; i <= Alen; i++ )
    {
        p = A [ i ];
        while( p )
        {
            r = p;
            p = p->next;
            delete r;
        }
    }

    delete [ ] A;
}

void MSTree::addEdge ( Edge e )
{
    TNode *p;

    weight += e.weight;
    p = new TNode;
    p->v = e.v2;
    p->weight = e.weight;
    p->next = A [ e.v1 ];
    A [ e.v1 ] = p;

    p = new TNode;
    p->v = e.v1;
    p->weight = e.weight;
    p->next = A [ e.v2 ];
    A [ e.v2 ] = p;
}

void MSTree::print( )
{
    int i;
    TNode *p;

    cout << endl;
    for( i = 0; i <= Alen; i++ )
    {
        cout << "vertex " << i << " - ";
        for( p = A [ i ]; p; p = p->next ) cout << p->v << ":" << p->weight << " ";
        cout << endl;
    }
    cout << endl << endl << "minimal spanning tree weight = " << weight << endl << endl;
}

TNode * MSTree::getAList ( int n )
{
    return A [ n ];
}

Stack::Stack( )
{
    S = nullptr;
}

Stack::~Stack( )
{
    while( S ) pop( );
}

bool Stack::empty (void )
{
    return !S;
}

int Stack::top (void )
{
    return S->v;
}

void Stack::push (int v )
{
    slistEl * e = new slistEl;
    e->v    = v;
    e->next = S;
    S = e;
}

void Stack::pop (void )
{
    if( S )
    {
        slistEl * e = S;
        S = S->next;
        delete e;
    }
}

Paths::Paths(string filename)
{
    this->filename = filename;
}

Paths::~Paths() = default;

void Paths::init()
{
    int m, i, j;
    ifstream file(filename);
    if (!file.is_open()) {
        throw "nie mozna otworzyc pliku";
    }

    bool first = true;
    string line;
    vector<Edge> numbers;
    while (getline(file, line)) {
        stringstream ss(line);
        if (first) {
            ss >> n;
            ss >> m;
            first = false;
        } else {
            Edge e;
            ss >> e.v1;
            ss >> e.v2;
            numbers.push_back(e);
        }
    }

    A = new char * [ n ];
    visited = new bool [ n ];

    for( i = 0; i < n; i++ )
        A [ i ] = new char [ n ];

    for ( i = 0; i < n; i++ )
    {
        visited [ i ] = false;
        for( j = 0; j < n; j++ ) A [ i ][ j ] = 0;
    }

    for( i = 0; i < m; i++ )
    {
        A [ numbers[i].v1 ][ numbers[i].v2 ] = 1;
    }
}

void Paths::end()
{
    int i;

    for ( i = 0; i < n; i++ ) delete A [ i ];
    delete [ ] A;
    delete [ ] visited;
}


DepthPaths::DepthPaths(string filename) : Paths(filename) {}

DepthPaths::~DepthPaths() = default;

void DepthPaths::dfs(int v)
{
    int i;

    visited [ v ] = true;
    result.push_back(v);

    for( i = 0; i < n; i++ )
        if( ( A [ v ][ i ] == 1 ) && !visited [ i ] ) dfs ( i );
}

std::vector<int> DepthPaths::path(int start)
{
    init();
    dfs ( start );
    end();
    return result;
}

BreathPaths::BreathPaths(string filename) : Paths(filename) {}

BreathPaths::~BreathPaths() = default;

void BreathPaths::bfs(int v)
{
    int i;
    slistEl *q, *head, *tail;

    q = new slistEl;
    q->next = NULL;
    q->v = v;
    head = tail = q;

    visited [ v ] = true;

    while( head )
    {
        v = head->v;

        q = head;
        head = head->next;
        if( !head ) tail = NULL;
        delete q;

        result.push_back(v);

        for( i = 0; i < n; i++ )
            if( ( A [ v ][ i ] == 1 ) && !visited [ i ] )
            {
                q = new slistEl;
                q->next = NULL;
                q->v = i;
                if( !tail ) head = q;
                else tail->next = q;
                tail = q;
                visited [ i ] = true;
            }
    }
}

std::vector<int> BreathPaths::path(int start)
{
    init();
    bfs ( start );
    end();
    return result;
}

MST::MST(string filename)
{
    this->filename = filename;
}

MST::~MST() = default;

vector<Edge> MST::init()
{
    ifstream file(this->filename);
    if (!file.is_open()) {
        throw "nie mozna otworzyc pliku";
    }

    bool first = true;
    string line;
    vector<Edge> numbers;
    while (getline(file, line)) {
        stringstream ss(line);
        if (first) {
            ss >> n;
            ss >> m;
            first = false;
        } else {
            Edge e;
            ss >> e.v1;
            ss >> e.v2;
            ss >> e.weight;
            numbers.push_back(e);
        }
    }

    return numbers;
}

PrimMST::PrimMST(string filename) : MST(filename) {}

PrimMST::~PrimMST() = default;

MSTree PrimMST::mst()
{
    Edge e;
    TNode * p;
    int i, v;

    vector<Edge> numbers = init();

    Queue Q ( m );
    MSTree T ( n );
    MSTree G ( n );
    bool * visited = new bool [ n ];

    for( i = 0; i < n; i++ )
        visited [ i ] = false;

    for( i = 0; i < m; i++ )
        G.addEdge ( numbers[i] );

    v = 0;
    visited [ v ] = true;

    for( i = 1; i < n; i++ )
    {
        for( p = G.getAList ( v ); p; p = p->next )
            if( !visited [ p->v ] )
            {
                e.v1 = v;
                e.v2 = p->v;
                e.weight = p->weight;
                Q.push ( e );
            }

        do
        {
            e = Q.front( );
            Q.pop( );
        } while( visited [ e.v2 ] );

        T.addEdge ( e );
        visited [ e.v2 ] = true;
        v = e.v2;
    }

    delete [ ] visited;

    return T;
}

KruskalMST::KruskalMST(string filename) : MST(filename) {}

KruskalMST::~KruskalMST() = default;

MSTree KruskalMST::mst()
{
    Edge e;
    int i;

    vector<Edge> numbers = init();

    DSStruct Z ( n );
    Queue Q ( m );
    MSTree T ( n );

    for( i = 0; i < n; i++ )
        Z.MakeSet ( i );

    for( i = 0; i < m; i++ )
        Q.push ( numbers[i] );

    for( i = 1; i < n; i++ )
    {
        do
        {
            e = Q.front( );
            Q.pop( );
        } while( Z.FindSet ( e.v1 ) == Z.FindSet ( e.v2 ) );
        T.addEdge ( e );
        Z.UnionSets ( e );
    }

    return T;
}

DijkstraSP::DijkstraSP(string filename)
{
    this->filename = filename;
}

DijkstraSP::~DijkstraSP() = default;

void DijkstraSP::sp()
{
    int i, j, m, n, v, u, w, x, y, sptr, *d, *p, *S;
    bool *QS;
    slistEl **graf;
    slistEl *pw, *rw;

    ifstream file(this->filename);
    if (!file.is_open()) {
        throw "nie mozna otworzyc pliku";
    }

    bool first = true;
    string line;
    vector<Edge> numbers;
    while (getline(file, line)) {
        stringstream ss(line);
        if (first) {
            ss >> v;
            ss >> n;
            ss >> m;
            first = false;
        } else {
            Edge e;
            ss >> e.v1;
            ss >> e.v2;
            ss >> e.weight;
            numbers.push_back(e);
        }
    }

    d = new int [ n ];
    p = new int [ n ];
    QS = new bool [ n ];
    graf = new slistEl * [ n ];
    S = new int [ n ];
    sptr = 0;

    for( i = 0; i < n; i++ )
    {
        d [ i ] = MAXINT;
        p [ i ] = -1;
        QS [ i ] = false;
        graf [ i ] = NULL;
    }

    for( i = 0; i < m; i++ )
    {
        pw = new slistEl;
        pw->v = numbers[i].v2;
        pw->w = numbers[i].weight;
        pw->next = graf [ numbers[i].v1 ];
        graf [ numbers[i].v1 ] = pw;
    }

    d [ v ] = 0;

    for( i = 0; i < n; i++ )
    {

        for( j = 0; QS [ j ]; j++ );
        for( u = j++; j < n; j++ )
            if( !QS [ j ] && ( d [ j ] < d [ u ] ) ) u = j;

        QS [ u ] = true;

        for( pw = graf [ u ]; pw; pw = pw->next )
            if( !QS [ pw->v ] && ( d [ pw->v ] > d [ u ] + pw->w ) )
            {
                d [ pw->v ] = d [ u ] + pw->w;
                p [ pw->v ] = u;
            }
    }

    for( i = 0; i < n; i++ )
    {
        cout << i << ": ";

        for( j = i; j > -1; j = p [ j ] ) S [ sptr++ ] = j;

        while( sptr ) cout << S [ --sptr ] << " ";

        cout << "$" << d [ i ] << endl;
    }

    delete [ ] d;
    delete [ ] p;
    delete [ ] QS;
    delete [ ] S;

    for( i = 0; i < n; i++ )
    {
        pw = graf [ i ];
        while( pw )
        {
            rw = pw;
            pw = pw->next;
            delete rw;
        }
    }

    delete [ ] graf;
}

BFordaSP::BFordaSP(string filename)
{
    this->filename = filename;
}

BFordaSP::~BFordaSP() = default;

void BFordaSP::sp()
{
    int i, v, x, y, w, sptr, *S;
    slistEl *rv, *pv;

    ifstream file(this->filename);
    if (!file.is_open()) {
        throw "nie mozna otworzyc pliku";
    }

    bool first = true;
    string line;
    vector<Edge> numbers;
    while (getline(file, line)) {
        stringstream ss(line);
        if (first) {
            ss >> v;
            ss >> n;
            ss >> m;
            first = false;
        } else {
            Edge e;
            ss >> e.v1;
            ss >> e.v2;
            ss >> e.weight;
            numbers.push_back(e);
        }
    }

    A = new slistEl * [ n ];
    d = new long long [ n ];
    p = new int [ n ];
    for( i = 0; i < n; i++ )
    {
        d [ i ] = MAXINT;
        p [ i ] = -1;
        A [ i ] = NULL;
    }

    for( i = 0; i < m; i++ )
    {
        pv = new slistEl;
        pv->v = numbers[i].v2;
        pv->w = numbers[i].weight;
        pv->next = A [ numbers[i].v1 ];
        A [ numbers[i].v1 ] = pv;
    }

    if( bf ( v ) )
    {
        S = new int [ n ];
        sptr = 0;

        for( i = 0; i < n; i++ )
        {
            cout << i << ": ";
            for( x = i;x != -1;x = p [ x ] )
                S [ sptr++ ] = x;

            while( sptr )
                cout << S [ --sptr ] << " ";

            cout << "$" << d [ i ] << endl;
        }
        delete [ ] S;
    }
    else cout << "negative cycle found!" << endl;

    for( i = 0; i < n; i++ )
    {
        pv = A [ i ];
        while( pv )
        {
            rv = pv;
            pv = pv->next;
            delete rv;
        }
    }

    delete [ ] A;
    delete [ ] d;
    delete [ ] p;

}

bool BFordaSP::bf(int v)
{
    int i, x;
    bool test;
    slistEl * pv;

    d [ v ] = 0;
    for( i = 1; i < n; i++ )
    {
        test = true;
        for( x = 0; x < n; x++ )
            for( pv = A [ x ]; pv; pv = pv->next )
                if( d [ pv->v ] > d [ x ] + pv->w )
                {
                    test = false;
                    d [ pv->v ] = d [ x ] + pv->w;
                    p [ pv->v ] = x;
                }
        if( test ) return true;
    }

    for( x = 0; x < n; x++ )
        for( pv = A [ x ];pv;pv = pv->next )
            if( d [ pv->v ] > d [ x ] + pv->w ) return false;

    return true;
}

Cycle::Cycle(string filename)
{
    this->filename = filename;
}

Cycle::~Cycle() = default;

bool Cycle::dfsFindCycle(slistEl **graf, int v, int w, Stack &S, bool *visited)
{
    int u;
    slistEl * p;

    visited [ w ] = true;
    S.push ( w );
    p = graf [ w ];
    while( p )
    {
        u = p->v;

        if( u == v ) return true;

        if( !visited [ u ] && dfsFindCycle ( graf, v, u, S, visited ) ) return true;

        p = p->next;
    }
    S.pop( );
    return false;
}

void Cycle::find()
{
    int n, m, i, j, v1, v2;
    slistEl * p, * r, ** A;
    bool * visited;
    Stack S, T;

    ifstream file(filename);
    if (!file.is_open()) {
        throw "nie mozna otworzyc pliku";
    }

    bool first = true;
    string line;
    vector<Edge> numbers;
    while (getline(file, line)) {
        stringstream ss(line);
        if (first) {
            ss >> n;
            ss >> m;
            first = false;
        } else {
            Edge e;
            ss >> e.v1;
            ss >> e.v2;
            numbers.push_back(e);
        }
    }

    A = new slistEl * [ n ];

    for( i = 0; i < n; i++ ) A [ i ] = NULL;

    for( i = 0; i < m; i++ )
    {
        p = new slistEl;
        p->v = numbers[i].v2;
        p->next = A [ numbers[i].v1 ];
        A [ numbers[i].v1 ] = p;
    }

    cout << endl;

    visited = new bool [ n ];

    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
            visited [ j ] = false;

        if( !dfsFindCycle ( A, i, i, S, visited ) )
            cout << i << " - no cycle\n";
        else
        {
            T.push ( i );
            while( !S.empty( ) )
            {
                T.push ( S.top( ) ); S.pop( );
            }

            while( !T.empty( ) )  // Wyświetlamy ścieżkę
            {
                cout << T.top( ) << " "; T.pop( );
            }
            cout << endl;
        }
    }

    delete [ ] visited;

    for( i = 0; i < n; i++ )
    {
        p = A [ i ];
        while( p )
        {
            r = p;
            p = p->next;
            delete r;
        }
    }

    delete [ ] A;
}
