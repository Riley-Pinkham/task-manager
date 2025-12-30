#include <sys/socket.h> // For send()
#include <arpa/inet.h>  // For htonl()
#include <string.h>     // For strlen()
#include <iostream>     // For error output
#include <vector>
#include "NetworkUtils.h"



// NOTE: use of size_t. 
int NetworkUtils::send_all_data(int socketFD, const char* buffer, size_t total_length)
{
    // Loop through all data. 
    // documentation on the socket send() function: The call returns the number of characters sent, or -1 if an error occurred.
    size_t total_bytes_sent = 0;
    size_t remaining = total_length;
    int n;

    while(total_bytes_sent < total_length)
    {
        // Send total size of data first. 

        n = send(socketFD, buffer + total_bytes_sent, remaining, 0);

        if(n <= 0)
        {
            if(n < 0)
            {
                std::cerr << "Failed to send data";
            }
            return -1;
        }

        total_bytes_sent += n;
        remaining -= n;
    }

    return 0;
}

int NetworkUtils::send_framed_json(int socketFD, const char* json_data)
{
    //Calculat total size of json and store it in a 32 bit (4byte) integer. 
    uint32_t json_data_length = (uint32_t)strlen(json_data);// explicitly cast to uint32_t. intentionally using C style cast to show intent. 

    uint32_t network_json_data_length = htonl(json_data_length);// Need to use network byte order. Can't be certain what the host will use (big or little)

    if(send_all_data(socketFD, (const char*)&network_json_data_length, sizeof(network_json_data_length)) < 0)
    {
        std::cerr << "Failed to send json header data" << std::endl;
        return -1;
    }

    if(send_all_data(socketFD, json_data, json_data_length) < 0)
    {
        std::cerr << "Failed to send json data" << std::endl;
        return -1;
    }


    return 0;
} 

//read(newSocket, buffer, 1024);
// The recv() calls return the number of bytes received, or -1 if an error occurred.
int NetworkUtils::recieve_all_data(int sockfd, char* buffer, size_t total_length) {
    size_t bytes_received = 0;
    size_t remaining = total_length;
    int n;

    while(bytes_received < total_length)
    {
        n = recv(sockfd, buffer + bytes_received, remaining, 0);

        if (n == 0) 
        {
            // Connection closed gracefully by the peer
            std::cerr << "Connection closed by peer." << std::endl;
            return 0; // Return 0 to indicate graceful closure
        }
        if (n < 0) 
        {
            // Error occurred (e.g., connection reset)
            perror("recv failed");
            return -1; // Indicate failure
        }

        bytes_received += n;
        remaining -= n;
    }
        return total_length; // Return total bytes successfully received
}

std::string NetworkUtils::recieve_framed_json(int socketFD)
{
    // We should get the header first that gives info on how big the json data is. i.e. how much we need to read. 
    uint32_t recieved_network_json_data_length;
    uint32_t recieved_json_data_length;

    //get header
    int header_length = recieve_all_data(socketFD, (char*)&recieved_network_json_data_length, sizeof(recieved_network_json_data_length));

    if(header_length <= 0)
    {
        std::cerr << "Error Getting Header Length" << std::endl;
    }

    recieved_json_data_length = ntohl(recieved_network_json_data_length);

    std::vector<char> json_data(recieved_json_data_length + 1);

    int status_of_payload = recieve_all_data(socketFD, json_data.data(), recieved_json_data_length);

    if(status_of_payload <= 0)
    {
        std::cerr << "Error Getting JSON Payload" << std::endl;
    }

    json_data[recieved_json_data_length] = '\0';
    return std::string(json_data.data());
}

