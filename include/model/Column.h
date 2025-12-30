#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include <vector>
#include "Task.h"

class Column
{
private:
    unsigned int ColumnID;
    unsigned int taskCount;
    std::string ColumnName;
    std::vector<Task> tasks;

    /* data */
public:
    Column(const std::string& ColumnName, unsigned int ColumnID, unsigned int taskCount) : ColumnName(ColumnName), ColumnID(ColumnID), taskCount(taskCount) {};
    ~Column();

    std::string getName();
    unsigned int getID();
    unsigned int getTaskCount();
    std::vector<Task> getTasks();

    void setName(const std::string& name);
    void setID(unsigned int id);
    void setTaskCount(unsigned int count);
    void addTask(const Task& task);
};



#endif // COLUMN_H