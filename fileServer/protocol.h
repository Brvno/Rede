#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <bits/stdc++.h>
#include "communication.h"


#define PORT 50000


struct protocol{
    int tipo;       // Podendo ser de 3 tipos. Post, Ask e Send
    char nome[128]; // Nome do arquivo
    int size;       // Tamanho do Arquivo
    char* arquivo;  // Dados do arquivo
    int checkSum;   // verificacao
};

struct File{
    char* arquivo;
    char nome[128];
};


#endif // PROTOCOL_H
