#include "TaskCommandDispatcher.h"


// Shoud call the service
// Consider returning the created task ID in the future. 
json TaskCommandDispatcher::handleCreateTask(const CreateTaskCommand& createCmd){
    json message;
    bool success = service.createTask(createCmd.title, createCmd.description, createCmd.priority, createCmd.assignee);

    if (success) {
        // 2. TRIGGER PUB/SUB: Tell the world a task was created
        //notifier.broadcast("TASK_CREATED", cmd.title);
        message = {{"status", "success"}, {"message", "Task created"}};
        return message;
    }
    
    message = {{"status", "error"}, {"message", "Database insertion failed"}};
    return message;

}

json TaskCommandDispatcher::handleGetTask(const GetTaskCommand& getCmd){
    Task recievedTask = service.getTask(getCmd.id);
    
    if(recievedTask.getTaskID()){
        return {
            {"status", "success"}, 
            {"data", { 
                {"id", recievedTask.getTaskID()}, 
                {"title", recievedTask.getTitle()}, 
                {"description", recievedTask.getDescription()}, 
                {"priority", recievedTask.getPriority()}, 
                {"assignee", recievedTask.getAssignee()}
            }}
        };
    }

    return {{"status", "error"}, {"message", "Task Not Retrieved"}};

}

json TaskCommandDispatcher::execute(const Command& cmd){
    json jsonObj;

    CommandType cmdType = cmd.getType();

    if(cmdType == CommandType::CREATE_TASK){
        return handleCreateTask(static_cast<const CreateTaskCommand&>(cmd));

    } else if (cmdType == CommandType::GET_TASK){
        return handleGetTask(static_cast<const GetTaskCommand&>(cmd));
    } else {
        return {{"status", "error"}, {"message", "Could not execute command"}};
    }

}