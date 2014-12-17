#include "funcoes.h"

using namespace std;

int main()
{
    cout << "Iniciando... \n Server/Client? <1/0>" << endl;
    bool server;
    cin >> server;

    if(server){
        servidor();
    }
    else{
        cout << "IP do servidor: ";
        char *ip;
        ip = (char*)malloc(sizeof(char)*20);
        cin >> ip;
        client(ip);
    }

    return 0;
}

