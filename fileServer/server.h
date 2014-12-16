#ifndef SERVER_H
#define SERVER_H

#include <bits/stdc++.h>
#include <pthread.h>
#include "protocol.h"

using namespace std;

//Variaveis Globais
vector<int> sockets;
int mainSocket;
socklen_t sockLen;
vector<File> arquivosCache;

///Funcoes
int checkFile(char* nome);
char* protocolar(File file, int tipo);
void* threadServidor(void* socket);
void servidor();

#endif // SERVER_H
