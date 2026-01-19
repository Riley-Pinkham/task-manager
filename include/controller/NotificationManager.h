#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <mutex>
#include <vector>
#include "external/json.hpp"

class NotificationManager{

private:
    std::vector<int> subscriberList;
    std::mutex subscriberMutex;

public:

    NotificationManager() = default;
    ~NotificationManager() = default;

    void subscribe(int clientSocket);
    void unsubscribe(int clientSocket);
    void broadcast(const nlohmann::json& message);
    void send(int clientSocket, const std::string& message);

};





#endif //NOTIFICATION_MANAGER_H