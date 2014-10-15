#include <bits/stdc++.h>
#include "communication.h"

using namespace std;

#define PORT 50000
int fdSocket;
char message[5];
bool janela;

void receiveFrame(){

    do {
        receiveMessage(fdSocket, message, sizeof(message));
        cout << "Recebeu: " << message << endl;
        sleep(1);
        sendMessage(fdSocket, message, sizeof(message));
    } while(message[2] != '#');

    cout << " -------- Acabou Janela --------" << endl;
    sleep(1);
}

void sendFrame(){
    do{
        sendMessage(fdSocket, message, sizeof(message));
        cout << "Enviou: " << message << endl;
        sleep(1);
        receiveMessage(fdSocket, message, sizeof(message));
    } while(message[2] != '#');

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
        fdSocket=tryConnection("localhost", PORT, 0);
        receiveFrame();
    }

    closeConnection(fdSocket);
    closeConnection(mainSocket);
    return 0;
}

