#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cstring>
#include <iostream>

#include "NetworkUtils.h"

/*
* When server socket object is created it does not have any details of the IP address or port it will use.
* To give a socket this information it needs to be bound with these details. Each of these detaisl, the IP address
* and port, along with some other info like the address family etc. are stored in a struct of type sockaddr. 
* On the server side we will always have a listening socket. That means when we make a new connection with a client 
* we will need to spin up a new socket for that connection. 
*
*/




int main (int argc, char* argv[]){

    // Socket Programing. Note: This is not using SSL or any sort of security. On wireshark you should be able to see raw data

    /*
    * Steps for socket programing SERVER:
    *   1. Create two file descriptors. One for a listening socket, the other for a new socket connection..   
    *   2. Create our sockaddr struct that will hold our socket details. 
    *   3. 
    *   4. 
    *   5. 
    *   .
    *   .
    *   .
    */
    
    // NOTE: we will want to make the code support the ability to create newSockets (multiple) to handle many connections. 
    int socketfd, newSocket; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

      // Attach socket to the port
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(8080);

          // Bind
    if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } 


    // Listen
    if (listen(socketfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(true){


        newSocket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (newSocket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Read data from the connected client socket
        std::string recieved_json = NetworkUtils::recieve_framed_json(newSocket);

        std::cout << "Message from client: " << recieved_json << std::endl;

        //recieve framed json


    }
    



    // Close socket
    close(newSocket);
    close(socketfd);

    return 0;
}