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

char* tabelaToString(tabela t){
    char final[500];
    final[0] = (char)t.id;
    final[1] = '#';
    for(unsigned int i = 0; i < t.grafo.size(); i++){
        for(unsigned int j = 0; j < t.grafo[i].size(); j++){
            int pos = 2 + j*(i+1);
            final[pos++] = t.grafo[i][j].ping;
            final[pos] = '-';
            strcat(final, t.grafo[i][j].ip);
        }
        final[t.grafo[i].size()] = ';';
    }

    return final;
}

#endif // STRUCTS_H
