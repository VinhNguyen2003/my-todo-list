#include "task.h"

Task::Task(const std::string& desc, 
           const std::chrono::system_clock::time_point& dl, 
           bool comp)
    : description(desc), deadline(dl), completed(comp) {}

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

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool comp) {
    completed = comp;
}
