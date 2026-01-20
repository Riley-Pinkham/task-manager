#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <thread>

#include "NetworkUtils.h"
#include "TaskRepository.h"
#include "TaskService.h"
#include "NotificationManager.h"
#include "TaskCommandDispatcher.h"
#include "CommandSerializer.h"

using json = nlohmann::json;

/*
* When server socket object is created it does not have any details of the IP address or port it will use.
* To give a socket this information it needs to be bound with these details. Each of these detaisl, the IP address
* and port, along with some other info like the address family etc. are stored in a struct of type sockaddr. 
* On the server side we will always have a listening socket. That means when we make a new connection with a client 
* we will need to spin up a new socket for that connection. 
*
*/


// GLOBAL/SHARED INSTANCES

TaskRepository repo;
TaskService service(&repo);
NotificationManager notifier;
TaskCommandDispatcher dispatcher(service, notifier);

// Make it easy to pass socket file descriptors off to new threads.
void handle_client(int clientSocket, NotificationManager& notifier, TaskCommandDispatcher& dispatcher){
    std::cout << "Thread started for client socked: " << clientSocket << std::endl;

    // Register the socket
    notifier.subscribe(clientSocket);

    try
    {
        // I'm not sure how I like this while true. We also break out of it when we recieve an 
        // empty json string... I'm sure we can make this better at some point. 
        while (true)
        {
            // Recieve data
            std::string recievedJsonString = NetworkUtils::recieve_framed_json(clientSocket);

            if(recievedJsonString.empty()){
                //
                break;
            }

            Command* cmd = CommandSerializer::fromJsonString(recievedJsonString);

            if (cmd != nullptr){
                // Use the command and then delete it. 
                std::string response = dispatcher.execute(*cmd).dump();

                NetworkUtils::send_framed_json(clientSocket, response.c_str());

                delete cmd;
            } else {
                std::cerr << "ERROR: Invalid Command Format" << std::endl;
            }
        }
        notifier.unsubscribe(clientSocket);
        close(clientSocket);
        std::cout << "Client on socket " << clientSocket << " has disconnected." << std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

// I'm sure I will change the schema in the future...maybe. 
std::string readSchemaFile(const std::string& filepath) {
    std::ifstream file (filepath);
    if (!file.is_open()){
        std::cerr << "an error occurred" << std::endl;
        return "";
    }

    std::string line;
    std::string schemaSql;
    while (std::getline(file, line)) {
        schemaSql += line + "\n";
    }

    return schemaSql;

}


int main (int argc, char* argv[]){

    sqlite3* db;
    int returnCode = sqlite3_open("task_manager.db", &db);
    if (returnCode) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const std::string schemaSql = readSchemaFile("db/schema.sql");

    int rc = sqlite3_exec(db, schemaSql.c_str(), NULL, 0, NULL);

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

        // pass socket off to new thread. 
        std::thread passingThread(handle_client, newSocket, std::ref(notifier), std::ref(dispatcher));
        passingThread.detach();

        // NOTE: 
        // Detached threads can't be joined, so on server shutdown you'll have orphaned threads. 
        // Consider keeping a vector of thread objects and joining them on shutdown

    }
    
    // Close socket.. Never reached because of while loop. Need to add a way to gracefully shut down.
    close(newSocket);
    close(socketfd);

    return 0;
}