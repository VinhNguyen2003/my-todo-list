#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>

class Task {
public:
    enum class Type {
        Day,
        Week,
        LongTerm
    };

private:
    std::string description;
    std::chrono::system_clock::time_point deadline;
    Type type;
    bool completed;
    int id;
    static int nextId;

public:
    Task(const std::string& desc, 
         const std::chrono::system_clock::time_point& dl, 
         bool comp = false, Type t);

    std::string getDescription() const;
    void setDescription(const std::string& desc);

    std::chrono::system_clock::time_point getDeadline() const;
    void setDeadline(const std::chrono::system_clock::time_point& dl);

    Type getType() const;
    void setType(Type t);

    bool isCompleted() const;
    void setCompleted(bool comp);

    int getId() const;
};

#endif // TASK_H
