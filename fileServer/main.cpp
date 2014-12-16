#include "client.h"

using namespace std;

int main()
{
    cout << "Iniciando... \n Server/Client? <1/0>" << endl;
    bool server;
    cin >> server;

    if(server){
        servidor();
    }

    return 0;
}

