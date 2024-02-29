//
// Created by sgvch on 25/02/2024.
//

#include "Manager.h"
#include "Validation.h"

string manager_register() {
    string manager_id, manager_name, manager_email, manager_phone_number, manager_password;
    char manager_gender;
    bool id_exists = false;
    bool email_exists = false;
    bool phone_number_exists = false;

    do {
        cout << "Enter Manager ID (up to 9 digits): ";
        cin >> manager_id;
        if (!check_id(manager_id)) {
            cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << endl;
        } else if (!check_existing_id(manager_id)) {
            cout << "Invalid ID. This ID already exists, try again." << endl;
            id_exists = true;
        } else {
            id_exists = false;
        }
    } while (!check_id(manager_id) || id_exists);

    // Clearing input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        // Getting name
        cout << "Enter Manager Name with upper case in first name and last name: ";
        getline(cin, manager_name);
        if (!check_name(manager_name)) {
            cout
                    << "Invalid Name. Please enter a valid Name with upper case in first letter in first name and upper case in first letter in last name."
                    << endl;
        }
    } while (!check_name(manager_name));

    do {
        // Getting email
        cout << "Enter Manager Email in format: user@example.com: ";
        getline(cin, manager_email);
        if (!check_email(manager_email)) {
            cout << "Invalid Email. Please enter a valid Email in the format: user@example.com." << endl;
        } else if (!check_existing_email(manager_email)) {
            cout << "Invalid Email. This Email already exists, try again." << endl;
            email_exists = true;
        } else {
            email_exists = false;
        }
    } while (!check_email(manager_email) || email_exists);

    do {
        // Getting phone number
        cout << "Enter Manager Phone Number no more than 10 digits: ";
        getline(cin, manager_phone_number);
        if (!check_phone_number(manager_phone_number)) {
            cout << "Invalid Phone Number. Please enter a valid phone number no more than 10 digits." << endl;
        } else if (!check_existing_phone_number(manager_phone_number)) {
            cout << "Invalid Phone number. This Phone number already exists, try again." << endl;
            phone_number_exists = true;
        } else {
            phone_number_exists = false;
        }
    } while (!check_phone_number(manager_phone_number) || phone_number_exists);

    do {
        // Getting password
        cout << "Enter Manager Password: ";
        getline(std::cin, manager_password);
        if (!check_password(manager_password)) {
            cout << "Invalid Password. Please enter a valid Password." << endl;
        }
    } while (!check_password(manager_password));

    do {
        // Getting gender
        cout << "Enter Manager Gender: M/F: ";
        cin >> manager_gender;
        if (!check_gender(manager_gender)) {
            cout << "Invalid Gender. Please enter a valid Gender M/F." << endl;
        }
    } while (!check_gender(manager_gender));

    // Prepare a statement to insert a new manager into the Managers table
    try {
        // Open the database
        Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

        // Prepare a statement to insert a new manager into the Managers table
        Statement query(db,
                                "INSERT INTO Managers (Id, Name, Email, \"Phone number\", Password, Gender) VALUES (?, ?, ?, ?, ?, ?)");

        // Bind parameters to the statement
        int integer_id = stoi(manager_id);
        int integer_phoneNum = stoi(manager_phone_number);
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
        cerr << "SQLite exception: " << e.what() << endl;
    }

    return manager_id;
}

string manager_login() {
    string manager_id, manager_password, name;
    bool id_exists = false;
    do {
        cout << "Enter your ID (up to 9 digits): ";
        cin >> manager_id;
        if (!check_id(manager_id)) {
            cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << endl;
        }
        if (!check_existing_id(manager_id)) {
            try {
                cout << "Enter your Password: ";
                cin >> manager_password;
//                    std::cin.ignore(); // Clear the input buffer
//                    std::getline(std::cin, manager_password); // Read password with getline
                // Open the database
                Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

                // Prepare SQL query to retrieve the name and password based on the ID
                Statement query(db, "SELECT Name, Password FROM Manager WHERE Id = ?");
                query.bind(1, manager_id); // Bind the ID parameter

                // Execute the query
                if (query.executeStep()) {
                    // Retrieve the name and password from the result set
                    name = query.getColumn(0).getText();
                    string stored_password = query.getColumn(1).getText();

                    // Check if the entered password matches the stored password
                    if (manager_password == stored_password) {
                        cout << "Welcome, " << name << "! You are now logged in as a Manager." << endl;
                        id_exists = true; // Return the manager ID if login is successful
                    } else {
                        cout << "Invalid Password. Please try again." << endl;
                    }
                } else {
                    cout << "Manager ID not found. Please try again." << endl;
                }
            } catch (exception &e) {
                cerr << "SQLite exception: " << e.what() << endl;
            }
        } else {
            cout << "Manager ID does not exist. Please try again." << endl;
        }
    } while (!check_id(manager_id) || !id_exists);

    return manager_id; // Return empty string if login is unsuccessful
}

bool edit_manager_details(string manager_id){
    try {
        int choice;

        // Open a database file
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Retrieve existing player details (optional)
        SQLite::Statement selectQuery(db, "SELECT Id, Name, Email, \"Phone number\", Password FROM Manager WHERE Id=?");
        selectQuery.bind(1, manager_id);

        if (selectQuery.executeStep()) {
            // Display current player details (optional)
            cout << "Current Manager Details:"
                 << "\nID: " << selectQuery.getColumn(0).getText()
                 << "\nName: " << selectQuery.getColumn(1).getText()
                 << "\nEmail: " << selectQuery.getColumn(2).getText()
                 << "\nPhone: " << selectQuery.getColumn(3).getText()
                 << "\nPassword: " << selectQuery.getColumn(4).getText() << endl;
        } else {
            cout << "Manager not found." << endl;
            return false;
        }

        // Ask the user which details they want to change
        cout << "Select the detail to change:\n"
             << "1. Name\n"
             << "2. Email\n"
             << "3. Phone number\n"
             << "4. Password\n"
             << "5. Exit\n"
             << "Enter your choice (1-5): ";

        cin >> choice;
        cleanBuffer();

        // Get new details from the user based on their choice
        string new_value;
        switch (choice) {
            case 1: {
                cout << "Enter new name: ";
                getline(cin,new_value);
                // Add validation
                if (check_name(new_value)) {
                    SQLite::Statement updateQueryName(db, "UPDATE Manager SET Name=? WHERE Id=?");
                    updateQueryName.bind(1, new_value);
                    updateQueryName.bind(2, manager_id);
                    updateQueryName.exec();
                    cout << "Name is updated!" << endl;
                }
                break;
            }

            case 2: {
                cout << "Enter new email: ";
                getline(cin,new_value);
                // Add validation
                if (check_email(new_value)) {
                    SQLite::Statement updateQueryEmail(db, "UPDATE Manager SET Email=? WHERE Id=?");
                    updateQueryEmail.bind(1, new_value);
                    updateQueryEmail.bind(2, manager_id);
                    updateQueryEmail.exec();
                    cout << "Email is updated!" << endl;
                }
                break;
            }

            case 3: {
                cout << "Enter new phone number: ";
                getline(cin,new_value);
                // Add validation
                if (check_phone_number(new_value)) {
                    SQLite::Statement updateQueryPhone(db, "UPDATE Manager SET \"Phone number\"=? WHERE Id=?");
                    updateQueryPhone.bind(1, new_value);
                    updateQueryPhone.bind(2, manager_id);
                    updateQueryPhone.exec();
                    cout << "Phone number is updated!" << endl;
                }
                break;
            }

            case 4: {
                cout << "Enter new password: ";
                getline(cin,new_value);
                // Add validation
                if (check_password(new_value)) {
                    SQLite::Statement updateQueryPassword(db, "UPDATE Manager SET Password=? WHERE Id=?");
                    updateQueryPassword.bind(1, new_value);
                    updateQueryPassword.bind(2, manager_id);
                    updateQueryPassword.exec();
                    cout << "Password is updated!" << endl;
                }
                break;
            }

            case 5: {
                cout << "Exiting without making changes." << endl;
                return false;
            }

            default: {
                cout << "Invalid choice. No changes made." << endl;
                return false;
            }
        }

        cout << "Manager details updated successfully." << endl;
        return true;
    } catch (const std::exception &e) {
        cerr << "Error updating Manager details: " << e.what() << endl;
        return false;
    }
}

void mark_dates_as_unavailable(string manager_id) {
    int current_year, current_month, current_day;
    bool is_valid_date = false;
    string start_time = "08:00";
    string end_time = "20:00";
    string order_date;
    string field_id = get_field_id(manager_id);
    try {

        do{
            cout << "Enter order Date, first enter day, then month, then year.\n"
                    "(format: DD/MM/YYYY): " << endl;
            getline(cin, order_date);


            is_valid_date = check_date(order_date);

            if (!is_valid_date) {
                cout << "Invalid day for the given month and year." << endl;
            }
            // Get the current date
            get_current_date(current_year, current_month, current_day);

            // Check if the entered date is before the current date
        } while (!check_date(order_date));
        // Open the SQLite database
        Database db("FieldManagement.db", OPEN_READWRITE);
        string order_id = getNextOrderIdFromDatabase(db);
        string player_id = "";
        // Prepare the SQL query to insert the order
        string insert_query_str = "INSERT INTO Orders (OrderId, Orderdate, OrderStartTime, OrderFinishTime, ManagerId, PlayerId, FieldId) VALUES (?, ?, ?, ?, ?, ?, ?)";
        SQLite::Statement insert_query(db, insert_query_str);
        insert_query.bind(1, order_id); // אולי כדאי להשתמש במספרים מזהים ייחודיים, לא בשם "auto"
        insert_query.bind(2, order_date);
        insert_query.bind(3, start_time); // תוסיף שניות לסוף השעה
        insert_query.bind(4, end_time); // תוסיף שניות לסוף השעה
        insert_query.bind(5, manager_id);
        insert_query.bind(6, player_id);
        insert_query.bind(7, field_id);

        // Execute the insert query
        insert_query.exec();

        cout << "Order created for Field ID: " << field_id << " on date: " << order_date << " by Manager ID: " << manager_id << endl;
    } catch (std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void view_orders_by_date(string manager_id) {
    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare the SQL query to get fields managed by the specified manager
        std::string fields_query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
        SQLite::Statement fields_query(db, fields_query_str);
        fields_query.bind(1, manager_id);

        std::vector<int> field_ids;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0);
            field_ids.push_back(field_id);
        }

        // Ask the manager to choose a date
        std::string chosen_date;
        bool valid_date = false;
        do {
            std::cout << "Enter the date (dd/mm/yyyy) to view orders: ";
            std::cin >> chosen_date;

            if (check_date(chosen_date)) {
                valid_date = true;
            } else {
                std::cout << "Invalid date format. Please enter date in dd/mm/yyyy format." << std::endl;
            }
        } while (!valid_date);

        // Prepare the SQL query to get orders for the chosen date and manager's fields
        std::string orders_query_str = "SELECT * FROM Orders WHERE Orderdate = ? AND FieldId IN (";
        for (size_t i = 0; i < field_ids.size(); ++i) {
            orders_query_str += std::to_string(field_ids[i]);
            if (i < field_ids.size() - 1) {
                orders_query_str += ",";
            }
        }
        orders_query_str += ")";
        SQLite::Statement orders_query(db, orders_query_str);
        orders_query.bind(1, chosen_date);

        // Execute the query and print the results
        std::cout << "Orders for Manager ID: " << manager_id << " on " << chosen_date << std::endl;
        while (orders_query.executeStep()) {
            int order_id = orders_query.getColumn(0);
            int field_id = orders_query.getColumn(6).getInt();
            std::string order_start_time = orders_query.getColumn(2);
            std::string order_finish_time = orders_query.getColumn(3);

            std::cout << "Order ID: " << order_id << ", Field ID: " << field_id << ", Order Start Time: " << order_start_time << ", Order Finish Time: " << order_finish_time << std::endl;
        }

        std::cout << "Done." << std::endl;
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void view_field_orders(string manager_id) {
    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare the SQL query to get fields managed by the specified manager
        std::string fields_query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
        SQLite::Statement fields_query(db, fields_query_str);
        fields_query.bind(1, manager_id);

        std::vector<int> field_ids;
        std::map<int, std::string> field_map; // Map to store FieldId and corresponding Field details
        std::cout << "Fields managed by Manager ID: " << manager_id << std::endl;
        int choice_counter = 1;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0);
            std::cout << choice_counter << ". Field ID: " << field_id << std::endl;
            field_ids.push_back(field_id);
            field_map[choice_counter++] = "Field ID: " + std::to_string(field_id);
        }

        // Ask the manager to choose a field from the list
        int choice;
        bool valid_choice = false;
        do {
            std::cout << "Enter the choice of the Field you want to select: ";
            std::cin >> choice;

            if (choice >= 1 && choice <= field_ids.size()) {
                valid_choice = true;
            } else {
                std::cout << "Invalid choice. Please choose from the list." << std::endl;
            }
        } while (!valid_choice);

        int chosen_field_id = field_ids[choice - 1];

        // Prepare the SQL query to get orders for the chosen field ID
        std::string orders_query_str = "SELECT * FROM Orders WHERE FieldId = ?";
        SQLite::Statement orders_query(db, orders_query_str);
        orders_query.bind(1, chosen_field_id);

        // Execute the query and print the results
        std::cout << "Orders for Field ID: " << chosen_field_id << std::endl;
        while (orders_query.executeStep()) {
            int order_id = orders_query.getColumn(0);
            std::string order_date = orders_query.getColumn(1);
            std::string other_details = orders_query.getColumn(3);

            std::cout << "Order ID: " << order_id << ", Order Date: " << order_date << ", Other Details: " << other_details << std::endl;
        }

        std::cout << "Done." << std::endl;
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}
