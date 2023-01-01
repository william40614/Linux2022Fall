// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char* str, int start){
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}
int get_int(char* str, int start){
    int i, res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello";
    char *del;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

    while(1){
        int len = recv(new_socket,buffer,sizeof(buffer),0);
	int no = 0;
        int English = 0,a = 0,b = 0,i = 3,ans = 0;
	for(int j=3;j<len;j++){
	    if((buffer[i]<'0' || buffer[i] >'9') && 
			(buffer[i] <'a' || buffer[i] >'z') &&
				buffer[i]!=' ')
		no = 1;
	}
	//printf("%s",buffer);
	//printf("%s",input);
        if(buffer[i]!=' ')
	    no = 1;
	if(buffer[i+1] == '-')
	{
	    a = get_int(buffer,i+2);
	    a *= -1;
	}
	else
	    a = get_int(buffer,i+1);
	i = get_next_space(buffer,i+1);
	if(buffer[i+1]=='-')
	{
	    b = get_int(buffer,i+2);
	    b *= -1;
	}
	else
	    b = get_int(buffer,i+1);

	char tmp[4] = {buffer[0],buffer[1],buffer[2],0};
        
        //printf("%d %d %d %s\n",no,a,b,tmp);
	if(no == 1){
	    send(new_socket,hello,sizeof(hello),0);
	    continue;
	}
	else if(tmp[0] == 'a' && tmp[1] == 'd' && tmp[2] == 'd')
	    ans = a+b; 
	else if(tmp[0] == 'm' && tmp[1] == 'u' && tmp[2] == 'l')
	    ans = a * b;
	else if(tmp[0] == 'a' && tmp[1] == 'b' && tmp[2] == 's')
	{
	    ans = a;
	    if(ans < 0)
		ans *= -1;
	}
        char output[1024] = {0};
	sprintf(output,"%d",ans);
	//printf("%s\n%d %d \n%d\n%s\n",tmp,a,b,ans,output);
    	send(new_socket,output,sizeof(output),0);
    }

	return 0;
}
