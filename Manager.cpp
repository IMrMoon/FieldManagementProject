//
// Created by sgvch on 25/02/2024.
//

#include "Manager.h"
#include "SQLiteCpp/Database.h"
#include "Validation.h"




void view_field_orders(std::string manager_id) {
    // TODO: check first for that manager which lot
    //  is responsible for which we want to print the orders for that lot
    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare the SQL query to get fields managed by the specified manager
        std::string fields_query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
        SQLite::Statement fields_query(db, fields_query_str);
        fields_query.bind(1, manager_id);

        std::string field_ids = "";
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0);
            field_ids += std::to_string(field_id) + ",";
        }

        // Remove the last comma
        if (!field_ids.empty()) {
            field_ids.pop_back();
        }

        // Prepare the SQL query to get orders for the fields managed by the manager
        std::string orders_query_str = "SELECT * FROM Orders WHERE FieldId IN (" + field_ids + ")";
        SQLite::Statement orders_query(db, orders_query_str);

        // Execute the query and print the results
        std::cout << "Orders for Manager ID: " << manager_id << std::endl;
        while (orders_query.executeStep()) {
            int order_id = orders_query.getColumn(0);
            int field_id = orders_query.getColumn(1);
            std::string order_date = orders_query.getColumn(2);
            std::string other_details = orders_query.getColumn(3);

            std::cout << "Order ID: " << order_id << ", Field ID: " << field_id << ", Order Date: " << order_date << ", Other Details: " << other_details << std::endl;
        }

        std::cout << "Done." << std::endl;
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

string manager_register() {
    std::string manager_id, manager_name, manager_email, manager_phone_number, manager_password;
    char manager_gender;
    bool id_exists = false;
    bool email_exists = false;
    bool phone_number_exists = false;

    do {
        std::cout << "Enter Manager ID (up to 9 digits): ";
        std::cin >> manager_id;
        if (!check_id(manager_id)) {
            std::cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
        } else if (!check_existing_id(manager_id)) {
            std::cout << "Invalid ID. This ID already exists, try again." << std::endl;
            id_exists = true;
        } else {
            id_exists = false;
        }
    } while (!check_id(manager_id) || id_exists);

    // Clearing input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        // Getting name
        std::cout << "Enter Manager Name with upper case in first name and last name: ";
        getline(std::cin, manager_name);
        if (!check_name(manager_name)) {
            std::cout
                    << "Invalid Name. Please enter a valid Name with upper case in first letter in first name and upper case in first letter in last name."
                    << std::endl;
        }
    } while (!check_name(manager_name));

    do {
        // Getting email
        std::cout << "Enter Manager Email in format: user@example.com: ";
        getline(std::cin, manager_email);
        if (!check_email(manager_email)) {
            std::cout << "Invalid Email. Please enter a valid Email in the format: user@example.com." << std::endl;
        } else if (!check_existing_email(manager_email)) {
            std::cout << "Invalid Email. This Email already exists, try again." << std::endl;
            email_exists = true;
        } else {
            email_exists = false;
        }
    } while (!check_email(manager_email) || email_exists);

    do {
        // Getting phone number
        std::cout << "Enter Manager Phone Number no more than 10 digits: ";
        getline(std::cin, manager_phone_number);
        if (!check_phone_number(manager_phone_number)) {
            std::cout << "Invalid Phone Number. Please enter a valid phone number no more than 10 digits." << std::endl;
        } else if (!check_existing_phone_number(manager_phone_number)) {
            std::cout << "Invalid Phone number. This Phone number already exists, try again." << std::endl;
            phone_number_exists = true;
        } else {
            phone_number_exists = false;
        }
    } while (!check_phone_number(manager_phone_number) || phone_number_exists);

    do {
        // Getting password
        std::cout << "Enter Manager Password: ";
        getline(std::cin, manager_password);
        if (!check_password(manager_password)) {
            std::cout << "Invalid Password. Please enter a valid Password." << std::endl;
        }
    } while (!check_password(manager_password));

    do {
        // Getting gender
        std::cout << "Enter Manager Gender: M/F: ";
        std::cin >> manager_gender;
        if (!check_gender(manager_gender)) {
            std::cout << "Invalid Gender. Please enter a valid Gender M/F." << std::endl;
        }
    } while (!check_gender(manager_gender));

    // Prepare a statement to insert a new manager into the Managers table
    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Prepare a statement to insert a new manager into the Managers table
        SQLite::Statement query(db,
                                "INSERT INTO Managers (Id, Name, Email, \"Phone number\", Password, Gender) VALUES (?, ?, ?, ?, ?, ?)");

        // Bind parameters to the statement
        int integer_id = std::stoi(manager_id);
        int integer_phoneNum = std::stoi(manager_phone_number);
        query.bind(1, integer_id);
        query.bind(2, manager_name);
        query.bind(3, manager_email);
        query.bind(4, integer_phoneNum);
        query.bind(5, manager_password);
        query.bind(6, manager_gender);

        // Execute the statement
        query.exec();

        // Close the database (optional if you're done with the database)

    } catch (std::exception &e) {
        // Handle exceptions (e.g., print error message)
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }

    return manager_id;
}

string manager_login() {
        std::string manager_id, manager_password, name;
        bool id_exists = false;
        do {
            std::cout << "Enter your ID (up to 9 digits): ";
            std::cin >> manager_id;
            if (!check_id(manager_id)) {
                std::cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
            }
            if (!check_existing_id(manager_id)) {
                try {
                    std::cout << "Enter your Password: ";
                    std::cin >> manager_password;
//                    std::cin.ignore(); // Clear the input buffer
//                    std::getline(std::cin, manager_password); // Read password with getline
                    // Open the database
                    SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

                    // Prepare SQL query to retrieve the name and password based on the ID
                    SQLite::Statement query(db, "SELECT Name, Password FROM Manager WHERE Id = ?");
                    query.bind(1, manager_id); // Bind the ID parameter

                    // Execute the query
                    if (query.executeStep()) {
                        // Retrieve the name and password from the result set
                        name = query.getColumn(0).getText();
                        std::string stored_password = query.getColumn(1).getText();

                        // Check if the entered password matches the stored password
                        if (manager_password == stored_password) {
                            std::cout << "Welcome, " << name << "! You are now logged in as a Manager." << std::endl;
                            id_exists = true; // Return the manager ID if login is successful
                        } else {
                            std::cout << "Invalid Password. Please try again." << std::endl;
                        }
                    } else {
                            std::cout << "Manager ID not found. Please try again." << std::endl;
                    }
                } catch (std::exception &e) {
                    std::cerr << "SQLite exception: " << e.what() << std::endl;
                }
            } else {
                std::cout << "Manager ID does not exist. Please try again." << std::endl;
            }
        } while (!check_id(manager_id) || !id_exists);

        return manager_id; // Return empty string if login is unsuccessful
    }

void view_orders_by_date(std::string manager_id) {

        try {
            // Open the SQLite database
            SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

            // Prepare the SQL query to get fields managed by the specified manager
            std::string fields_query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
            SQLite::Statement fields_query(db, fields_query_str);
            fields_query.bind(1, manager_id);

            std::string field_ids = "";
            while (fields_query.executeStep()) {
                int field_id = fields_query.getColumn(0);
                field_ids += std::to_string(field_id) + ",";
            }

            // Remove the last comma
            if (!field_ids.empty()) {
                field_ids.pop_back();
            }

            // Prepare the SQL query to get orders for the fields managed by the manager
            std::string orders_query_str = "SELECT * FROM Orders WHERE FieldId IN (" + field_ids + ") ORDER BY Orderdate";
            SQLite::Statement orders_query(db, orders_query_str);

            // Execute the query and print the results
            std::cout << "Orders for Manager ID: " << manager_id << " (sorted by Order Date)" << std::endl;
            while (orders_query.executeStep()) {
                int order_id = orders_query.getColumn(0);
                int field_id = orders_query.getColumn(5);
                std::string order_date = orders_query.getColumn(2);
                std::string other_details = orders_query.getColumn(4);

                std::cout << "Order ID: " << order_id << ", Field ID: " << field_id << ", Order Date: " << order_date << ", Other Details: " << other_details << std::endl;
            }

            std::cout << "Done." << std::endl;
        } catch (std::exception& e) {
            std::cerr << "SQLite exception: " << e.what() << std::endl;
        }
    }

void mark_dates_as_unavailable(std::string manager_id, int field_id, std::string order_date, std::string start_time, std::string end_time) {
    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare the SQL query to insert the order
        std::string insert_query_str = "INSERT INTO Orders (ManagerId, FieldId, OrderDate, StartTime, EndTime) VALUES (?, ?, ?, ?, ?)";
        SQLite::Statement insert_query(db, insert_query_str);
        insert_query.bind(1, manager_id);
        insert_query.bind(2, field_id);
        insert_query.bind(3, order_date);

        // Convert start time and end time to HH:MM:SS format
        std::stringstream start_time_ss, end_time_ss;
        start_time_ss << start_time << ":00"; // Add seconds
        end_time_ss << end_time << ":00"; // Add seconds

        insert_query.bind(4, start_time_ss.str());
        insert_query.bind(5, end_time_ss.str());

        // Execute the insert query
        insert_query.exec();

        std::cout << "Order created for Field ID: " << field_id << " on date: " << order_date << " by Manager ID: " << manager_id << std::endl;
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}