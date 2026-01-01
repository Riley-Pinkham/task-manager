
#include "CommandModels.h"



CreateTaskCommand::CreateTaskCommand(){
    
}

class CreateTaskCommand : public Command {
public:
    std::string title;
    std::string description;
    Task::Priority priority; // Using the Task model's enum
    std::string assignee;
    
    CreateTaskCommand() : Command(CommandType::CREATE_TASK) {};
};

class GetTaskCommand : public Command {
public:
    int id;
    
    GetTaskCommand() : Command(CommandType::GET_TASK) {};
};

