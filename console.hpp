#ifndef CONSOLE
#define CONSOLE

#include "node.hpp"
#include "todo.hpp"

#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

void display_menu()
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "|        Todo List        |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "|1. Create Task           |" << std::endl;
    std::cout << "|2. Update Task           |" << std::endl;
    std::cout << "|3. Delete Task           |" << std::endl;
    std::cout << "|4. Mark as Done          |" << std::endl;
    std::cout << "|5. Display Tasks         |" << std::endl;
    std::cout << "|0. Exit                  |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

void play()
{
        Todo todo;

        int choice {0};

        while (true) {
                display_menu();

                std::cin >> choice;

                if(choice == 0) {
                        break;
                } else if(choice == 1) {
                        // std::string description;
                        // std::cout << "Enter task description: ";
                        // std::cin.ignore(); // Add this line to clear the input buffer
                        // std::getline(std::cin, description);

                        // std::string deadline;
                        // std::cout << "Enter deadline (Unix timestamp): ";
                        // std::cin >> deadline;
                        // std::tm* timeinfo = std::gmtime(&deadline);
                        // char timeStr[80];
                        // strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
                        
                        // todo.add(description, deadline);

                        std::string description;
                        std::cout << "Enter task description: ";
                        std::cin.ignore(); // Clear the input buffer
                        std::getline(std::cin, description);

                        std::string deadlineStr;
                        std::cout << "Enter deadline (YYYY-MM-DD HH:MM:SS): ";
                        std::getline(std::cin, deadlineStr);

                        std::tm timeinfo = {};
                        std::istringstream iss(deadlineStr);
                        iss >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

                        if (iss.fail()) {
                        std::cout << "Invalid deadline format. Please use YYYY-MM-DD HH:MM:SS." << std::endl;
                        } else {
                        time_t deadline = std::mktime(&timeinfo);
                        if (deadline == -1) {
                                std::cout << "Error converting deadline to time_t." << std::endl;
                        } else {
                                // Now 'deadline' holds the time_t value for the entered deadline
                                todo.add(description, deadline);
                        }
                        }
                } else if(choice == 2) {
                        int index;
                        std::cout << "Enter task index to update: ";
                        std::cin >> index;

                        std::string newDescription;
                        std::cout << "Enter new task description: ";
                        std::cin.ignore(); 
                        std::getline(std::cin, newDescription);

                        todo.modify_task(index, newDescription);
                } else if(choice == 3) {
                        int index;
                        std::cout << "Enter task index to delete: ";
                        std::cin >> index;

                        todo.remove(index - 1);
                } else if(choice == 4) {
                        int index;
                        std::cout << "Enter task index to mark as done: ";
                        std::cin >> index;

                        todo.done(index - 1);
                } else if(choice == 5) {
                        todo.print();
                } else {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
        }
}

#endif
