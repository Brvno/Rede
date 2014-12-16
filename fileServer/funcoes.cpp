//#include "funcoes.h"


///// ---------------------- CLIENT ------------------------------------- ////

//void client(char* IP){
//    int fdSocket = tryConnection(IP, PORT, 0);

//    while(true){
//        cout << "[1]Fazer download" << endl;
//        cout << "[2]Fazer upload" << endl;
//        int x;
//        cin >> x;
//        if(x == 2){
//            cout << "Qual arquivo?" << endl;
//            char* nome;
//            cin >> nome;
//            int pos = checkFile(nome, cacheF);
//            sendMessage(fdSocket,protocolar(cacheF[pos], x), sizeof(protocol));
//            cout << "Enviado para Server" << endl;
//        }
//        else if(x == 1){
//            cout << "Qual arquivo?" << endl;
//            char* nome;
//            cin >> nome;
//            protocol *prot;
//            *prot->nome = *nome;
//            prot->tipo = x;
//            sendMessage(fdSocket,(char*)prot, sizeof(protocol));
//            receiveMessage(fdSocket, nome, sizeof(protocol));
//            prot = (protocol*)nome;
//            cout << prot->nome << " recebido" << endl;
//        }
//    }
//}


///// ---------------------- SERVER ------------------------------------- ////

////Thread que ficara rodando no servidor
//void* threadServidor(void* socket){
//    int fdSocket = (int)socket;
//    char* message;
//    protocol *requisit;
//    while(true){
//        receiveMessage(fdSocket,message,sizeof(protocol));
//        requisit = (protocol*)message;
//        //Verificar msg
//        if(requisit->tipo > 3)
//            cout << "Mensagem em formato errado" << endl;
//        //Upload
//        else if(requisit->tipo == 1) {
//            File up;
//            up.arquivo = requisit->arquivo;
//            *up.nome = *requisit->nome;
//            arquivosCache.push_back(up);
//            //TODO: Salvar no arquivo
//        }
//        //Pedir download
//        else if(requisit->tipo == 2) {
//            int posFile = checkFile(requisit->nome);
//            if(posFile){
//                message = protocolar(arquivosCache[posFile],3);
//                sendMessage(fdSocket, message, sizeof(protocol));
//            }
//        }
//    }
//}


//void servidor(){
//    mainSocket = openConnection(PORT, 0);

//    //Abertura de sockets para os clientes
//    cout << "Quantos clientes?" << endl;
//    int num;
//    cin >> num;
//    sockets.resize(num);
//    pthread_t thServer[num];

//    for(int i = 0; i < num; i++){
//        sockets[i] = acceptConnection(mainSocket, sockLen);
//        pthread_create(&thServer[i], NULL, &threadServidor, (void*)sockets[i]);
//    }

//}

