#include "node.hpp"

Node::Node(const std::string& description, const std::string& status, time_t time):
        m_description{description},  m_status{status}, m_dedline{time}
{

}

std::string Node::get_description() const {
    return m_description;
}

std::string Node::get_status() const {
    return m_status;
}

time_t Node::get_dedline() const {
    return m_dedline;
}

void Node::set_description(const std::string& messege) {
    m_description = messege;
}

void Node::set_status(const std::string& status) {
    m_status = status;
}

void Node::set_dedline(time_t time) {
    m_dedline = time;
}
