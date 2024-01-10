#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "task.h"
#include <vector>
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>

class TaskManager {
    std::vector<Task> tasks;

public:
    void addTask(const Task& task);
    void removeTask(int taskId);
    void updateTask(int taskId, const Task& updatedTask);
    void markTaskCompleted(int taskId);
    void displayTasks() const;
    void displayDueTasks() const;
    void removeExpiredTasks();
    void adjustTaskDeadline(int taskId, const std::chrono::system_clock::time_point& newDeadline);
    void saveTasksToFile(const std::string& filename);
    void loadTasksFromFile(const std::string& filename);
    std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTime);

private:
    std::chrono::system_clock::time_point nextMondayMidnight();
    std::string timePointToString(const std::chrono::system_clock::time_point& tp) const;
    void displayTasksByType(Task::Type type) const;
    bool isDueSoon(const std::chrono::system_clock::time_point& deadline) const;
};

#endif
