#pragma once
#include <string>
#include <mysqlx/xdevapi.h>

class Doctor {
public:
    int doctor_id;
    std::string name;
    std::string specialization;

    void save(mysqlx::Session& db_session);
    static Doctor findById(int id, mysqlx::Session& db_session);
    void display();
};