#include "NotificationManager.h"
#include "NetworkUtils.h"
#include <iostream>


void NotificationManager::subscribe(int clientSocket){

    std::lock_guard<std::mutex> lock(subscriberMutex);
    try
    {
        subscriberList.push_back(clientSocket);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed To Subscribe" << e.what() << '\n';
    }

}

void NotificationManager::unsubscribe(int clientSocket){
    std::lock_guard<std::mutex> lock(subscriberMutex);

    try
    {
        subscriberList.erase(std::remove(subscriberList.begin(), subscriberList.end(), clientSocket), subscriberList.end());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed to unsubscribe" << e.what() << '\n';
    }
}


void NotificationManager::broadcast(const nlohmann::json& message){

    std::string messageString = message.dump();

    // copy with lock in seperate scope so lock_guard unlocks as soon a possible. 
    std::vector<int> currentSubscribers;
    {
        std::lock_guard<std::mutex> lock(subscriberMutex);
        currentSubscribers = subscriberList;
    }

    for (int subscriber : currentSubscribers ){
            send(subscriber, messageString);
        
    }

}

void NotificationManager::send(int clientSocket, const std::string& message){

    int result = NetworkUtils::send_framed_json(clientSocket, message.c_str());

    if (result < 0){
        std::cerr << "Error: Client on socket " << clientSocket << " has disappeared." << std::endl;
        unsubscribe(clientSocket);
    }

}