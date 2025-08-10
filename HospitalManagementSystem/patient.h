#pragma once
#include <string>
#include <mysqlx/xdevapi.h>

class Patient {
public:
    int patient_id;
    std::string name;
    int age;
    std::string gender;

    void save(mysqlx::Session& db_session);
    static Patient findById(int id, mysqlx::Session& db_session);
    void update(mysqlx::Session& db_session);
    void remove(mysqlx::Session& db_session);
    void display();
};