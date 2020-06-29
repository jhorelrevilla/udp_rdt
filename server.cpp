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
	struct sockaddr_in servaddr, cliaddr; 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { perror("socket creation failed"); exit(EXIT_FAILURE); } 
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { perror("bind failed"); exit(EXIT_FAILURE); } 

	string msg = "recibido"; 
	int len, n; 
	while (true){	
		len = sizeof(cliaddr); 
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr,(socklen_t *) &len); 
		buffer[n] = '\0'; 
		cout<<"Cliente envio: "<<buffer<<endl; 
		sendto(sockfd, msg.c_str() , msg.size(), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
		cout<<"mensaje enviado"<<endl;
		cout<<"//////////////////////////////"<<endl;
	}
	return 0; 
} 
