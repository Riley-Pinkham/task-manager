#ifndef TASK_SERIALIZER_H
#define TASK_SERIALIZER_H

#include "Task.h"
#include "external/json.hpp"
#include <string>

using json = nlohmann::json;


/* 
    At first I want sure why these were static. Then you realize no instance of an object 
    is needed to use these functions. They are utility functions. Call them with the class 
    name and function name TaskSerializer::toJson(someTask); 
*/
class TaskSerializer 
{
public:

    //USER–FACING
    // Convert Task to JSON string
    static std::string toJson(const Task& task);
    
    // Convert JSON string to Task
    static Task fromJson(const std::string& jsonStr);
    
    //INTERNAL
    // Convert Task to json object (for internal use)
    static json toJsonObject(const Task& task);
    
    // Convert json object to Task (for internal use)
    static Task fromJsonObject(const json& j);
};

#endif // TASK_SERIALIZER_H
