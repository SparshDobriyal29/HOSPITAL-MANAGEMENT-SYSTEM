#include "patient.h"
#include <iostream>

using namespace std;

void Patient::save(mysqlx::Session& db_session) {
    try {
        mysqlx::Table patients_table = db_session.getSchema("hospital_db").getTable("patients");
        patients_table.insert("name", "age", "gender")
            .values(this->name, this->age, this->gender).execute();
        cout << "\nSUCCESS: Patient '" << this->name << "' saved." << endl;
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR saving patient: " << err << endl;
    }
}

Patient Patient::findById(int id, mysqlx::Session& db_session) {
    Patient p;
    p.patient_id = 0;
    try {
        mysqlx::Table patients_table = db_session.getSchema("hospital_db").getTable("patients");
        mysqlx::RowResult result = patients_table.select("*").where("patient_id = :id").bind("id", id).execute();
        mysqlx::Row row = result.fetchOne();
        if (row) {
            p.patient_id = (int)row[0];
            p.name = (string)row[1];
            p.age = (int)row[2];
            p.gender = (string)row[3];
        }
        else {
            cout << "\nINFO: No patient found with ID: " << id << endl;
        }
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR finding patient: " << err << endl;
    }
    return p;
}

void Patient::update(mysqlx::Session& db_session) {
    try {
        mysqlx::Table patients_table = db_session.getSchema("hospital_db").getTable("patients");
        patients_table.update()
            .set("name", this->name)
            .set("age", this->age)
            .set("gender", this->gender)
            .where("patient_id = :id").bind("id", this->patient_id).execute();
        cout << "\nSUCCESS: Patient ID " << this->patient_id << " updated." << endl;
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR updating patient: " << err << endl;
    }
}

void Patient::remove(mysqlx::Session& db_session) {
    try {
        mysqlx::Table patients_table = db_session.getSchema("hospital_db").getTable("patients");
        patients_table.remove().where("patient_id = :id").bind("id", this->patient_id).execute();
        cout << "\nSUCCESS: Patient ID " << this->patient_id << " removed." << endl;
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR removing patient: " << err << endl;
    }
}

void Patient::display() {
    if (patient_id == 0) return;
    cout << "\n--- Patient Details ---" << endl;
    cout << "Patient ID: " << patient_id << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
}