#include "appointment.h"
#include <iostream>

using namespace std;

void Appointment::save(mysqlx::Session& db_session) {
    try {
        mysqlx::Table app_table = db_session.getSchema("hospital_db").getTable("appointments");
        app_table.insert("patient_id", "doctor_id", "appointment_date")
            .values(this->patient_id, this->doctor_id, this->appointment_date).execute();
        cout << "\nSUCCESS: Appointment booked." << endl;
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR booking appointment: " << err << endl;
    }
}

// This function shows the power of JOINs
void Appointment::findById(int id, mysqlx::Session& db_session) {
    try {
        // A raw SQL query is best for complex JOINs
        string query = "SELECT a.appointment_id, p.name, d.name, a.appointment_date "
            "FROM appointments a "
            "JOIN patients p ON a.patient_id = p.patient_id "
            "JOIN doctors d ON a.doctor_id = d.doctor_id "
            "WHERE a.appointment_id = " + to_string(id);

        mysqlx::SqlResult result = db_session.sql(query).execute();
        mysqlx::Row row = result.fetchOne();

        if (row) {
            cout << "\n--- Appointment Details ---" << endl;
            cout << "Appointment ID: " << (int)row[0] << endl;
            cout << "Patient Name: " << (string)row[1] << endl;
            cout << "Doctor Name: " << (string)row[2] << endl;
            cout << "Date: " << (string)row[3] << endl;
        }
        else {
            cout << "\nINFO: No appointment found with ID: " << id << endl;
        }
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR displaying appointment details: " << err << endl;
    }
}