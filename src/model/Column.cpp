#include "Column.h"


Column::~Column(){}

std::string Column::getName() {
    return ColumnName;
}

unsigned int Column::getID() {
    return ColumnID;
}

unsigned int Column::getTaskCount() {
    return taskCount;
}

std::vector<Task> Column::getTasks() {
    return tasks;
}

void Column::setID(unsigned int id) {
    this->ColumnID = id;
}

void Column::setTaskCount(unsigned int count) {
    this->taskCount = count;
}

void Column::addTask(const Task& task) {
    tasks.push_back(task);
    taskCount = tasks.size();
}

void Column::setName(const std::string& name) {
    this->ColumnName = name;
}