#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>




#include "Column.h"
#include "Task.h"
#include "ITaskRepository.h"
#include "TaskRepository.h"
#include "TaskService.h"
#include "CommandModels.h"
#include "CommandSerializer.h"


std::string readSchemaFile(const std::string& filepath) {
    std::ifstream file (filepath);
    if (!file.is_open()){
        std::cerr << "an error occurred" << std::endl;
        return "";
    }

    std::string line;
    std::string schemaSql;
    while (std::getline(file, line)) {
        schemaSql += line + "\n";
    }

    return schemaSql;

}


int main(int argc, char* argv[]) {

    sqlite3* db;
    int returnCode = sqlite3_open("task_manager.db", &db);
    if (returnCode) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const std::string schemaSql = readSchemaFile("db/schema.sql");

    // std::cout << "Schema SQL: " << std::endl << schemaSql << std::endl;

    int rc = sqlite3_exec(db, schemaSql.c_str(), NULL, 0, NULL);

    // 1. CREATE the repository object first (after db exists of course)
    TaskRepository taskRepo;

    // 2. THEN pass its address to the service
    TaskService taskService(&taskRepo);// give the address of. Pass by pointer. we can do this because TaskService used the ITaskRepository. Implicitly converts: TaskRepository* → ITaskRepository*. This accepts any implementation of the ITaskRepository

    // 3. NOW I can use the service
    taskService.createTask("Do Dishes please", "Dont forget to dry and put away please", Task::Priority::YELLOW_MEDIUM, "Riley isTheBest");

    Task someTask = taskService.getTask(6);

    someTask.printTask();


    const GetTaskCommand myGTC(42);

    const CreateTaskCommand myCTC("My Title", "My Description", Task::Priority::RED_URGENT, "Riley Pinkham");


   //std::cout << CommandSerializer::toJsonString(myCTC) << std::endl;

   std::string jsonString = "{\"assignee\": \"Riley Pinkham\",\"command\": \"CREATE_TASK\",\"description\": \"My Description\",\"priority\": \"RED_URGENT\",\"title\": \"My Title\"}";

   Command* cmd = CommandSerializer::fromJsonString(jsonString);

   if(cmd->getType() == CommandType::CREATE_TASK)
   {
        CreateTaskCommand* myCTCptr = static_cast<CreateTaskCommand*>(cmd);
        std::cout << "title: " << myCTCptr->title << " description: " << myCTCptr->description << " priority: " << Task::priorityToString(myCTCptr->priority) << " assignee: " << myCTCptr->assignee << std::endl;
   }

   delete cmd;

    sqlite3_close(db);

    return 0;
}