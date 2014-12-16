#ifndef CLIENT_H
#define CLIENT_H

#include <bits/stdc++.h>
#include "server.h"

using namespace std;

//Variaveis Globais
int socketClient;
vector<File> cacheF;

//Funcoes
void client(char*);
int checkFile(char*);
char* protocolar(File, int);



#endif // CLIENT_H
