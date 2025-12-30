#include "shared/TaskSerializer.h"

std::string TaskSerializer::toJson(const Task& task) {
    json j = toJsonObject(task);
    return j.dump(4); // Pretty print with 4 space indent
}

Task TaskSerializer::fromJson(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return fromJsonObject(j);
}

json TaskSerializer::toJsonObject(const Task& task) {
    json j;
    j["taskID"] = task.getTaskID();
    j["title"] = task.getTitle();
    j["description"] = task.getDescription();
    j["priority"] = task.getPriority();
    j["assignee"] = task.getAssignee();
    return j;
}

Task TaskSerializer::fromJsonObject(const json& j) {
    unsigned int taskID = j["taskID"];
    std::string title = j["title"];
    std::string description = j["description"];
    std::string assignee = j["assignee"];
    
    // Convert priority string to enum
    std::string priorityStr = j["priority"];
    Task::Priority priority = Task::Priority::GREEN_LOW;
    if (priorityStr == "YELLOW_MEDIUM") {
        priority = Task::Priority::YELLOW_MEDIUM;
    } else if (priorityStr == "ORANGE_HIGH") {
        priority = Task::Priority::ORANGE_HIGH;
    } else if (priorityStr == "RED_URGENT") {
        priority = Task::Priority::RED_URGENT;
    }
    
    return Task(taskID, title, description, priority, assignee);
}
