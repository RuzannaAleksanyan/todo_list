#include "todo.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstring>

Todo::Todo() 
{
    load_file();
}

void Todo::add(const std::string& description, time_t deadline){
    m_todo.push_back(new Node(description, "unfulfilled", deadline));
    save_file();
}

void Todo::remove(int index) {
    if(index >= 0 && index < m_todo.size()) {
        m_todo.erase(m_todo.begin() + index);
    } else {
        std::cout << "Invalid index." << std::endl;
    }
    save_file();
}

void Todo::modify_task(int index, const std::string& newdescription) {
    if(index >= 0 && index < m_todo.size()) {
        m_todo[index]->set_description(newdescription);
    } else {
        std::cout << "Invalid index." << std::endl;
    }
    save_file();
}

void Todo::print() {
    if(m_todo.size() == 0) {
        std::cout << "File is empty. " << std::endl;
    } else {
        for(int i = 0; i < m_todo.size(); ++i) {
            std::cout << "description: " << m_todo[i]->get_description() << std::endl;
            std::cout << "status:  " << m_todo[i]->get_status() << std::endl;
            std::cout << "deadline: " << m_todo[i]->get_deadline() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Todo::done(int index) {
    if(index >= 0 && index < m_todo.size()) {
        m_todo[index]->set_status("done");
    } else {
        std::cout << "Invalid index" << std::endl;
    }
    save_file();
}

void Todo::completed_task() {
    for(int i = 0; i < m_todo.size(); ++i) {
        if(m_todo[i]->get_status() == "done") {
            std::cout << "description: " << m_todo[i]->get_description() << std::endl;
            std::cout << "status:  " << m_todo[i]->get_status() << std::endl;
            std::cout << "deadline: " << m_todo[i]->get_deadline() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Todo::uncompleted_task() {
    for(int i = 0; i < m_todo.size(); ++i) {
        if(m_todo[i]->get_status() == "unfulfilled") {
            std::cout << "description: " << m_todo[i]->get_description() << std::endl;
            std::cout << "status:  " << m_todo[i]->get_status() << std::endl;
            std::cout << "deadline: " << m_todo[i]->get_deadline() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Todo::save_file() {
    std::ofstream report_file("todo.txt");

    if(report_file.is_open()) {
        for(int i = 0; i < m_todo.size(); ++i) {
            report_file << "description: " << m_todo[i]->get_description() << std::endl;
            report_file << "status:      " << m_todo[i]->get_status() << std::endl;
            char buffer[80];
            time_t t = m_todo[i]->get_deadline();
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
            report_file << "deadline:     " << buffer << std::endl;
            report_file << std::endl;
        }
        report_file.close();
    } else {
        std::cout << "Unable to open report file." << std::endl;
    }
}

void Todo::is_approaching_deadline() const 
{
    time_t current_time = time(nullptr);
    for(int i = 0; i < m_todo.size(); ++i) {
        if((m_todo[i]->get_status() != "done") && (m_todo[i]->get_deadline() - current_time < 24 * 60 * 60)) {
            m_todo[i]->set_description(m_todo[i]->get_description() + "  The deadline is near");
        }
    }
}

void Todo::load_file() {
    std::ifstream load_file("todo.txt");

    if (load_file.is_open()) {
        while (!load_file.eof()) {
            std::string lable;
            std::string description;
            std::string status;
            std::string deadline;
            std::string t;

            load_file >> lable >> description;
            load_file >> lable >> status;
            load_file >> lable >> deadline;
            load_file >> t;
            std::string str = deadline + " " + t;

            time_t time = convert(str);
            if (time != -1) { 
                Node* obj = new Node(description, status, time);
                m_todo.push_back(obj);
            }
        }

        load_file.close();
    } else {
        std::cout << "Unable to open report file." << std::endl;
    }
}

time_t Todo::convert(const std::string& deadline) {
    const char* format = "%Y-%m-%d %H:%M:%S";
    
    struct tm timeStruct;
    memset(&timeStruct, 0, sizeof(struct tm));
    
    timeStruct.tm_isdst = -1; 
    
    if (strptime(deadline.c_str(), format, &timeStruct) == nullptr) {
        return -1;
    }
    
    time_t convertedTime = mktime(&timeStruct);
    
    if (convertedTime == -1) {
        return -1;
    }
    
    return convertedTime;
}
