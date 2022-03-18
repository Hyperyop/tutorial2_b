#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
int main(int argc, char* argv[])
{
	if (argc < 3) {
	fprintf(stderr, "Missing argument. Please enter IP and port.\n");
	return 1;
    }

    char *IP = argv[1];
	char *port = argv[2];
	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	inet_pton(AF_INET,IP,&to.sin_addr.s_addr);
	to.sin_port  = htons(atoi(port));
	int sockto = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	from.sin_family = AF_INET;
	inet_pton(AF_INET,IP,&from.sin_addr.s_addr);
	from.sin_port = htons(atoi(port));
	int sockfrom = socket(AF_INET, SOCK_DGRAM, 0);
    if (bind(sockfrom,(struct sockaddr*)&from, sizeof(from))){
		fprintf(stderr,"failed to bind\n");
		return 1;
	}
	int sizeofsocket=sizeof(from);
	char data_received[256];
	char data_to_send[256];
	while(1){
	printf("Please enter data to send\n");
	memset(data_to_send,0,256);
	scanf("%255s", data_to_send);
	int bytes_sent = sendto(sockto, data_to_send, strlen(data_to_send), 0,
           (struct sockaddr*)&to, sizeof(to));
	memset(data_received,0,256);
	int bytes_received = recvfrom(sockfrom, data_received, 255, 0,
           (struct sockaddr*)&from, &sizeofsocket);
	printf("data received is: %s\n",data_received);
	}
	return (0);
}