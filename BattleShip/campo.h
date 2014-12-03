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
public:
    Campo(bool);
    void posicionar();
    char* atirar(int x, int y);
    void showCampo();
    bool isGameOver();
};

#endif // CAMPO_H
