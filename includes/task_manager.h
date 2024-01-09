#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "task.h"
#include <vector>
#include <string>
#include <chrono>

class TaskManager {
    std::vector<Task> tasks;

public:
    void addTask(const Task& task);
    void removeTask(const std::string& description);
    void updateTask(const std::string& description, const Task& updatedTask);
    void markTaskCompleted(const std::string& description);
    void displayTasks() const;
    void displayDueTasks() const;
    void removeExpiredTasks();
    void adjustTaskDeadline(const std::string& description, const std::chrono::system_clock::time_point& newDeadline);

private:
    std::chrono::system_clock::time_point nextMondayMidnight();
    std::string timePointToString(const std::chrono::system_clock::time_point& tp) const;
    void displayTasksByType(Task::Type type) const;
    bool isDueSoon(const std::chrono::system_clock::time_point& deadline) const;
};

#endif
