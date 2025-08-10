#pragma once
#include <string>
#include <mysqlx/xdevapi.h>

class Appointment {
public:
    int appointment_id;
    int patient_id;
    int doctor_id;
    std::string appointment_date;

    void save(mysqlx::Session& db_session);
    static void findById(int id, mysqlx::Session& db_session);
};