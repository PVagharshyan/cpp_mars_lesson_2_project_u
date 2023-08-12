#pragma once

dict sep_comma(const std::string&);
bool check_element_completed(const std::string&);
bool is_number(char);
bool check_hour(std::string);
bool check_minute(std::string);
std::string check_element_time(const std::string&);
std::string check_element_task(std::string);
dict analysis_single_line(const std::string&);
bool check_event(std::string);
bool check_event_completed(std::string);
bool check_id(std::string, int);
bool check_event_time(std::string);
