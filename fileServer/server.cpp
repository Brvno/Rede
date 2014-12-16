#include "server.h"

int checkFile(char* nome){
    for(unsigned int i = 0; i < arquivosCache.size(); i++)
        if(arquivosCache[i].nome == nome){
            cout << nome << " encontrado na cache" << endl;
            return i;
        }

    cout << nome << " nao esta na cache" << endl;
    //TODO: Ler arquivo e colocar em arquivosCache
    return arquivosCache.size();

    // Arquivo nao existente
    cout << nome <<  " nao existe" << endl;
    return false;
}

//Cria Mensagem de acordo com o protocolo
char* protocolar(File file, int tipo){
    protocol *prot;
    *prot->nome = *file.nome;
    prot->size = sizeof(file.arquivo);
    prot->tipo = tipo;

    return (char*)prot;
}

//Thread que ficara rodando no servidor
void* threadServidor(void* socket){
    int fdSocket = (int)socket;
    char* message;
    protocol *requisit;
    while(true){
        receiveMessage(fdSocket,message,sizeof(protocol));
        requisit = (protocol*)message;
        //Verificar msg
        if(requisit->tipo > 3)
            cout << "Mensagem em formato errado" << endl;
        //Upload
        else if(requisit->tipo == 1) {
            File up;
            up.arquivo = requisit->arquivo;
            *up.nome = *requisit->nome;
            arquivosCache.push_back(up);
            //TODO: Salvar no arquivo
        }
        //Pedir download
        else if(requisit->tipo == 2) {
            int posFile = checkFile(requisit->nome);
            if(posFile){
                message = protocolar(arquivosCache[posFile],3);
                sendMessage(fdSocket, message, sizeof(protocol));
            }
        }
    }
}

void servidor(){
    mainSocket = openConnection(PORT, 0);

    //Abertura de sockets para os clientes
    cout << "Quantos clientes?" << endl;
    int num;
    cin >> num;
    sockets.resize(num);
    pthread_t thServer[num];

    for(int i = 0; i < num; i++){
        sockets[i] = acceptConnection(mainSocket, sockLen);
        pthread_create(&thServer[i], NULL, &threadServidor, (void*)sockets[i]);
    }

}

////Client Code
