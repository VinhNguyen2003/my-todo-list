#include "task_manager.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::removeTask(int taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                             [taskId](const Task& task) {
                                 return task.getId() == taskId;
                             });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
    }
}

void TaskManager::updateTask(int taskId, const Task& updatedTask) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [taskId](const Task& task) {
                               return task.getId() == taskId;
                           });
    if (it != tasks.end()) {
        it->setDescription(updatedTask.getDescription());
        it->setDeadline(updatedTask.getDeadline());
        it->setType(updatedTask.getType());
    }
}


void TaskManager::markTaskCompleted(int taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [taskId](const Task& task) {
                               return task.getId() == taskId;
                           });
    if (it != tasks.end()) {
        it->setCompleted(true);
    }
}

void TaskManager::displayTasks() const {
    std::cout << "Today's Tasks:\n";
    displayTasksByType(Task::Type::Day);

    std::cout << "This Week's Tasks:\n";
    displayTasksByType(Task::Type::Week);

    std::cout << "General Tasks:\n";
    displayTasksByType(Task::Type::LongTerm);
}

void TaskManager::displayTasksByType(Task::Type type) const {
    int taskNumber = 1;
    for (const auto& task : tasks) {
        if (task.getType() == type) {
            std::cout << " " << taskNumber << ". " << task.getDescription()
                      << " - ID: " << task.getId() 
                      << ", Deadline: " << timePointToString(task.getDeadline()) 
                      << ", Completed: " << (task.isCompleted() ? "Yes" : "No") << "\n";
            ++taskNumber;
        }
    }
    if (taskNumber == 1) {
        std::cout << " None\n";
    }
}

std::string TaskManager::timePointToString(const std::chrono::system_clock::time_point& tp) const {
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &tm);
    return std::string(buffer);
}

void TaskManager::displayDueTasks() const {
    std::cout << "Tasks Due Soon:\n";
    int taskNumber = 1;
    for (const auto& task : tasks) {
        if (!task.isCompleted() && isDueSoon(task.getDeadline())) {
            std::cout << " " << taskNumber << ". " << task.getDescription()
                      << " - ID: " << task.getId()
                      << " - Deadline: " << timePointToString(task.getDeadline())
                      << ", Completed: " << (task.isCompleted() ? "Yes" : "No") << "\n";
            ++taskNumber;
        }
    }
    if (taskNumber == 1) {
        std::cout << " None\n";
    }
}


void TaskManager::removeExpiredTasks() {
    auto now = std::chrono::system_clock::now();
    auto endOfWeek = nextMondayMidnight();

    tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [now, endOfWeek](const Task& task) {
        if (task.getType() == Task::Type::Day) {
            return now > task.getDeadline();
        }
        if (task.getType() == Task::Type::Week) {
            return now > endOfWeek;
        }
        return false;
    }), tasks.end());
}

void TaskManager::adjustTaskDeadline(int taskId, const std::chrono::system_clock::time_point& newDeadline) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& task) {
        return task.getId() == taskId;
    });
    if (it != tasks.end()) {
        it->setDeadline(newDeadline);
    }
}

std::chrono::system_clock::time_point TaskManager::nextMondayMidnight() {
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t now_c = system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    int daysUntilMonday = (8 - now_tm->tm_wday) % 7;
    if (daysUntilMonday == 0) {
        daysUntilMonday = 7;
    }

    system_clock::time_point nextMonday = now + hours(24 * daysUntilMonday);

    time_t nextMonday_c = system_clock::to_time_t(nextMonday);
    std::tm* nextMonday_tm = std::localtime(&nextMonday_c);
    nextMonday_tm->tm_hour = 0;
    nextMonday_tm->tm_min = 0;
    nextMonday_tm->tm_sec = 0;

    return system_clock::from_time_t(std::mktime(nextMonday_tm));
}


bool TaskManager::isDueSoon(const std::chrono::system_clock::time_point& deadline) const {
    auto now = std::chrono::system_clock::now();
    auto one_week_later = now + std::chrono::hours(24 * 7);

    return (deadline > now && deadline <= one_week_later);
}
