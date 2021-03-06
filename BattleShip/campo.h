#ifndef CAMPO_H
#define CAMPO_H

#include <bits/stdc++.h>

/* Peças
/* 1 porta aviões (5 blocos -  forma de T)  : P
/* 3 submarinos (1 unidade)                 : S
/* 2 barcos tipo A (2 unidades)             : A
/* 2 barcos tipo B (3 unidades)             : B
*/

class Campo
{
private:
    char mat[11][11][2];
    bool dono;
    int hitCont;
    bool desistencia;
public:
    Campo(bool);
    void posicionar();
    int rcvTiro(int x, int y);
    void rcvTiro(int x, int y, bool hit);
    void showCampo();
    bool isGameOver();
    void surrender();
    std::pair<int,int> atirar();
};

#endif // CAMPO_H
