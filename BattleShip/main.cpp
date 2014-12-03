#include <bits/stdc++.h>
#include "communication.h"

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
  /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
   */

    /// Iniciar conexao
    bool server;
    socklen_t sockLen;
    if(server){
        mainSocket = openConnection(PORT, 0);
        fdSocket = acceptConnection(mainSocket, sockLen);
    }
    else
        fdSocket = tryConnection("localhost", PORT, 0);


    closeConnection(mainSocket);
    closeConnection(fdSocket);
    return 0;
}
