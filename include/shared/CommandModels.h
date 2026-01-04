#ifndef COMMAND_MODELS_H
#define COMMAND_MODELS_H

#include <string>
#include "Task.h"


/* 
* Commands 
*
*
*/

enum class CommandType {
    CREATE_TASK,
    GET_TASK,
    // ... other commands
};

class Command {
protected:
    CommandType type;
    Command(CommandType type) : type(type) {};
public:    
    virtual ~Command() = default; // Important for polymorphism
    CommandType getType() const { return type; } 
};

/**
 * 
 * @param title
 * @param description
 * @param priority
 * @param assignee
 */
class CreateTaskCommand : public Command {
public:
    std::string title;
    std::string description;
    Task::Priority priority;
    std::string assignee;
    
    /**
     * Maybe add Doxygen commands? 
     * Constructs a CreateTaskCommand with the specified task details.
     * 
     * Initializes the base Command class with CommandType::CREATE_TASK and sets
     * the task properties. 
     * Note: When I was researching the order in the initializer list I found 
     * it does NOT affect the initialization order - They are always initialized 
     * in the order they are declared in the class definition. However, base classes are ALWAYS 
     * initialized before derived class members, regardless of initializer list order.
     * Having the base class initilizer forst makes sense becasue it will be initilized first. 
     */
    CreateTaskCommand(std::string title, std::string description, 
                      Task::Priority priority, std::string assignee) 
        : Command(CommandType::CREATE_TASK), title(title), 
          description(description), priority(priority), assignee(assignee) {}
    ~CreateTaskCommand() = default; 
};

class GetTaskCommand : public Command {
public:
    int id;
    
    GetTaskCommand(int id) : Command(CommandType::GET_TASK), id(id) {};
    ~GetTaskCommand() = default; 
};

#endif // COMMAND_MODELS_H
