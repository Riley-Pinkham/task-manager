#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include "ITaskRepository.h"
#include <sqlite3.h>

class TaskRepository : public ITaskRepository
{
private:
    /* data */
public:
    TaskRepository();
    ~TaskRepository();      

    // CRUD operations
    // Create
    bool createTask(const Task& newTask) override;

    // Read
    Task readTask(unsigned int taskID) override;
    std::vector<Task> readAllTasks() const override;
    std::vector<Task> readTasksByColumn(unsigned int columnID) const override;

    // Update
    bool updateTask(unsigned int taskID, const Task& taskToUpdate) override;

    // Delete
    bool deleteTask(unsigned int taskID) override;

};

#endif // TASK_REPOSITORY_H
