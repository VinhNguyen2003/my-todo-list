#include "task_manager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTime);
void printHelp();

int main() {
    TaskManager taskManager;
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "quit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else if (command == "add") {
            std::string description, deadline, typeStr;
            Task::Type type;
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter deadline (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, deadline);
            std::cout << "Enter task type (Day/Week/LongTerm): ";
            std::getline(std::cin, typeStr);

            if (typeStr == "Day") {
                type = Task::Type::Day;
            } else if (typeStr == "Week") {
                type = Task::Type::Week;
            } else {
                type = Task::Type::LongTerm;
            }
            taskManager.addTask(Task(description, stringToTimePoint(deadline), false, type));
        } else if (command == "remove") {
            // Implement task removal logic
        } else if (command == "update") {
            std::string description, newDescription, newDeadline, newTypeStr;
            Task::Type newType;
            std::cout << "Enter current task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter new task description: ";
            std::getline(std::cin, newDescription);
            std::cout << "Enter new deadline (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, newDeadline);
            std::cout << "Enter new task type (Day/Week/LongTerm): ";
            std::getline(std::cin, newTypeStr);

            if (newTypeStr == "Day") {
                newType = Task::Type::Day;
            } else if (newTypeStr == "Week") {
                newType = Task::Type::Week;
            } else {
                newType = Task::Type::LongTerm;
            }
            taskManager.updateTask(description, Task(newDescription, stringToTimePoint(newDeadline), false, newType));
        } else if (command == "markComplete") {
            // Implement mark task as completed logic
        } else if (command == "display") {
            taskManager.displayTasks();
        } else if (command == "displayDue") {
            taskManager.displayDueTasks();
        } else if (command == "removeExpired") {
            taskManager.removeExpiredTasks();
        } else if (command == "adjustDeadline") {
            // Implement deadline adjustment logic
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}

void printHelp() {
    std::cout << "Commands:\n"
              << "  add - Add a new task\n"
              << "  remove - Remove an existing task\n"
              << "  update - Update an existing task\n"
              << "  markComplete - Mark a task as completed\n"
              << "  display - Display all tasks\n"
              << "  displayDue - Display tasks that are due soon\n"
              << "  removeExpired - Remove expired tasks\n"
              << "  adjustDeadline - Adjust the deadline of a task\n"
              << "  quit - Exit the program\n";
}
