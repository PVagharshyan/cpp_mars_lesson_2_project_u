#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../headers/Task.h"

typedef std::vector<std::string> dict;
typedef std::vector<Task> dump_load_type;

#include "../headers/obj_db.h"
#include "../headers/function_def.h"

//obj_db

obj_db::obj_db(std::string file_name) {
    std::ifstream file;
    file.open(file_name);
    if (file.is_open()) {
        std::cout << "File open successfully" << std::endl;
        m_file_name = file_name;
    }
    else {
        throw std::runtime_error("Error: File is not opened!");
    }
    file.close();
}

dump_load_type obj_db::dump() const {  
    std::ifstream file;
    file.open(m_file_name);
    dump_load_type result = {};
    if (file.is_open()) {
        std::string current_line = "";
        while (std::getline(file, current_line)) {
            dict current_line_dict = analysis_single_line(current_line);
            bool completed = false;
            if (current_line_dict[0] == "True") {
                completed = true;
            } 
            result.push_back(Task(
                        completed,
                        current_line_dict[1],
                        current_line_dict[2]
                        ));
        } 
    }
    else {
        throw std::runtime_error("Error: File is not opened!");
    }
    file.close();
    return result;
}

void obj_db::load(const dump_load_type& load_value) const {
    std::ofstream file;
    file.open(m_file_name);
    if (file.is_open()) {
        for (int i = 0;i < load_value.size();++i) {
            std::string completed = load_value[i].get_completed();
            std::string time = load_value[i].get_time();
            std::string task = load_value[i].get_task();
            std::string current_result_str = "{" + completed + "," + time + "," + task + "}";
            if (i != load_value.size() - 1)
                file << current_result_str << std::endl;
            else
                file << current_result_str;
        }
    }
    else {
        throw std::runtime_error("Error: File is not opened!");
    }
    file.close();
}
