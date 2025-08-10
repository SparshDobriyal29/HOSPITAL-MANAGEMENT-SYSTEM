# Hospital Management System in C++

This is a comprehensive, console-based Hospital Management System created using C++. It connects to a MySQL database to manage records for patients, doctors, and appointments, featuring a full suite of CRUD (Create, Read, Update, Delete) operations.

## Key Features

* **Modular Design:** The project is organized into separate modules for Patients, Doctors, and Appointments, each with its own class (`.h`) and implementation (`.cpp`) files.
* **Database Integration:** Uses the official MySQL Connector/C++ (X DevAPI) to connect to a MySQL database, ensuring all data is persistent.
* **Full CRUD Functionality:**
    * **Create:** Add new patients and doctors to the database.
    * **Read:** Search for specific patients or doctors by their unique ID.
    * **Update:** Modify the details of existing records.
    * **Delete:** Remove records from the database.
* **Relational Data:** An `appointments` table links patients and doctors using **Foreign Keys**, demonstrating a relational database schema.
* **Interactive Menu:** A user-friendly, menu-driven interface allows for easy navigation and management of all operations.

## Technologies Used

* **Language:** C++
* **Database:** MySQL
* **Connector:** MySQL Connector/C++ 9.4.0 (using the X DevAPI)
* **IDE:** Visual Studio 2022

## Setup and Installation

1.  **Prerequisites:**
    * Visual Studio 2022 with the "Desktop development with C++" workload.
    * MySQL Server and MySQL Workbench.
    * MySQL Connector/C++ 9.4.0.

2.  **Database Setup:**
    * In MySQL Workbench, create a new schema named `hospital_db`.
    * Run the following SQL script to create the necessary tables:
        ```sql
        USE hospital_db;

        CREATE TABLE patients (
            patient_id INT PRIMARY KEY AUTO_INCREMENT,
            name VARCHAR(255) NOT NULL,
            age INT,
            gender VARCHAR(10)
        );

        CREATE TABLE doctors (
            doctor_id INT PRIMARY KEY AUTO_INCREMENT,
            name VARCHAR(255) NOT NULL,
            specialization VARCHAR(255)
        );
        ```

3.  **Project Configuration:**
    * Open the `.sln` file in Visual Studio.
    * Set the configuration to **Release | x64**.
    * In **Project Properties**, configure the `Additional Include Directories`, `Additional Library Directories`, and `Additional Dependencies` to point to your MySQL Connector/C++ installation.
    * Copy the required `.dll` files from the connector's `lib64` folder to the project's output directory (`x64/Release`).

## Usage

Once the project is built, run the `.exe` file. The main menu will appear, allowing you to navigate through the patient and doctor management systems.
