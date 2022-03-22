# A simple implementation of a multi-threaded UDP client and UDP echo server
Concurrent client program is using 2 functions one to receive data from server and another to send it existing in two separate threads.
Server program is made of a number of threads each can handle receiving and echo back data using the function echo.
A makefile was included to help with compiling the project