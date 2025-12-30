#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>




#include "Column.h"
#include "Task.h"
#include "ITaskRepository.h"
#include "TaskRepository.h"
#include "TaskService.h"


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
    taskService.createTask("Do Dishes", "Dont forget to dry and put away", Task::Priority::YELLOW_MEDIUM, "Riley");

    Task someTask = taskService.getTask(5);

    someTask.printTask();


    sqlite3_close(db);

    return 0;
}