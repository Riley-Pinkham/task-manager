#ifndef COMMAND_SERIALIZER_H
#define COMMAND_SERIALIZER_H

#include <string>
#include "CommandModels.h"
#include "external/json.hpp"

using json = nlohmann::json;

// Serializes network commands. Converts Data Transfer Objects to and from JSON 
/**
 * DTO <-> JSON
 * NOTE: a DTO is a simple container used to pass data between different layers of an application
 */
class CommandSerializer {
    // Methods need to be static so we can call them without a class instance. 
    // i.e. we dont need to create the objest like CommandSerializer someCMD; someCMD.toJson()...
    // we can just call CommandSerializer::toJson().... NOTE: may want to use an alais with this class
    static std::string toJsonString(const Command& cmd);
    static Command* fromJsonString(const std::string& jsonStr);
    
    static json toJsonObject(const Command& cmd);
    static Command* fromJsonObject(const json& json);
 



};



#endif //COMMAND_SERIALIZER_H