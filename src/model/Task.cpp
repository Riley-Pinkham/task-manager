#include "Task.h"




Task::~Task() {}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const{
    return description;
}

unsigned int Task::getTaskID() const {
    return taskID;
}

std::string Task::getAssignee() const {
    return assignee;
}

std::string Task::getPriority() const {
    switch (priority) {
        case Priority::GREEN_LOW:
            return "GREEN_LOW";
        case Priority::YELLOW_MEDIUM:
            return "YELLOW_MEDIUM";
        case Priority::ORANGE_HIGH:
            return "ORANGE_HIGH";
        case Priority::RED_URGENT:
            return "RED_URGENT";
        default:
            return "UNKNOWN";
    }
}

void Task::setPriority(Priority priority) {
    this->priority = priority;
}

void Task::setTaskID(unsigned int id) {
    this->taskID = id;
}

void Task::setAssignee(const std::string& assignee) {
    this->assignee = assignee;
}

void Task::setTitle(const std::string& title) {
    this->title = title;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::printTask(){
    //title description priority
    std::cout << "id: " << this->taskID << " title: " << this->title << " description: " << this->description << " priority: " << this->getPriority() << std::endl;
}