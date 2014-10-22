#include <bits/stdc++.h>
#include "communication.h"
#include "yggdrasil.h"

using namespace std;

#define PORT 50000

///FIXME: respTunnel, nao sei como fazer

///Variaveis Globais
tabela table;
int mainSocket;
vector<int> clientSocket; // Onde este ponto esta conectado
int serverSocket[10];     // Onde me conecatam
socklen_t sockLen;
char messageTh[50];

//Thread para receber mensagens
void *serverResp(void*){
    while(true){
        for(int i = 0; i < 10; i++){
            receiveMessage(serverSocket[i], messageTh, sizeof(messageTh));
            /// Mensagem de ping
            if(strcmp(messageTh, "Ping") ){
                messageTh[0] = rand() % 150 + 1;
                sendMessage(serverSocket[i], messageTh, sizeof(messageTh));
            }
            /// Mensagem de tabela
            if(messageTh[0] == '#'){
                //TODO: Atualizar tabela
            }
        }
    }
    pthread_exit(NULL);
}

//Conectar este ponto aos outros
void iniciarCon(){
    for(int i = 0; i < 10; i++){
        mainSocket = openConnection(PORT+i,1);
        serverSocket[i] = acceptConnection(mainSocket, sockLen);
    }
    cout << "Quantas conexoes nesse ponto? ";
    int numCon;
    cin >> numCon;


    clientSocket.resize(numCon);
    vector<ponto> aux;
    for(int i = 0; i < numCon; i++){
        ponto temp;
        cout << "IP alvo: ";
        cin >> temp.ip;
        aux.push_back(temp);

        clientSocket[i] = tryConnection(temp.ip, PORT, 0);
    }
    table.id = 0;
    table.grafo.push_back(aux);
    pthread_t th;
    pthread_create(&th, NULL, &serverResp, NULL);

    cout << "Conexao estabelecida" << endl;
}

//Verificar Latencia
void tunnel(){
    cout << "--- Verificando Latencia das conexoes..." << endl;
    unsigned int p = table.grafo.size()-1;
    char message[10];
    for(unsigned int i = 0; i < table.grafo[p].size(); i++){
        cout << "Disparando pacotes em " << table.grafo[p][i].ip << endl;
        sleep(1);
        strcpy(message ,"Ping");
        sendMessage(clientSocket[i], message, sizeof(message));
        receiveMessage(clientSocket[i], message, sizeof(message));
        cout << "  time: " << (int) message[0] << " ms" << endl;
        table.grafo[p][i].ping = (int)message[0];
    }
    cout << "--- Done ---" << endl;
}

//Enviar Tabela para os adj
void enviarTabela(){
/// FIXME: Como saber qual eh o indice deste pc? Ultimo(?)
/// RESP: Quando for concatenar na nova tabela, manter a ultima linha.
    char *msg = tabelaToString(table);
    vector<ponto> aux = table.grafo.back();

    for(unsigned int i = 0; i < aux.size(); i++){
        cout << "Enviou tabela para: " << aux[i].ip << endl;
        sendMessage(clientSocket[i], msg, sizeof(msg));
        sleep(1);
    }
}

int main(){
    iniciarCon();
    tunnel();
    //pthread_join(th, NULL);
    enviarTabela();
    //djikstra();
    //enviarMsg(dst);
}
