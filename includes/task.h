#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>

class Task {
    std::string description;
    std::chrono::system_clock::time_point deadline;
    bool completed;

public:
    Task(const std::string& desc, 
         const std::chrono::system_clock::time_point& dl, 
         bool comp = false);

    std::string getDescription() const;
    void setDescription(const std::string& desc);

    std::chrono::system_clock::time_point getDeadline() const;
    void setDeadline(const std::chrono::system_clock::time_point& dl);

    bool isCompleted() const;
    void setCompleted(bool comp);
};

#endif // TASK_H
