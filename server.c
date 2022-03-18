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
	if (argc < 2) {
	fprintf(stderr, "Missing argument. Please enter Port to listen to.\n");
	return 1;
    }

	char *port = argv[1];
	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	from.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&from.sin_addr.s_addr);
	from.sin_port = htons(atoi(port));
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int sizeofsocket=sizeof(from);
    if (bind(sockfd,(struct sockaddr*)&from, sizeofsocket)){
		printf("failed to bind\n");
		return 1;
	}
	char data_received[256];
	while(1){
	memset(data_received,0,256);
	int bytes_received = recvfrom(sockfd, data_received, 255, 0,
           (struct sockaddr*)&from, &sizeofsocket);
	int bytes_sent = sendto(sockfd, data_received, strlen(data_received), 0,
           (struct sockaddr*)&from, sizeofsocket);
	printf("%s\n",data_received);
	}
	return (0);
}