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
#include <time.h>

#define WAITBUF 10
#define RECVBUFSIZE 100

static void handle_request(int new_fd)
{
	int nbytes;
 	char buffer[RECVBUFSIZE];

while(1)
 {        
	memset(buffer,0,sizeof(buffer));
	if((nbytes=recv(new_fd,buffer, RECVBUFSIZE,0))==-1)
	{
       	 	fprintf(stderr,"Receive Error:%s\n",strerror(errno));
        	exit(1);
 	}
	else
 	{
		printf("");
		//printf("Size is:%d\n",strlen(buffer));	
	}

//Process the request
	char Request[RECVBUFSIZE];
	char ReqContend[RECVBUFSIZE];
	int i=0;
	int j=0;
	int k=0;
	int record=0;

	memset(Request,0,sizeof(Request));
	memset(ReqContend,0,sizeof(ReqContend));
	for(i;i<strlen(buffer);i++)
	{
		if(buffer[i]!=' ')
		{
			Request[j]=buffer[i];
			j++;
		}
		else
		{
			record=i;
			//printf("The request type is:%s\n",Request);
			break;
		}
	}

	int l=record+1;
	for(l;l<strlen(buffer);l++)
	{
		ReqContend[k]=buffer[l];
		k++;
	}
	//printf("The request contend is:%s\n",ReqContend);

//check the request type
  	if((strcmp(Request,"echo"))==0)
	{                

 	       if(send(new_fd,ReqContend,strlen(ReqContend),0)==-1)
        	{
       		  	fprintf(stderr,"Service Error:%s\n",strerror(errno));
         		exit(1);
        	}continue;
	}
	else if((strcmp(Request,"upper"))==0)
	{
		//Function UpperCase
		for(i=0;i<strlen(ReqContend);i++)
		{
			if(ReqContend[i]>='a'&&ReqContend[i]<='z')
			ReqContend[i]=ReqContend[i]-32;
		}
		//printf("The Upper Case request contend is:%s\n",ReqContend);
	
		if(send(new_fd,ReqContend,strlen(ReqContend),0)==-1)
        	{
       		  	fprintf(stderr,"Service Error:%s\n",strerror(errno));
         		exit(1);
        	}continue;
	}
	else if((strcmp(Request,"lower"))==0)
	{
		//Function LowerCase
		for(i=0;i<strlen(ReqContend);i++)
		{
			if(ReqContend[i]>='A'&&ReqContend[i]<='Z')
			ReqContend[i]=ReqContend[i]+32;
		}
		//printf("The Lower Case request contend is:%s\n",ReqContend);
	
		if(send(new_fd,ReqContend,strlen(ReqContend),0)==-1)
        	{
       		  	fprintf(stderr,"Service Error:%s\n",strerror(errno));
         		exit(1);
        	}continue;
	}
	else if((strcmp(Request,"reverse"))==0)
	{
		//Function Reverse
		int old,new=0;
		char ReverseContend[RECVBUFSIZE];
		memset(ReverseContend,0,sizeof(ReverseContend));
		old=strlen(ReqContend);
		while(old>0)
		{
			ReverseContend[new]=ReqContend[old-1];
			old--;
			new++;
		}
		//printf("The reversed contend is:%s\n",ReverseContend);

		if(send(new_fd,ReverseContend,strlen(ReverseContend),0)==-1)
        	{
       		  	fprintf(stderr,"Service Error:%s\n",strerror(errno));
         		exit(1);
        	}continue;

	}
	else if((strcmp(Request,"date"))==0)
	{	
		//function date
		time_t t;
		t=time(NULL);
		char *time;
		time=ctime(&t);
		//printf("The time is %s\n",time);

		if(send(new_fd,time,strlen(time),0)==-1)
        	{
       		  	fprintf(stderr,"Service Error:%s\n",strerror(errno));
         		exit(1);
        	}continue;
	}
	else
	{
                printf("Request command error!\n");
        	exit(1);        
	}
  
  }

      close(new_fd);	


}

static void handle_connect(int sockfd)
{
	int new_fd;
	socklen_t sin_size; 
	struct sockaddr_in client_addr;
  	sin_size=sizeof(struct sockaddr_in);

     while(1)
     {  
        if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
        {
                fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                exit(1);
    	}
	
	if(new_fd>0)
	{
		if(fork()>0)
		{
			close(new_fd);
		}
		else
		{
			handle_request(new_fd);
			return(0);
		}			
	}
    }  

}

int main(int argc, char *argv[])
{
 int sockfd;
 struct sockaddr_in server_addr;
 
 int portnumber;  

 portnumber=3333;

 if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  
 {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
 }

 bzero(&server_addr,sizeof(struct sockaddr_in));
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 server_addr.sin_port=htons(portnumber);
 
 if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
 {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
 }
 
 if(listen(sockfd, WAITBUF)==-1)
 {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);
 }

 printf("Waiting for clietn request:\n");
      
 handle_connect(sockfd);
	
	
      close(sockfd);
      exit(1);
}
