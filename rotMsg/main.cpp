#include <bits/stdc++.h>
#include "communication.h"
#include "yggdrasil.h"

using namespace std;

#define PORT 50000

///FIXME: respTunnel, nao sei como fazer

///Variaveis Globais
tabela table;
int mainSocket;
vector<int> fdSocket;
int socketOpen[10];
socklen_t sockLen;
char messageTh[50];

//Thread para responder Tunnel
void *respTunnel(void *socket){

    receiveMessage((int)socket, messageTh, sizeof(messageTh));
    if(strcmp(messageTh, "Ping") ){
        messageTh[0] = rand() % 150 + 1;
        sendMessage((int)socket, messageTh, sizeof(messageTh));
    }
    pthread_exit(NULL);
}


//Conectar este ponto aos outros
void iniciarCon(){
    for(int i = 0; i < 10; i++){
        mainSocket = openConnection(PORT+i,0);
        socketOpen[i] = acceptConnection(mainSocket, sockLen);
    }
    cout << "Quantas conexoes nesse ponto? ";
    int numCon;
    cin >> numCon;

    pthread_t th[numCon];

    fdSocket.resize(numCon);
    vector<ponto> aux;
    for(int i = 0; i < numCon; i++){
        ponto temp;
        cout << "IP alvo: ";
        cin >> temp.ip;
        aux.push_back(temp);

        fdSocket[i] = tryConnection(temp.ip, PORT, 0);
        pthread_create(&th, NULL, &respTunnel, NULL, (void*)fdSocket[i]);
    }
    table.id = 0;
    table.grafo.push_back(aux);

    cout << "Conexao estabelecida" << endl;
}

//Verificar Latencia
void tunnel(){
    cout << "--- Verificando Latencia das conexoes..." << endl;
    unsigned int p = table.grafo.size()-1;
    char message[10];
    for(int i = 0; i < table.grafo[p]; i++){
        cout << "Disparando pacotes em " << table.grafo[p][i].ip << endl;
        sleep(1);
        message = "Ping";
        sendMessage(fdSocket[i], message, sizeof(message));
        receiveMessage(fdSocket[i], message, sizeof(message));
        cout << "  time: " << (int) message[0] << " ms" << endl;
        table.grafo[p][i].ping = (int)message[0];
    }
    cout << "--- Done ---" << endl;
}

int main()
{
    iniciarCon();
    tunnel();
    pthread_join(th, NULL);
}

