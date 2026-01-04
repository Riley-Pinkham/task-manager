#include "CommandSerializer.h"

std::string CommandSerializer::toJsonString(const Command& cmd) {
    json j = toJsonObject(cmd);
    return j.dump(4); // Pretty print with 4 space indent
}

// delete ptr after command object is used
Command* CommandSerializer::fromJsonString(const std::string& jsonStr) {
    json j = json::parse(jsonStr);
    return fromJsonObject(j);
}

json CommandSerializer::toJsonObject(const Command& cmd) {

    json jsonObj;

    // Check type to know what type to cast cmd to. 
    if(cmd.getType() == CommandType::CREATE_TASK){
        // Alais creation for the exact same memory location. Down casting to derived type(so I can access parameters.)
        const CreateTaskCommand& createTaskRef = static_cast<const CreateTaskCommand&>(cmd);
        std::string priorityStr = Task::priorityToString(createTaskRef.priority);
        jsonObj["command"] = "CREATE_TASK";
        jsonObj["title"] = createTaskRef.title;
        jsonObj["description"] = createTaskRef.description;
        jsonObj["priority"] = priorityStr;
        jsonObj["assignee"] = createTaskRef.assignee;

        return jsonObj;

    } else if(cmd.getType() == CommandType::GET_TASK){
        const GetTaskCommand& getTaskRef = static_cast<const GetTaskCommand&>(cmd);

        jsonObj["command"] = "GET_TASK";
        jsonObj["taskID"] = getTaskRef.id;

        return jsonObj;
    }

    return jsonObj;
}

// delete ptr after command object is used
Command* CommandSerializer::fromJsonObject(const json& jsonObj) {

    std::string cmdStr = jsonObj.at("command");

    if(cmdStr == "CREATE_TASK"){
        std::string priorityStr = jsonObj["priority"].get<std::string>(); // use get<T>() to get string type not json type
        Task::Priority priority = Task::priorityFromString(priorityStr);
        CreateTaskCommand* createCmdPtr = new CreateTaskCommand(
            jsonObj["title"].get<std::string>(), 
            jsonObj["description"].get<std::string>(), 
            priority, 
            jsonObj["assignee"].get<std::string>());

        return createCmdPtr;

    } else if (cmdStr == "GET_TASK"){
        GetTaskCommand* getCmdPtr = new GetTaskCommand(jsonObj["taskID"].get<int>());

        return getCmdPtr;
    }

    return nullptr;
}
