// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

    usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

    while(1){
        // write your code!
	int j = 0;
	char c;
	char input[1024] ={0},output[1024] = {0};
	//printf("connected\n");
	//send(sock,hello,sizeof(hello),0);
	//recv(sock,buffer,sizeof(buffer),0);
	//printf("%s\n",buffer);
	//send(sock,hello,sizeof(hello),0);
	//printf("!!!!\n");
	while(1){
	    c = getchar();
	    input[j] = c;
	    if(c == '\n')
		break;
	    j++;
	}
	//printf("%s",input);
	if(input[0] =='k' && input[1] == 'i' && 
			input[2] == 'l' && input[3] == 'l'){
	    printf("\n");
	    break;
	}
	send(sock,input,sizeof(input),0);
	int len = recv(sock,buffer,sizeof(buffer),0);
	for(int i=0;i<len ;i++)
	    output[i] = buffer[i];
	printf("%s\n",output);
    }

	return 0;
}
