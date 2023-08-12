#pragma once

class obj_db {
public:
    obj_db(std::string);
    dump_load_type dump() const;
    void load(const dump_load_type&) const; 
private:
    std::string m_file_name;
};
