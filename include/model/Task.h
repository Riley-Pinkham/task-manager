#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <chrono>

class Task
{
private:
    unsigned int taskID;
    std::string title;
    std::string description;
    std::string assignee; 
    // Due date and timer can be implemented using std::chrono types This will be added in future updates

public:
    enum class Priority { GREEN_LOW, YELLOW_MEDIUM, ORANGE_HIGH, RED_URGENT } priority;

    Task(unsigned int taskID = 0, const std::string& title = "", const std::string& description = "", const Priority priority = Priority::GREEN_LOW, const std::string& assignee = "Unassigned")
        : taskID(taskID), title(title), description(description), priority(priority), assignee(assignee) {};
    ~Task();


    std::string getTitle() const;
    std::string getDescription() const;
    std::string getPriority() const;
    std::string getAssignee() const;
    unsigned int getTaskID() const;
    
    void setTaskID(unsigned int id);
    void setAssignee(const std::string& assignee);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setPriority(Priority priority);

    void printTask();

};

#endif // TASK_H