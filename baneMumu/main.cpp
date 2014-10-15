#include <bits/stdc++.h>
#include "communication.h"
#include <pthread.h>

using namespace std;

#define PORT 50000
#define IP "localhost"
int fdSocket;
char message[1];
bool janela;

void receiveFrame(){

    do {
        receiveMessage(fdSocket, message, sizeof(message));
        if(rand() % 20 > 2)
            cout << "Recebeu: " << (int)message[0] << endl;
        else {
            cout << "falhou" << endl;
        }
        sleep(1);
        sendMessage(fdSocket, message, sizeof(message));
    } while(message[0] != '#');

    cout << " -------- Acabou Janela --------" << endl;
    sleep(1);
}

void *confirmFrame(void * i){
    receiveMessage(fdSocket, message, sizeof(message));
}

void sendFrame(){
    pthread_t thread;
    int a;
    pthread_create(&thread, NULL, &confirmFrame, (void *)a);
    for(int i = 1; i < 99; i++){
        message[0] = i;
        if(i == 99)
            message[0] = '#';
        sendMessage(fdSocket, message, sizeof(message));
        cout << "Enviou: " << (int)message[0] << endl;
        sleep(1);
    }

    cout << " -------- Acabou Janela --------" << endl;
}

int main()
{
    int mainSocket;
    struct sockaddr_in socketAddr;
    socklen_t sockLen;

    message[0] = '0';
    message[1] = '1';
    message[2] = '#';

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
