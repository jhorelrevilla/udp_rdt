#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <vector>
using namespace std;

#define PORT	 8080 
#define MAXLINE 1024 
bool wait(double t){
	clock_t begin,end;
	begin=clock();
	double paso=0;
	while(paso!=t){
		end=clock();
		paso = double(end - begin) / CLOCKS_PER_SEC;
	}
	return true;
}
vector<string> paquetes(string t,int prot){
	vector<string> temp;
	while (t.size()>prot){
		string tem=t.substr(0,prot);
		temp.push_back(tem);
		t=t.substr(prot,t.size());
	}
	temp.push_back(t);
	return temp;
}
bool verificar(string msg,int mod,int check){
	int suma=0;
	for (int i = 0; i < msg.size(); i++){
		suma+=int(msg[i]);
	}
	suma=suma%mod;
	if(suma==check)
		return true;
	return false;
}

int enviar(string msg){
	int sockfd;
	char buffer[MAXLINE]; 
	struct sockaddr_in	 servaddr;
	vector<string> package;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { perror("socket creation failed"); exit(EXIT_FAILURE); } 
	memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	if (msg.size()>500){
		for(int i=0;i<msg.size();i+=500){

		}
	}
	///////Formar mensaje
	sendto(sockfd, msg.c_str(), msg.size()  , MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	///////
	cout<<"Mensaje enviado"<<endl;
	close(sockfd); 
}


int main() { 
	string test="prueba1";
	enviar(test);
	return 0; 
} 
