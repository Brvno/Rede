#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <bits/stdc++.h>

using namespace std;

class Protocol
{
private:
    int tipo;       // Podendo ser de 3. Post, Ask e Send
    string nome;    // Nome do arquivo
    int size;       // Tamanho do Arquivo
    char* arquivo;  // Dados do arquivo
    int checkSum;   // verificacao
public:
    Protocol();
    char* byterizar();
    int checkSum(char*);
};

#endif // PROTOCOL_H
