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
            std::chrono::system_clock::time_point deadlineTp;
            Task::Type type;
            while (true) {
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                if (!description.empty()) {
                    break;
                }
                std::cerr << "Error: Task description cannot be empty. Please enter a description." << std::endl;
            }
            while (true) {
                std::cout << "Enter deadline (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, deadline);
                try {
                    deadlineTp = stringToTimePoint(deadline);
                    break;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << ". Please enter a valid deadline." << std::endl;
                }
            }
            while (true) {
                std::cout << "Enter task type (Day/Week/LongTerm): ";
                std::getline(std::cin, typeStr);

                if (typeStr == "Day") {
                    type = Task::Type::Day;
                    break;
                } else if (typeStr == "Week") {
                    type = Task::Type::Week;
                    break;
                } else if (typeStr == "LongTerm") {
                    type = Task::Type::LongTerm;
                    break;
                } else {
                    std::cerr << "Error: Invalid task type. Choose from Day, Week, LongTerm." << std::endl;
                }
            }
            taskManager.addTask(Task(description, deadlineTp, type, false));
        } else if (command == "remove") {
            int taskId;
            std::cout << "Enter task ID to remove: ";
            std::cin >> taskId;
            std::cin.ignore();
            taskManager.removeTask(taskId);
        } else if (command == "update") {
            int taskId;
            std::cout << "Enter task ID to update: ";
            std::cin >> taskId;
            std::cin.ignore();

            std::string newDescription, newDeadline, newTypeStr;  
            std::chrono::system_clock::time_point newDeadlineTp;
            Task::Type newType;
            while (true) {
                std::cout << "Enter task description: ";
                std::getline(std::cin, newDescription);
                if (!newDescription.empty()) {
                    break;
                }
                std::cerr << "Error: Task description cannot be empty. Please enter a description." << std::endl;
            }
            while (true) {
                std::cout << "Enter deadline (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, newDeadline);
                try {
                    newDeadlineTp = stringToTimePoint(newDeadline);
                    break;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << ". Please enter a valid deadline." << std::endl;
                }
            }
            while (true) {
                std::cout << "Enter task type (Day/Week/LongTerm): ";
                std::getline(std::cin, newTypeStr);

                if (newTypeStr == "Day") {
                    newType = Task::Type::Day;
                    break;
                } else if (newTypeStr == "Week") {
                    newType = Task::Type::Week;
                    break;
                } else if (newTypeStr == "LongTerm") {
                    newType = Task::Type::LongTerm;
                    break;
                } else {
                    std::cerr << "Error: Invalid task type. Choose from Day, Week, LongTerm." << std::endl;
                }
            }
            taskManager.updateTask(taskId, Task(newDescription, newDeadlineTp, newType, false));
        } else if (command == "markComplete") {
            int taskId;
            std::cout << "Enter task ID to mark as complete: ";
            std::cin >> taskId;
            std::cin.ignore();
            taskManager.markTaskCompleted(taskId);
        } else if (command == "display") {
            taskManager.displayTasks();
        } else if (command == "displayDue") {
            taskManager.displayDueTasks();
        } else if (command == "removeExpired") {
            taskManager.removeExpiredTasks();
        } else if (command == "adjustDeadline") {
            int taskId;
            std::string newDeadline;
            std::chrono::system_clock::time_point newDeadlineTp;
            std::cout << "Enter task ID to adjust deadline: ";
            std::cin >> taskId;
            std::cin.ignore();

            while (true) {
                std::cout << "Enter deadline (YYYY-MM-DD HH:MM): ";
                std::getline(std::cin, newDeadline);
                try {
                    newDeadlineTp = stringToTimePoint(newDeadline);
                    break;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << ". Please enter a valid deadline." << std::endl;
                }
            }

            taskManager.adjustTaskDeadline(taskId, newDeadlineTp);
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

std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTime) {
    std::tm tm = {};
    char* ret = strptime(dateTime.c_str(), "%Y-%m-%d %H:%M", &tm);
    if (ret == nullptr) {
        throw std::runtime_error("Invalid date-time format. Expected format: YYYY-MM-DD HH:MM");
    }
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}