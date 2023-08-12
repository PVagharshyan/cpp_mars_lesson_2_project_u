#pragma once

class Task {
public:
    Task(bool, std::string, std::string);
    void set_completed(bool turn_value);
    void set_time(std::string time);
    void set_task(std::string task);
    std::string get_completed() const;
    std::string get_time() const;
    std::string get_task() const; 
    void print_task() const;
public:
    std::string m_task;
    std::string m_time;
    bool m_is_deleted;
    bool m_is_completed;
};
