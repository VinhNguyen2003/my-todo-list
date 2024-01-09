#include "task.h"

int Task::nextId = 1;
Task::Task(const std::string& desc, 
           const std::chrono::system_clock::time_point& dl, 
           bool comp, Type t)
    : description(desc), deadline(dl), completed(comp), type(t), id(nextId++){}

std::string Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string& desc) {
    description = desc;
}

std::chrono::system_clock::time_point Task::getDeadline() const {
    return deadline;
}

void Task::setDeadline(const std::chrono::system_clock::time_point& dl) {
    deadline = dl;
}

Task::Type Task::getType() const {
    return type;
}

void Task::setType(Type t) {
    type = t;
}

int Task::getId() const { return id; }

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool comp) {
    completed = comp;
}
