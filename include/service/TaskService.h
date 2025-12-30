#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "ITaskRepository.h"


class TaskService 
{
    private:
        ITaskRepository* repository;

    public:
        TaskService(ITaskRepository* repo);
        ~TaskService();

        /*
            Pass by reference refers to the origional string, not a copy. When dealing with longer strings this will increase preformance
            Const promise to not modify the object
            For anything larger than an int that you're just reading use `const Type&`
        
        */
        bool createTask(const std::string& title, 
                        const std::string& description, 
                        Task::Priority priority, 
                        const std::string& assignee);

        
        Task getTask(unsigned int taskID);
        


};
















#endif //TASK_SERVICE_H