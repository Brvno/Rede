#include <bits/stdc++.h>
#include "communication.h"
#include "campo.h"

#define PORT 5000

int fdSocket, mainSocket;

struct mensagem{
    int code;
    int x,y;
};

mensagem *rcvMsg(){
    char msg[100];
    receiveMessage(fdSocket,msg,sizeof(msg));
    return (mensagem*)msg;
}

int main(int argc, char *argv[])
{
    /// Iniciar conexao
    bool server;
    socklen_t sockLen;
    if(server){
        mainSocket = openConnection(PORT, 0);
        fdSocket = acceptConnection(mainSocket, sockLen);

    }
    else
    {
        fdSocket = tryConnection("localhost", PORT, 0);
    }

    Campo mySide = new Campo(true);
    Campo enemySide = new Campo(false);
    mySide.posicionar();


    while(!mySide.isGameOver() && !enemySide.isGameOver()){
        mySide.showCampo();
        enemySide.showCampo();
        std::pair<int,int> posTiro;
        mensagem *cmd;
        if(server){
            ///Atirar
            posTiro = mySide.atirar();
            cmd->x = posTiro.first;
            cmd->y = posTiro.second;
            cmd->code = 1;

            sendMessage(fdSocket,(char*)cmd, sizeof(cmd));
            cmd = rcvMsg();
            if(cmd->code == 5 || cmd->code == 6){
                std::cout << "WINNER!" << std::endl;
                break;
            }


        }
    }


    closeConnection(mainSocket);
    closeConnection(fdSocket);
    return 0;
}
