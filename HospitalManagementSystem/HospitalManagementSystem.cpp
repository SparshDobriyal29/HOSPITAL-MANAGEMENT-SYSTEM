#include <iostream>
#include <limits>
#include <string>
#include <mysqlx/xdevapi.h>
#include "patient.h" 
#include "doctor.h"
#include "appointment.h"

using namespace std;

// Function declarations for menus
void manage_patients(mysqlx::Session& db_session);
void manage_doctors(mysqlx::Session& db_session);
void manage_appointments(mysqlx::Session& db_session);

int main() {
    // --- NEW SPLASH SCREEN ---
    cout << "==========================================" << endl;
    cout << "||                                      ||" << endl;
    cout << "||      HOSPITAL MANAGEMENT SYSTEM      ||" << endl;
    cout << "||                                      ||" << endl;
    cout << "||      - Made by Sparsh Dobriyal -     ||" << endl;
    cout << "||                                      ||" << endl;
    cout << "==========================================" << endl << endl;
    // --- END OF SPLASH SCREEN ---

    try {
        const char* password = "1234";

        mysqlx::Session sess("localhost", 33060, "root", password);
        sess.sql("USE hospital_db").execute();
        

        int choice;
        while (true) {
            cout << "\n\n===== MAIN MENU =====" << endl;
            cout << "1. Manage Patients" << endl;
            cout << "2. Manage Doctors" << endl;
            cout << "3. Manage Appointments" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
            case 1: manage_patients(sess); break;
            case 2: manage_doctors(sess); break;
            case 3: manage_appointments(sess); break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                sess.close();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    catch (const mysqlx::Error& err) {
        cerr << "ERROR: " << err << endl;
    }

    cout << "\nPress Enter to exit.";
    cin.get();
    cin.get();
    return 0;
}

// The rest of the management functions (manage_patients, manage_doctors, etc.) remain the same...

void manage_patients(mysqlx::Session& db_session) {
    int choice;
    while (true) {
        cout << "\n--- Patient Management ---" << endl;
        cout << "1. Add New Patient" << endl;
        cout << "2. Find Patient by ID" << endl;
        cout << "3. Update Patient Details" << endl;
        cout << "4. Delete Patient" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 5) return;
        switch (choice) {
        case 1: {
            Patient p;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Name: ";
            getline(cin, p.name);
            cout << "Enter Age: ";
            cin >> p.age;
            cout << "Enter Gender: ";
            cin >> p.gender;
            p.save(db_session);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            Patient p = Patient::findById(id, db_session);
            p.display();
            break;
        }
        case 3: {
            int id;
            cout << "Enter Patient ID to update: ";
            cin >> id;
            Patient p = Patient::findById(id, db_session);
            if (p.patient_id != 0) {
                p.display();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nEnter new Name: ";
                getline(cin, p.name);
                cout << "Enter new Age: ";
                cin >> p.age;
                cout << "Enter new Gender: ";
                cin >> p.gender;
                p.update(db_session);
            }
            break;
        }
        case 4: {
            int id;
            cout << "Enter Patient ID to delete: ";
            cin >> id;
            Patient p = Patient::findById(id, db_session);
            if (p.patient_id != 0) {
                p.remove(db_session);
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void manage_doctors(mysqlx::Session& db_session) {
    int choice;
    while (true) {
        cout << "\n--- Doctor Management ---" << endl;
        cout << "1. Add New Doctor" << endl;
        cout << "2. Find Doctor by ID" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 3) return;
        switch (choice) {
        case 1: {
            Doctor d;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Name: ";
            getline(cin, d.name);
            cout << "Enter Specialization: ";
            getline(cin, d.specialization);
            d.save(db_session);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Doctor ID: ";
            cin >> id;
            Doctor d = Doctor::findById(id, db_session);
            d.display();
            break;
        }
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void manage_appointments(mysqlx::Session& db_session) {
    int choice;
    while (true) {
        cout << "\n--- Appointment Management ---" << endl;
        cout << "1. Book New Appointment" << endl;
        cout << "2. View Appointment Details by ID" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 3) return;
        switch (choice) {
        case 1: {
            Appointment app;
            cout << "Enter Patient ID: "; cin >> app.patient_id;
            cout << "Enter Doctor ID: "; cin >> app.doctor_id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Date (YYYY-MM-DD): "; getline(cin, app.appointment_date);
            app.save(db_session);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Appointment ID: "; cin >> id;
            Appointment::findById(id, db_session);
            break;
        }
        default: cout << "Invalid choice." << endl;
        }
    }
}