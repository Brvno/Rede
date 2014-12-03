#include <bits/stdc++.h>
#include "communication.h"
#include "campo.h"

#define PORT 50000

int fdSocket, mainSocket;

struct mensagem{
    int code, x, y;
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
    std::cout << "Servidor? [1/0]" << std::endl;
    std::cin >> server;
    if(server){
        mainSocket = openConnection(PORT, 0);
        fdSocket = acceptConnection(mainSocket, sockLen);

    }
    else
    {
        fdSocket = tryConnection((char*)argv[1], PORT, 0);
    }

    Campo mySide = new Campo(true);
    Campo enemySide = new Campo(false);
    mySide.posicionar();


    while(!mySide.isGameOver() && !enemySide.isGameOver()){
        system("clear");
        mySide.showCampo();
        enemySide.showCampo();

        mensagem *cmd = (mensagem*)malloc(sizeof(mensagem));
        char *msg = (char*)malloc(sizeof(mensagem));

        if(server){
            ///Atirar
            bool errou = false;
            do {
                std::cout << "Posição do Tiro: " << std::endl;
                std::cin >> cmd->x >> cmd->y;
                cmd->code = 1;
                msg = (char*)cmd;

                sendMessage(fdSocket, msg, sizeof(mensagem));

                //Confirmacao
                receiveMessage(fdSocket, msg, sizeof(mensagem));
                if(cmd->code == 5 || cmd->code == 6){
                    std::cout << "WINNER!" << std::endl;
                    break;
                }
                else if(cmd->code == 2){
                    enemySide.rcvTiro(cmd->x, cmd->y,true);
                    std::cout << "Acertou! \n";
                    errou = false;
                }
                else if(cmd->code == 3){
                    enemySide.rcvTiro(cmd->x, cmd->y, false);
                    std::cout << "AGUA! \n";
                    errou = true;
                }
                else if(cmd->code == 4)
                    std::cout << "Jogada Invalida" << std::endl;

                system("clear");
                mySide.showCampo();
                enemySide.showCampo();
            } while(!errou);

            //Receber tiro
            bool invalido = false;
            do {
                receiveMessage(fdSocket, msg, sizeof(mensagem));
                mensagem *cmd = (mensagem*)malloc(sizeof(mensagem));
                cmd = (mensagem*)msg;

                switch(cmd->code){
                    case 1:
                        if(cmd->x > 0 && cmd->x < 11 && cmd->y > 0 && cmd->y < 11){
                            cmd->code = mySide.rcvTiro(cmd->x,cmd->y);
                            std::cout << "Tiro Recebido em: [" << cmd->x << "," << cmd->y << "]" ;
                            if(cmd->code == 2){

                                std::cout << "Hit\n";
                                if(mySide.isGameOver())
                                   cmd->code=5;
                            }
                            else {
                                std::cout << "Miss\n";
                                invalido = true;
                            }
                        }
                        else
                            cmd->code = 4;
                        sendMessage(fdSocket, (char*)cmd, sizeof(mensagem));

                        break;
                    case 6:
                        std::cout << "WINNER!" << std::endl;
                        return 0;
                }
                system("clear");
                mySide.showCampo();
                enemySide.showCampo();
            } while(!invalido);

        }
        else {
            //Receber tiro
            bool invalido = true;
            do{
                receiveMessage(fdSocket, msg, sizeof(mensagem));
                mensagem *cmd = (mensagem*)malloc(sizeof(mensagem));
                cmd = (mensagem*)msg;

                switch(cmd->code){
                    case 1:
                        if(cmd->x > 0 && cmd->x < 11 && cmd->y > 0 && cmd->y < 11){
                            cmd->code = mySide.rcvTiro(cmd->x,cmd->y);
                            std::cout << cmd->code << " Tiro Recebido em: [" << cmd->x << "," << cmd->y << "]\n" ;
                            if(cmd->code == 2){
                                invalido = false;
                                std::cout << "Hit\n";
                                if(mySide.isGameOver())
                                   cmd->code=5;
                            }
                            else{
                                invalido = true;
                                std::cout << "Miss\n";
                            }
                        }
                        else
                            cmd->code = 4;

                        sendMessage(fdSocket, (char*)cmd, sizeof(mensagem));

                        break;
                    case 6:
                        std::cout << "WINNER!" << std::endl;
                        return 0;
                }
                system("clear");
                mySide.showCampo();
                enemySide.showCampo();

            } while(!invalido);
            ///Atirar
            bool errou = false;
            do {
                std::cout << "Posição do Tiro: " << std::endl;
                std::cin >> cmd->x >> cmd->y;
                cmd->code = 1;
                msg = (char*)cmd;

                sendMessage(fdSocket, msg, sizeof(mensagem));

                //Confirmacao
                receiveMessage(fdSocket, msg, sizeof(mensagem));
                if(cmd->code == 5 || cmd->code == 6){
                    std::cout << "WINNER!" << std::endl;
                    break;
                }
                else if(cmd->code == 2){
                    enemySide.rcvTiro(cmd->x, cmd->y,true);
                    std::cout << "Acertou! \n";
                    errou = false;
                }
                else if(cmd->code == 3){
                    enemySide.rcvTiro(cmd->x, cmd->y, false);
                    std::cout << "AGUA! \n";
                    errou = true;
                }
                else if(cmd->code == 4)
                    std::cout << "Jogada Invalida" << std::endl;

                system("clear");
                mySide.showCampo();
                enemySide.showCampo();

            } while(!errou);

        }
    }

    closeConnection(mainSocket);
    closeConnection(fdSocket);
    return 0;
}
