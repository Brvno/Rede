#include <bits/stdc++.h>
#include "communication.h"
#include <pthread.h>

using namespace std;

#define PORT 50000
#define IP "localhost"
#define TIME_OUT 3

//Globals Gambiarras
int fdSocket;
char message[1];
int janela;
bool confirmacao[105];
bool erro = false;
int inicio=1;
char msgs[1000][1];

/// Client Side
/// Recebe mensagem e a confirma. E simula falha
void receiveFrame(){

    do {
        receiveMessage(fdSocket, message, sizeof(message));
        if(rand() % 20 > 3){
            cout << "Recebeu: " << (int)message[0] << endl;
            sendMessage(fdSocket, message, sizeof(message));
        }
        else {
            cout << "Falha!" << endl;
        }
        sleep(1);
    } while(message[0] != '#');

    cout << " -------- Acabou Frames --------" << endl;
    sleep(1);
}


//Thread para receber message
void *th_rcvMsg(void *a){
    receiveMessage(fdSocket, message, sizeof(message));
    pthread_exit(NULL);
}

//Confirmacao de Frame
void *confirmFrame(void * i){
    int t = 0;
    char *m = (char*)i;
    int cogumelo = inicio;
    pthread_t th;
    do {
        pthread_create(&th, NULL, &th_rcvMsg, NULL);
        t++;
        cout << "                   Contador Tempo: " << t << endl;
        sleep(1);

        if(message[0] == m[0])
        {
            t=0;
            cout << "Confirmado: " << (int)m[0] << endl;
            inicio++;
            m[0]++;
        }

    } while( t < TIME_OUT);
    if(-cogumelo + inicio != janela)
        erro = true;

    pthread_exit(NULL);
}

/// Server Side
/// Utilizado para

void sendFrame(){
    pthread_t thread;

    int intervalo=rand()%100+10;
    janela = 5;
    erro = false;
    cout << "Janela Inicial: " << janela << endl;
    for(int i = 1; i < intervalo; i++)
        msgs[i][0] = i;

    inicio = 1;
    for(int i = 1; i < intervalo-janela; i++){

        pthread_create(&thread, NULL, &confirmFrame, msgs[i]);
        //Envia quadros da janela atual
        for(int j = i; j < janela+i; j++){
            sendMessage(fdSocket, msgs[j], sizeof(msgs[j]));
            cout << "Enviou: " << (int)msgs[j][0] << endl;
            sleep(1);
        }

        pthread_join(thread,NULL);
        ///Aumento da janela
        erro?   janela-- :
                janela++;
        erro = false;
        if(janela < 1) janela = 1;
        cout << "Nova janela: " << janela << endl;
        sleep(1);
        i=inicio-1;
    }

    cout << " -------- Acabou Intervalo --------" << endl;
}

int main(){
    int mainSocket;
    struct sockaddr_in socketAddr;
    socklen_t sockLen;

    bool server;
    cout << "Server(1) | Client(0): ";
    cin >> server;

    if(server){
        mainSocket = openConnection(PORT, 0);
        fdSocket = acceptConnection(mainSocket, sockLen);
        sendFrame();
    }
    else{
        fdSocket=tryConnection(IP, PORT, 0);
        receiveFrame();
    }

    closeConnection(fdSocket);
    closeConnection(mainSocket);
    return 0;
}
