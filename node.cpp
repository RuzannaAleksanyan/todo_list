#include "node.hpp"

Node::Node(const std::string& description, const std::string& status, time_t time):
        m_description{description},  m_status{status}, m_deadline{time}
{

}

std::string Node::get_description() const {
    return m_description;
}

std::string Node::get_status() const {
    return m_status;
}

time_t Node::get_deadline() const {
    return m_deadline;
}

void Node::set_description(const std::string& messege) {
    m_description = messege;
}

void Node::set_status(const std::string& status) {
    m_status = status;
}

void Node::set_deadline(time_t time) {
    m_deadline = time;
}
