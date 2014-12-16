#include "client.h"

void client(char* IP){
    int fdSocket = tryConnection(IP, PORT, 0);

    while(true){
        cout << "[1]Fazer download" << endl;
        cout << "[2]Fazer upload" << endl;
        int x;
        cin >> x;
        if(x == 2){
            cout << "Qual arquivo?" << endl;
            char* nome;
            cin >> nome;
            int pos = checkFile(nome);
            sendMessage(fdSocket,protocolar(cacheF[pos], x), sizeof(protocol));
            cout << "Enviado para Server" << endl;
        }
        else if(x == 1){
            cout << "Qual arquivo?" << endl;
            char* nome;
            cin >> nome;
            protocol *prot;
            *prot->nome = *nome;
            prot->tipo = x;
            sendMessage(fdSocket,(char*)prot, sizeof(protocol));
            receiveMessage(fdSocket, nome, sizeof(protocol));
            prot = (protocol*)nome;
            cout << prot->nome << " recebido" << endl;
        }
    }
}

char* protocolar(File file, int tipo){
    protocol *prot;
    *prot->nome = *file.nome;
    prot->size = sizeof(file.arquivo);
    prot->tipo = tipo;

    return (char*)prot;
}

int checkFile(char* nome){
    for(unsigned int i = 0; i < cacheF.size(); i++)
        if(cacheF[i].nome == nome){
            cout << nome << " encontrado na cache" << endl;
            return i;
        }

    cout << nome << " nao esta na cache" << endl;
    //TODO: Ler arquivo e colocar em arquivosCache
    return cacheF.size();

    // Arquivo nao existente
    cout << nome <<  " nao existe" << endl;
    return false;
}
