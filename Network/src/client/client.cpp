#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


#include <cstring>
#include <iostream>

#include "NetworkUtils.h"



int main (int argc, char* argv[]){

    // Socket Programing. Note: This is not using SSL or any sort of security. On wireshark you should be able to see raw data

    /*
    * Steps for socket programing CLIENT:
    *   1. 
    *   2. 
    *   3. 
    *   4. 
    *   5. 
    *   .
    *   .
    *   .
    */

    int socketfd = 0;
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to server
    if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed: " << strerror(errno) << std::endl;
        return -1;
    }

    // Send data... Send is not gaurnteeded to send all data in one go. This should really be in a while loop until all data is sent. 
    // TO DO: Create a Reliable Send Implementation that ensures all data has been sent. 
    // send(socketfd, hello, strlen(hello), 0);

    //use new send_all function
    const char* json_string = "{\"item1\": \"value1\",\"item2\": \"value2\",\"item3\": \"value3\"}";
    NetworkUtils::send_framed_json(socketfd, json_string);
    std::cout << "Message sent" << std::endl;

    // Close socket
    close(socketfd);

    return 0;
}