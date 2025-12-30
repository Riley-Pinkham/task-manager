#ifndef I_TASK_REPOSITORY_H
#define I_TASK_REPOSITORY_H

#include "Task.h"
#include <vector>
#include <optional>



class ITaskRepository
{
public:
    virtual ~ITaskRepository() = default;

    // CRUD operations

    // Create
    virtual bool createTask(const Task& newTask) = 0;
    // Read
    virtual Task readTask(unsigned int taskID) = 0;
    virtual std::vector<Task> readAllTasks() const = 0;
    virtual std::vector<Task> readTasksByColumn(unsigned int columnID) const = 0;
    // Update
    virtual bool updateTask(unsigned int taskID, const Task& taskToUpdate) = 0;
    // Delete
    virtual bool deleteTask(unsigned int taskID) = 0;

};

#endif // I_TASK_REPOSITORY_H