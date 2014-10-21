#ifndef STRUCTS_H
#define STRUCTS_H

#include<bits/stdc++.h>
using namespace std;

struct ponto{
    char ip[20];
    int ping;
};

struct tabela{
   vector< vector<ponto> > grafo;
   int id;
};


#endif // STRUCTS_H
