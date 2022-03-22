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
#include <pthread.h>
#define thread_number 10
void *echo(void* args);
int sockfd ;
int sizeofsocket;

pthread_mutex_t readlock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writelock = PTHREAD_MUTEX_INITIALIZER;

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
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	sizeofsocket=sizeof(from);
    if (bind(sockfd,(struct sockaddr*)&from, sizeofsocket)){
		printf("failed to bind\n");
		return 1;
	}
	
	int i=0;
	pthread_t threads[thread_number];
	for(i =0;i<thread_number;i++){
		if(pthread_create(threads+i, NULL, echo, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    	}
	}
	echo(NULL);
	
	return (0);
}
void *echo(void *args){
	struct sockaddr_in from;
	char data_received[256];
	while(1){
	pthread_mutex_lock(&readlock);
	memset(data_received,0,256);
	int bytes_received = recvfrom(sockfd, data_received, 255, 0,
           (struct sockaddr*)&from, &sizeofsocket);
	pthread_mutex_unlock(&readlock);
	pthread_mutex_lock(&writelock);
	int bytes_sent = sendto(sockfd, data_received, strlen(data_received), 0,
           (struct sockaddr*)&from, sizeofsocket);

	printf("Thread number %ld. The received data is %s\n", (long)pthread_self(), data_received);
	pthread_mutex_unlock(&writelock);
	}
	return NULL;
}