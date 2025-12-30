#include "TaskService.h"



TaskService::TaskService(ITaskRepository* repo)
{
    this->repository = repo;
}

TaskService::~TaskService() {}

bool TaskService::createTask(const std::string& title, const std::string& description, Task::Priority priority, const std::string& assignee)
{

    // validate before creating task object and before creating it in the database. 
    if(!title.empty() && !description.empty() && !assignee.empty())
    {
        Task tempTask(0, title, description, priority, assignee);
        return repository->createTask(tempTask); // repository createTask() returns true upon successful insert. 
    }

    return false;
}



Task TaskService::getTask(unsigned int taskID)
{
    Task tempTask = repository->readTask(taskID);

    // Valid tasks will not have an id of 0
    if(tempTask.getTaskID() == 0){
        std::cout << "Failed to get task with ID: " << taskID << std::endl;

        //Edit in the future to throw and exception. As of now, we just return empty task.
        return tempTask;
    }

    return tempTask;
}