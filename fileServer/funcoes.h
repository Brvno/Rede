#include <bits/stdc++.h>
#include "protocol.h"

using namespace std;

///////// --------------------------- Headers ------------------------------------  //
                                                                                    //
/// ---------------------- CLIENT ------------------------------------------------  //
// Variaveis Globais                                                                //
int socketClient;                                                                   //
vector<File> cacheF;                                                                //
                                                                                    //
// Funcoes                                                                          //
void client(char*);                                                                 //
                                                                                    //
/// ---------------------- SERVER -----------------------------------------------   //
// Variaveis Globais                                                                //
vector<int> sockets;                                                                //
int mainSocket;                                                                     //
socklen_t sockLen;                                                                  //
                                                     //
                                                                                    //
// Funcoes                                                                          //
void* threadServidor(void* socket);                                                 //
void servidor();                                                                    //
                                                                                    //
///////// -----------------------------------------------------------------------   //

/// ---------------------- CLIENT ------------------------------------- ////

void client(char* IP){
    cout << IP << endl;
    int fdSocket = tryConnection(IP, PORT, 0);
//    File aux;
//    strcpy(aux.nome, "teste");

//    cacheF.push_back(aux);

    while(true){
        cout << "[1]Fazer download" << endl;
        cout << "[2]Fazer upload" << endl;
        int x;
        cin >> x;
        if(x == 2){
            cout << "Qual arquivo?" << endl;
            char nome[128];

            cin >> nome;

            fstream file;

            file.open(nome, ios_base::in);
            File aux;
            char gh[1];

            protocol* prt = (protocol*)malloc(sizeof(protocol));
            strcpy(prt->nome, nome);
            prt->tipo = x;

            sendMessage(fdSocket,(char*)prt, sizeof(protocol));

            for(int i = 0; file.get(gh[0]); i++)
                sendMessage(fdSocket,gh, sizeof(char));
//            gh[0] = EOF;
//            sendMessage(fdSocket,gh, sizeof(char));

            file.close();
            cout << "Enviado para Server" << endl;
        }
        else if(x == 1){
            cout << "Qual arquivo?" << endl;
            char* nome;
            cin >> nome;
            protocol *prot = (protocol*)malloc(sizeof(protocol));
            strcpy(prot->nome,nome);
            prot->tipo = x;
            sendMessage(fdSocket,(char*)prot, sizeof(protocol));

            fstream file;
            file.open(nome, ios_base::out);
            char message[1];
            while(1){
                receiveMessage(fdSocket, message, sizeof(char));
                cout << message[0];
                file.put(message[0]);
                if(message[0] == EOF)
                    break;
            }
            file.close();
        }
    }
}


/// ---------------------- SERVER ------------------------------------- ////

//Thread que ficara rodando no servidor
void* threadServidor(void* socket){
    int fdSocket = (int)socket;
    char* message = (char*)malloc(sizeof(protocol));
    protocol *requisit = (protocol*)malloc(sizeof(protocol));
    //vector<File> arquivosCache;

    cout << "CONECTADO O SOCKET " << fdSocket << endl;
    while(true){
        cout << "Esperando Mensagem" << endl;
        receiveMessage(fdSocket,message,sizeof(protocol));
        requisit = (protocol*)message;
        cout << "Mensagem Recebida: " << requisit->nome << endl;
        //Verificar msg
        if(requisit->tipo > 3)
            cout << "Mensagem em formato errado" << endl;
        //Upload
        else if(requisit->tipo == 2) {
            fstream file;
            file.open(requisit->nome, ios_base::out);
            while(1){
                receiveMessage(fdSocket, message, 1);
                cout << message[0];
                file.put(message[0]);
                if(message[0] == EOF)
                    break;
            }
            file.close();

        }
        //Download
        else if(requisit->tipo == 1) {
            fstream file;

            file.open(requisit->nome, ios_base::in);
            File aux;
            char gh[1];

            for(int i = 0; file.get(gh[0]); i++)
                sendMessage(fdSocket,gh, sizeof(char));

        }
    }
}


void servidor(){
    mainSocket = openConnection(PORT, 0);

    //Abertura de sockets para os clientes
    cout << "Quantos clientes?" << endl;
    int num;
    cin >> num;
    sockets.resize(num);
    pthread_t thServer[num];
    sockaddr_in socketAddr;
    sockLen = sizeof(socketAddr);

    for(int i = 0; i < num; i++){
        sockets[i] = acceptConnection(mainSocket, sockLen);
        //threadServidor((void*)sockets[i]);
        pthread_create(&thServer[i], NULL, &threadServidor, (void*)sockets[i]);
    }
    for(int i = 0; i < num; i++)
        pthread_join(thServer[i], NULL);

}
