#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../headers/Task.h"

typedef std::vector<std::string> dict;
typedef std::vector<Task> dump_load_type;

#include "../headers/obj_db.h"

enum class Time {
    HOUR,
    MINUTE
};
const int ASSCI_0 = 48;
const int max_hour = 23;
const int max_minute = 59;
std::vector<char> events = {'c', 'u', 'd', 'p', 'e'};

dict sep_comma(const std::string& line) {
    std::string current_element = "";
    dict result = {};
    for (int i = 0;i < line.length();++i) {
        if (line[i] != ',') {
            current_element += line[i];
        }
        else {
            if (current_element != "") {
                result.push_back(current_element);
                current_element = ""; 
            }
        }
    }
    if (current_element != "") {
        result.push_back(current_element);
    }
    return result;
} 

bool check_element_completed(const std::string& str_element) {
    std::string str_completed = "";
    if (str_element[0] == '[' && str_element[str_element.length() - 1] == ']'){
        for (int i = 1;i < str_element.length() - 1;++i) {
            str_completed += str_element[i];
        }
        if (str_completed == "COMPLITED") {
            return true;
        }
        else if (str_completed == "") {
            return false;
        }
        else {            
            throw std::runtime_error("Error: There is an error in the relevant \"comlited\" section that you imported");
        }
    }
    else { 
        throw std::runtime_error("Error: Section imported in wrong format!");
    }
}

bool is_number(char c) {
    if (c - ASSCI_0 <= 9 && c + ASSCI_0 >= 0) {
        return true;
    }
    return false;
}

bool check_hour(std::string hour) {
    int result = 0;
    for (int i = 0;i < hour.length();++i) {
        result += hour[i] - ASSCI_0;
        result *= 10;
    }
    if (result/10 <= max_hour) {
        return true;
    }
    return false;
}

bool check_minute(std::string minute) {
    int result = 0;
    for (int i = 0;i < minute.length();++i) {
        result += minute[i] - ASSCI_0;
        result *= 10;
    }
    if (result/10 <= max_minute) {
        return true;
    }
    return false;
}

std::string check_element_time(const std::string& str_element) {
    const int position_endpoint = 2;
    const int currect_len_time = 5;
    if (str_element.length() != currect_len_time) {
        throw std::runtime_error("Error: Time imported in wrong format!");
    }
    if (str_element[position_endpoint] == ':') {
        std::map<Time, std::string> time;
        time[Time::HOUR] = "";
        time[Time::MINUTE] = "";
        for (int i = 0;i < position_endpoint;++i) {
            time[Time::HOUR] += str_element[i];
        }
        for (int i = position_endpoint + 1;i < str_element.length();++i) {
            time[Time::MINUTE] += str_element[i];
        }
        if (check_hour(time[Time::HOUR]) && check_minute(time[Time::MINUTE])) {
            return str_element;
        }
        else {
            throw std::runtime_error("Error: Time imported in wrong format!");
        }
    }
    else {
        throw std::runtime_error("Error: Time imported in wrong format!");
    }
}

std::string check_element_task(std::string str_element) {
    if (str_element[0] == '"' && str_element[str_element.length() - 1] == '"') {
        return str_element;
    }
    else {
        throw std::runtime_error("Error: Task imported in wrong format!");
    }
}

dict analysis_single_line(const std::string& line) {
    std::string str_line = "";
    dict result = {};
    if (line[0] == '{' && line[line.length() - 1] == '}') {
        for (int i = 1;i < line.length() - 1;++i) {
            str_line += line[i];
        }
        result = sep_comma(str_line);
        bool completed = check_element_completed(result[0]);
        if (completed) {
            result[0] = "True";
        }
        else {
            result[0] = "False";
        }
        result[1] = check_element_time(result[1]); 
        result[2] = check_element_task(result[2]);
        return result; 
    }
    else {
        throw std::runtime_error("Error: The file contains a line imported in the wrong format!");
    }
}

bool check_event(std::string ev) {
    if (ev.length() == 1) {
        for (const auto& item: events) {
            if (item == ev[0]) {
                return true; 
            }
        }
    }
    return false;
}

bool check_event_completed(std::string ev) {
    if (ev == "[COMPLITED]" || ev == "[]") {
        return true;
    }
    return false;
}

bool check_id(std::string ev, int limit) {
    if (ev.length() == 1 && is_number(ev[0]) && (ev[0] - ASSCI_0) < limit) {
        return true; 
    }
    return false;
}

bool check_event_time(std::string ev) {
    try{
        check_element_time(ev);
        return true;
    }
    catch (const std::runtime_error& err){
        return false;
    }
}
