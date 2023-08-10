#ifndef TODOLIDT
#define TODOLIDT
#include <string>
#include <vector>
#include "node.hpp"

class Todo {
private:
    std::vector<Node*> m_todo;

    void load_file();
    void save_file();
    time_t convert(const std::string& dedline);
    
public:
    Todo();
    ~Todo() = default;

    void add(const std::string& description, time_t dedline);
    void remove(int index);

    void modify_task(int index, const std::string& newdescription);

    void print();

    void done(int index);

    void completed_task();
    void uncompleted_task();
    
    void is_approaching_deadline() const;

};

#endif
