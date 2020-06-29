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
#include <ctime>
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

int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	string msg = "msg from client"; 
	struct sockaddr_in	 servaddr; 

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { perror("socket creation failed"); exit(EXIT_FAILURE); } 
	memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	while (true){
		cout<<"Escribe q para salir\nEnviar mensaje al server: ";	
		getline(cin,msg);
		if(msg=="q")
			break;
		sendto(sockfd, msg.c_str(), msg.size()  , MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
		cout<<"Mensaje enviado"<<endl;
			
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,(socklen_t *) &len); 

		buffer[n] = '\0'; 
		cout<<"El server envio "<<buffer<<endl;
		cout<<"//////////////////////////////"<<endl;
	}
	close(sockfd); 
	return 0; 
} 
