#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <bits/stdc++.h>
#include "communication.h"

using namespace std;


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

//Cria Mensagem de acordo com o protocolo
char* protocolar(File file, int tipo){
    protocol *prot;
    *prot->nome = *file.nome;
    prot->size = sizeof(file.arquivo);
    prot->tipo = tipo;

    return (char*)prot;
}

///Verificar a existencia do arquivo
int checkFile(char* nome, vector<File> cacheF){
    for(unsigned int i = 0; i < cacheF.size(); i++)
        if(cacheF[i].nome == nome){
            cout << nome << " encontrado na cache" << endl;
            return i;
        }

    cout << nome << " nao esta na cache" << endl;
    //TODO: Ler arquivo e colocar em arquivosCache
    return cacheF.size();

    // Arquivo nao existente
    cout << nome <<  " nao existe" << endl;
    return false;
}

#endif // PROTOCOL_H
