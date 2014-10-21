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

    bool temp = false;
    for(int i = 0; i < 2; i++){
        if(i == 0){
            cout << "[0]Server" << endl << "[1]Client" << endl;
            cin >> temp;
        }
        else{
            if(!temp){
                //Abrindo a conexao para maquina anterior
                int portal;
                cout << "Qual portal desejas abrir? ";
                cin >> portal;
                mainSocket = openConnection(portal, 0);
                fdSocketAcc = acceptConnection(mainSocket, sockLen);
                temp = true;
            }
            else{
                //Ip da maquina que sera conectado
                cout << "IP do alvo: " << endl;
                char ipTarget[20];
                cin >> ipTarget;
                cout << "Porta: " << endl;
                int portal;
                cin >> portal;
                fdSocketTry = tryConnection(ipTarget, portal, 0);
                temp = false;
            }
        }
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

