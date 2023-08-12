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
extern const int ASSCI_0;

//def_func

#include "../headers/function_def.h"

int main() {
    obj_db db{"../Tasks.txt"};
    while (true){
        try {
            dump_load_type all_dump = db.dump();
            std::string str_event = "";
            char c_event = 0;
            do{
                std::cout << "create(c), update(u), delete(d), print(p), exit(e)" << std::endl;
                std::getline(std::cin, str_event);
            } while (!check_event(str_event));
            c_event = str_event[0];
            if (c_event == 'u') {
                int counter = 0;
                for (const auto& item: all_dump) {
                    std::cout << counter++ << " : ";
                    item.print_task(); 
                }
                std::string id_task = "";
                while (!check_id(id_task, all_dump.size())) {
                    std::cout << "id: ";
                    std::getline(std::cin, id_task);
                }
                //is completed
                std::string ev_completed = "";
                while (!check_event_completed(ev_completed)) {
                    std::cout << "completed or not([COMPLITED]/[]):";
                    std::getline(std::cin, ev_completed); 
                }
                bool u_com = false;
                if (ev_completed == "[COMPLITED]") {
                    u_com = true;
                }
                all_dump[id_task[0] - ASSCI_0].set_completed(u_com); 
                //time
                std::string ev_time = "";
                while (!check_event_time(ev_time)) {
                    std::cout << "time(hour:minute):";
                    std::getline(std::cin, ev_time); 
                }
                all_dump[id_task[0] - ASSCI_0].set_time(ev_time);
                //task
                std::string ev_task = "";
                std::cout << "task: ";
                std::getline(std::cin, ev_task);
                all_dump[id_task[0] - ASSCI_0].set_task("\""+ ev_task + "\"");
            }
            else if (c_event == 'c') {
                //is completed
                std::string ev_completed = "";
                while (!check_event_completed(ev_completed)) {
                    std::cout << "completed or not([COMPLITED]/[]):";
                    std::getline(std::cin, ev_completed); 
                }
                bool u_com = false;
                if (ev_completed == "[COMPLITED]") {
                    u_com = true;
                } 
                //time
                std::string ev_time = "";
                while (!check_event_time(ev_time)) {
                    std::cout << "time(hour:minute):";
                    std::getline(std::cin, ev_time); 
                }
                //task
                std::string ev_task = "";
                std::cout << "task: ";
                std::getline(std::cin, ev_task);
                all_dump.push_back(Task{u_com, ev_time, "\"" + ev_task + "\""});
            }
            else if (c_event == 'd') {
                int counter = 0;
                for (const auto& item: all_dump) {
                    std::cout << counter++ << " : ";
                    item.print_task(); 
                }
                std::string id_task = "";
                while (!check_id(id_task, all_dump.size())) {
                    std::cout << "id: ";
                    std::getline(std::cin, id_task);
                }
                all_dump.erase(all_dump.begin() + (id_task[0] - ASSCI_0));
            }
            else if (c_event == 'p') {
                int counter = 0;
                for (const auto& item: all_dump) {
                    std::cout << counter++ << " : ";
                    item.print_task(); 
                }
            }
            else {
                break;
            }
            db.load(all_dump);
        }
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }
    return 0;
}


