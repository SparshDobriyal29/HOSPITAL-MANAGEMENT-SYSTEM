#include "doctor.h"
#include <iostream>

using namespace std;

void Doctor::save(mysqlx::Session& db_session) {
    try {
        mysqlx::Table doctors_table = db_session.getSchema("hospital_db").getTable("doctors");
        doctors_table.insert("name", "specialization")
            .values(this->name, this->specialization).execute();
        cout << "\nSUCCESS: Doctor '" << this->name << "' saved." << endl;
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR saving doctor: " << err << endl;
    }
}

Doctor Doctor::findById(int id, mysqlx::Session& db_session) {
    Doctor d;
    d.doctor_id = 0;
    try {
        mysqlx::Table doctors_table = db_session.getSchema("hospital_db").getTable("doctors");
        mysqlx::RowResult result = doctors_table.select("*").where("doctor_id = :id").bind("id", id).execute();
        mysqlx::Row row = result.fetchOne();
        if (row) {
            d.doctor_id = (int)row[0];
            d.name = (string)row[1];
            d.specialization = (string)row[2];
        }
        else {
            cout << "\nINFO: No doctor found with ID: " << id << endl;
        }
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR finding doctor: " << err << endl;
    }
    return d;
}

void Doctor::display() {
    if (doctor_id == 0) return;
    cout << "\n--- Doctor Details ---" << endl;
    cout << "Doctor ID: " << doctor_id << endl;
    cout << "Name: " << name << endl;
    cout << "Specialization: " << specialization << endl;
}