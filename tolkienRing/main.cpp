#include <iostream>
#include <bits/stdc++.h>
#include <communication.h>

using namespace std;

#define PORT 50000
int main()
{
    int mainSocket, fdSocketAcc, fdSocketTry;
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

    //Abrindo a conexao para maquina anterior
    mainSocket = openConnection(PORT, 0);
    fdSocketAcc = acceptConnection(mainSocket, sockLen);

    //Ip da maquina que sera conectado
    cout << "IP do alvo: " << endl;
    char ipTarget[20];
    cin >> ipTarget;
    fdSocketTry = tryConnection(ipTarget, PORT, 0);

    //Loop que ficara passando o One Ring
    while(true){
        if(portador)
        {
            cout << "Eu sou o Portador do Um Anel. Kneel before me!" << endl;
            sleep(2);
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

