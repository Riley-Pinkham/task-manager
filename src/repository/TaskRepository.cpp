#include "TaskRepository.h"
#include "Task.h"
#include <string>


TaskRepository::TaskRepository(/* args */)
{
}

TaskRepository::~TaskRepository()
{
}

bool TaskRepository::createTask(const Task& newTask) {
    std::string sql = "INSERT INTO Task (title, description, priority, assignee) VALUES ('" +
                      newTask.getTitle() + "', '" +
                      newTask.getDescription() + "', '" +
                      newTask.getPriority() + "', '" +
                      newTask.getAssignee() + "');";


    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("task_manager.db", &db);
    if (rc) {
        sqlite3_close(db);
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    // NOTE to self: Think of each SQL statement as a separate computer program. The original SQL text is source code. A prepared statement object is the compiled object code. All SQL must be converted into a prepared statement before it can be run.
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, NULL); // NOTE to self: the sqlite3_exec() function is a convenience wrapper that internally performs the entire lifecycle of an SQL statement execution, which includes preparing (compiling), running, and destroying the prepared statement object. 
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_close(db);
    std::cout << "Task created successfully" << std::endl;
    return true;
}

//callback function is called once per row
static int callback(void* data, int i, char** argc, char** argCol){
    // Do stuff here 
    //id, title, description, priority, assignee

    Task* task = reinterpret_cast<Task*>(data); //

    // Modify the object through the pointer - this should be SAFE
    task->setTaskID(std::atoi(argc[0]));
    task->setTitle(argc[1]);
    task->setDescription(argc[2]);
    // Convert string to Priority enum
    std::string priorityStr = argc[3];
    Task::Priority priority = Task::Priority::GREEN_LOW; // default
    if (priorityStr == "GREEN_LOW") {
        priority = Task::Priority::GREEN_LOW;
    } else if (priorityStr == "YELLOW_MEDIUM") {
        priority = Task::Priority::YELLOW_MEDIUM;
    } else if (priorityStr == "ORANGE_HIGH") {
        priority = Task::Priority::ORANGE_HIGH;
    } else if (priorityStr == "RED_URGENT") {
        priority = Task::Priority::RED_URGENT;
    }
    task->setPriority(priority);
    task->setAssignee(argc[4]);

    return 0;
}

Task TaskRepository::readTask(unsigned int taskID) {

    const char* data = "Some Sort Of Data";

    Task gottenTask; // Stack Object
    void* taskptr = &gottenTask; // Pointer to stack objeck


    std::string sql = "SELECT * FROM Task WHERE id = " + std::to_string(taskID);

    sqlite3* db;
    char* errMsg = 0;
    int rc = sqlite3_open("task_manager.db", &db);
    if (rc) {
        sqlite3_close(db);
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return Task();
    }
    // Here the ptr is passed to the callback function. The callback is modifying the object
    rc = sqlite3_exec(db, sql.c_str(), callback, taskptr, NULL);
        
    // readTask() returns a copy of the modified gottenTask
    return gottenTask;
}   

std::vector<Task> TaskRepository::readAllTasks() const {

    // Implementation here
    return std::vector<Task>();
}

std::vector<Task> TaskRepository::readTasksByColumn(unsigned int columnID) const {
    // Implementation here
    return std::vector<Task>();
}

bool TaskRepository::updateTask(unsigned int taskID, const Task& taskToUpdate) {
    // Implementation here
    return false;
}

bool TaskRepository::deleteTask(unsigned int taskID) {
    // Implementation here
    return false;
}


