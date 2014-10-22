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
int serverSocket[10];     // Onde me conecta
socklen_t sockLen;
char messageTh[50];

//Thread para receber mensagens
void *serverResp(void* s){
    int socket = (int)s;

    receiveMessage(socket, messageTh, sizeof(messageTh));
    /// Mensagem de ping
    if(strcmp(messageTh, "Ping") ){
        messageTh[0] = rand() % 150 + 1;
        sendMessage(socket, messageTh, sizeof(messageTh));
    }
    tabela t;
    recv(socket, (char*)&t, sizeof(tabela), 0);
    /// Mensagem de tabela
    if(messageTh[1] == '#'){
        //TODO: Atualizar tabela
    }

    pthread_exit(NULL);
}

//Conectar este ponto aos outros
void iniciarCon(){
    for(int i = 0; i < 10; i++){
        mainSocket = openConnection(5000+i,1);
        serverSocket[i] = acceptConnection(mainSocket, sockLen);
    }
    cout << "Quantas conexoes nesse ponto? ";
    int numCon;
    cin >> numCon;

    pthread_t th[numCon];

    clientSocket.resize(numCon);
    vector<ponto> aux;
    for(int i = 0; i < numCon; i++){
        ponto temp;
        cout << "IP alvo: ";
        cin >> temp.ip;
        aux.push_back(temp);

        clientSocket[i] = tryConnection(temp.ip, PORT, 0);
        pthread_create(&th[i], NULL, &serverResp, (void*)clientSocket[i]);
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
    //char *msg = tabelaToString(table);
    vector<ponto> aux = table.grafo.back();

    for(unsigned int i = 0; i < aux.size(); i++){
        cout << "Enviou tabela para: " << aux[i].ip << endl;
        send(clientSocket[i], (char*)&table, sizeof(table),0);
        sleep(1);
    }
}

int main(){
    iniciarCon();
    tunnel();
    enviarTabela();
    //djikstra();
    //enviarMsg(dst);
}
