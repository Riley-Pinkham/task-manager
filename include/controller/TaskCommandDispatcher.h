#ifndef TASK_COMMAND_DISPATCHER_H
#define TASK_COMMAND_DISPATCHER_H


#include "NotificationManager.h"
#include "CommandModels.h"
#include "TaskService.h"
#include "external/json.hpp"

using json = nlohmann::json;

class TaskCommandDispatcher
{
private:

    TaskService& service;
    NotificationManager& notifier;

    json handleCreateTask(const CreateTaskCommand& createCmd);
    json handleGetTask(const GetTaskCommand& getCmd);

    
public:
    TaskCommandDispatcher(TaskService& service, NotificationManager& notifier)
        : service(service), notifier(notifier){};
    ~TaskCommandDispatcher() = default;

    json execute(const Command& cmd); //Take in a command type reference. 
};

#endif //TASK_COMMAND_DISPATCHER_H