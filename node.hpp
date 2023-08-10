#ifndef NODE
#define NODE
#include <string>
#include <time.h>

class Node {
private:
    std::string m_description;
    std::string m_status; 
    time_t m_dedline;

public:
    Node(const std::string& description, const std::string& status, time_t time);

    std::string get_description() const;
    std::string get_status() const;
    time_t get_dedline() const;

    void set_description(const std::string& description);
    void set_status(const std::string& status);
    void set_dedline(time_t time);
};

#endif
