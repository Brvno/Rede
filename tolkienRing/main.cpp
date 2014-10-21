#include <iostream>
#include <bits/stdc++.h>
#include <communication.h>

using namespace std;

int mainSocket, fdSocketAcc, fdSocketTry;

void conectarServer(){

    //Abrindo a conexao para maquina anterior
    int portal;
    cout << "Qual portal desejas abrir? ";
    cin >> portal;
    mainSocket = openConnection(portal, 0);
    fdSocketAcc = acceptConnection(mainSocket, sockLen);

}

void conectarClient(){
    //Ip da maquina que sera conectado
    cout << "IP do alvo: " << endl;
    char ipTarget[20];
    cin >> ipTarget;
    cout << "Porta: " << endl;
    int portal;
    cin >> portal;
    fdSocketTry = tryConnection(ipTarget, portal, 0);
}

#define PORT 50000
int main()
{

    sockaddr_in sockAddr;
    char message[20] = "One Ring";
    socklen_t sockLen;

    char r;
    bool portador = false;

    cout << "Voce eh o Portador? [y/n]" << endl;
    cin >> r;
    cout << endl;
    if(r == 'y' || r == 'Y')
        portador = true;

    bool temp = false;
    cout << "[0]Server" << endl << "[1]Client" << endl;
    cin >> temp;
    if(temp){
        conectarClient();
        conectarServer();
    }
    else{
        conectarServer();
        conectarClient();
    }

    //Loop que ficara passando o One Ring
    while(true){
        if(portador)
        {
            cout << "Eu sou o Portador do Um Anel. Kneel before me!" << endl;
            sleep(2);
            cin >> temp;
            sendMessage(fdSocketTry, message, sizeof(message));
            cout << "Sneaky little hobbitsses... \n They stole it from us! \n My Precious" << endl;
            portador = false;
        }
        else{
            receiveMessage(fdSocketAcc, message, sizeof(message));
            if(message == "One Ring")
                portador = true;
        }
    }
}

