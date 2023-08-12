#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../headers/Task.h"

//Task

Task::Task(bool completed, std::string time, std::string task) 
    :m_is_completed(completed), m_time(time), m_task(task), m_is_deleted(false)
{}

void Task::set_completed(bool turn_value) {
    m_is_completed = turn_value;
}

void Task::set_time(std::string time) {
    m_time = time;
}

void Task::set_task(std::string task) {
    m_task = task;
}

std::string Task::get_completed() const {
    if (m_is_completed == true) {
        return "[COMPLITED]";      
    }
    return "[]";
}

std::string Task::get_time() const {
    return m_time;
}

std::string Task::get_task() const {
    return m_task;
}

void Task::print_task() const {
    std::string completed = "";
    std::string time = m_time;
    std::string task = m_task;
    if (m_is_completed) {
        completed = "[COMPLITED]";
    }
    else {
        completed = "[         ]";
    }
    std::string current_task = completed + ",\t" + time + ",\t" + task;
    std::cout << current_task << std::endl;
}
