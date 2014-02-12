#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <arpa/inet.h>
#define BUFSIZE 100

int main(int argc, char **argv)
{
 	int sockfd;
  	struct sockaddr_in server_addr;
  	struct hostent *host;
  	int portnumber;
  	char msg[BUFSIZE];
  	int nbytes;
  	char RECVbuffer[BUFSIZE];

 	if(argc!=3)
 	{
 	 	fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
  		exit(1);
 	}
 
 	if((portnumber=atoi(argv[2]))<0)
 	{
       	 	fprintf(stderr,"Usage:%s hostname portnumber\a\n",argv[0]);
        	exit(1);
 	}
 
 	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
 	{
        	fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
        	exit(1);
 	}


 	bzero(&server_addr,sizeof(server_addr));
 	server_addr.sin_family=AF_INET;
 	server_addr.sin_port=htons(portnumber);
 	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
 	//server_addr.sin_addr.s_addr=INADDR_ANY;

 	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
	{
  		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
  		exit(1);
	}

while(1)
{
   	//printf("Please input your request:\n");	
	memset(msg,0,sizeof(msg));
   	gets(msg);
   	//printf("The input request is:%s\n",msg);

        if(send(sockfd,msg,strlen(msg),0)==-1)
        {
         	fprintf(stderr,"Send Error:%s\n",strerror(errno));
         	exit(1);
        }

	memset(RECVbuffer,0,sizeof(RECVbuffer));
	if((nbytes=recv(sockfd,RECVbuffer,BUFSIZE,0))==-1)
	{
       	 	fprintf(stderr,"Receive Error:%s\n",strerror(errno));
        	exit(1);
 	}
	else
	{printf("%s\n\n",RECVbuffer);}
		
}
	close(sockfd);
 	exit(1);

}
