#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char tmp[4] ={0};
    scanf("%s",tmp);
    if(tmp == "A")
	printf("@@@@@");
    printf("!!!!");
}
