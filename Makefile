all : server client fancyclient concurrentClient
server : server.o
	cc -g -o server server.o -lpthread
server.o : server.c
	cc -c -Wall -g server.c 
concurrentClient : concurrentClient.o
	cc -g -o concurrentClient concurrentClient.o -lpthread
concurrentClient.o : concurrentClient.c
	cc -c -Wall -g concurrentClient.c 
client : client.o
	cc -g -o client client.o
client.o : client.c
	cc -c -Wall -g client.c 
fancyclient : fancyclient.o
	cc -g -o fancyclient fancyclient.o
fancyclient.o : fancyclient.c
	cc -c -Wall -g fancyclient.c 
clean:
	rm server.o server client client.o fancyclient fancyclient.o concurrentClient concurrentClient.o
clean_fancyclient:
	rm fancyclient fancyclient.o
clean_client:
	rm client client.o
clean_server:
	rm server server.o
clean_concurrentClient:
	rm concurrentClient concurrentClient.o