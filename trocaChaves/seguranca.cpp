#include "communication.h"
#include<iostream>

#define PORT  50000
#define PORT2 50001
int fdSocket, mainSocket,fdSocket2;
using namespace std;
char chave_ses,msg[100],minhachave,message[100];
void criptografa()
{
    int i=0;
    while(msg[i]!='\0')
    {
        message[i]=message[i]+chave_ses;
        i++;
    }
}
void descriptografa()
{
    int i=0;
    while(msg[i]!='\0')
    {
        message[i]=message[i]-chave_ses;
        i++;
    }
}
struct chaves
{
  char nome;        //codigo do computador
  int chave;

};
chaves banco[5];


// dois argumentos 2 ips
int main(int argc, char *argv[])
{
	//inicializacao
	banco[0].nome='A';
	banco[0].chave='1';
	banco[1].nome='B';
	banco[1].chave='2';
	char minhachavei,pc1,pc2; 
    /// Iniciar conexao
    int server;
    socklen_t sockLen;
    struct sockaddr_in socketAddr;
    sockLen = sizeof(socketAddr);
    cout << "Servidor? [0/1/2]" <<endl;
    cin >> server;
    if(server==0 || server==2){
        mainSocket = openConnection(PORT, 0);
        fdSocket = acceptConnection(mainSocket, sockLen);

    }
    else
    {
        fdSocket = tryConnection((char*)argv[1], PORT, 0);
        fdSocket2= tryConnection((char*)argv[2], PORT2, 0);
    }
    //se for server
    //recebe mensagem e envia a
    //criptografia da mensagem A,a chave de sessão a,b criptografada e uma criptografia para o b com a chave de sessão
    if(server==0)
    {
        char* msg;
		 msg = (char*)malloc(3*sizeof(char));		
        receiveMessage(fdSocket,msg,sizeof(char)*100);
        cout<<"mensagem eh ="<<msg<<endl;
        cout<<"recebeu a primeira"<<endl;
        pc1=msg[0];
        pc2=msg[1];
        int chave1,chave2;
        int chave3=3;
        for(int i=0;i<5;i++) 
        {
            if(pc1 == banco[i].nome)
                chave1=banco[i].chave;
            if(pc2 == banco[i].nome)
                chave2=banco[i].chave;
        }
        //chaveA,crip(A,B),chaveB,crip(a,b)
        char chave_encp31=(char)(chave3+chave1);
        char chave_encp32=(char)(chave3+chave2);
        cout<<chave_encp31<<"  "<<chave_encp32;
        msg[0]=chave_encp31;
        msg[1]=chave_encp32;
        sendMessage(fdSocket,msg,sizeof(char)*100);
        cout<<"mensagem eh"<<msg<<endl;
        closeConnection(fdSocket);
    }
    //se for pc 1
    if(server==1)
    {	
    	minhachave=1;
        char* msg;
        msg = (char*)malloc(3*sizeof(char));		
        msg[0]='A';
        msg[1]='B';
        msg[2] = '\0';
        //envia mensagem pro servidor
         cout<<"mensagem eh ="<<msg<<endl;
        sendMessage(fdSocket, msg, sizeof(char)*100);
        cout<<"enviou primeira"<<endl;
        //recebe mensagem do servidor
        receiveMessage(fdSocket,msg,sizeof(char)*100);
         cout<<"mensagem eh ="<<msg<<endl;
        cout<<"recebeu a criptografia"<<endl;
        chave_ses=(int)msg[0];
        chave_ses=chave_ses-minhachave;
        cout<<"chave_ses="<<chave_ses<<endl;
        msg[0]='A';
        sendMessage(fdSocket2,msg,sizeof(char)*100);
		//comeca mensagens
		while(strcmp(message, "tchau")){
			receiveMessage(fdSocket2,message,100*sizeof(char)); //Recebe mensagem
			printf("mensagem criptografada dele: %s\n", message);
			descriptografa();
			printf("mensagem descriptografada dele: %s\n", message);
			if(!strcmp(message, "tchau"))
				break;
			gets(message);
			printf("mensagem descriptografada minha: %s\n", message);
			criptografa();
			printf("mensagem criptografada minha: %s\n", message);
			sendMessage(fdSocket2,message,100*sizeof(char)); //Envia mensagem

		}

    }

    //se for pc 2
    if(server==2)
    {
    	minhachave=2;
        receiveMessage(fdSocket,msg,100*sizeof(char));
        chave_ses=(int)msg[1];
        chave_ses=chave_ses-minhachave;
		//comeca mensagens
		while(strcmp(message, "tchau")){
					printf("Você: ");
					gets(message);
					criptografa();
					sendMessage(fdSocket,message,100*sizeof(char)); //Envia mensagem			
					receiveMessage(fdSocket,message,100*sizeof(char)); //Recebe mensagem
					descriptografa();
					printf("Mensagem Recebida: %s\n", message);
		}
	

    }

}
