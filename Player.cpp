//
// Created by sgvch on 25/02/2024.
//
#include "Color.h"
#include "Player.h"
#include <limits>
#include "Validation.h"

string player_register() {
        string player_id, player_name, player_email, player_phone_number, player_password;
        char player_gender;
        bool id_exists = false;
        bool email_exists = false;
        bool phone_number_exists = false;
        do {
            cout << "Enter Player ID (up to 9 digits): " << endl;
            cin >> player_id;
            system("CLS");
            if (!check_id(player_id)) {
                ChangeColor(0,4);
                cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
                ChangeColor(0,15);
            }
            else if(!check_existing_id(player_id)){
                ChangeColor(0,4);
                cout << "Invalid ID. this ID already exist, try again." << std::endl;
                ChangeColor(0,15);
                id_exists = true;
            } else {
                id_exists = false;
            }
        } while (!check_id(player_id) || id_exists);

        // Clearing input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do {
            // Getting name
            std::cout << "Enter Player Name with upper case in first name and last name: " << endl;
            getline(cin, player_name);
            system("CLS");
            if (!check_name(player_name)) {
                ChangeColor(0,4);
                cout
                        << "Invalid Name. Please enter a valid Name with upper "
                           "case in first letter in first name and upper case in first letter in last name."<< std::endl;
                ChangeColor(0,15);
            }
        } while (!check_name(player_name));

        do {
            // Getting email
            cout << "Enter player Email in format: user@example.com " << endl;
            getline(cin, player_email);
            system("CLS");
            if (!check_email(player_email)) {
                ChangeColor(0,4);
                cout << "Invalid Email. Please enter a valid Email in the format: user@example.com." << std::endl;
                ChangeColor(0,15);
            }
            else if(!check_existing_email(player_email)){
                ChangeColor(0,4);
                cout << "Invalid Email. this Email already exist, try again." << std::endl;
                ChangeColor(0,15);
                email_exists = true;
            } else {
                email_exists = false;
            }
        } while (!check_email(player_email) || email_exists);

        do {
            // Getting phone number
            cout
                    << "Enter player password at least one uppercase letter and "
                       "at least one lowercase letter and numbers and minimum size 7" << endl;
            getline(cin, player_password);
            system("CLS");
            if (!check_password(player_password)) {
                ChangeColor(0,4);
                cout
                        << "Invalid Password. Please enter a valid Password at least one "
                           "uppercase letter and at least one lowercase letter and numbers and minimum size 7."
                        << std::endl;
                ChangeColor(0,15);
            }
        } while (!check_password(player_password));

        do {
            // Getting password
            cout << "Enter Player PhoneNumber no more than 10 digits: " << endl;
            getline(cin, player_phone_number);
            system("CLS");
            if (!check_phone_number(player_phone_number)) {
                ChangeColor(0,4);
                cout << "Invalid Phone Number. Please enter a "
                        "valid phone number no more than 10 digits." << std::endl;
                ChangeColor(0,15);
            }
            if(!check_existing_phone_number(player_phone_number)){
                ChangeColor(0,4);
                cout << "Invalid Phone number. this Phone number already exist, try again." << std::endl;
                ChangeColor(0,15);
            }
        } while (!check_phone_number(player_phone_number));

        do {
            // Getting password
            cout << "Enter Player Gender: M/F " << endl;
            cin >> player_gender;
            system("CLS");
            //player_gender = toupper(player_gender); //////check
                if (!check_gender(player_gender)) {
                    ChangeColor(0,4);
                    cout << "Invalid Gender. Please enter a valid Gender (M/F)." << endl;
                    ChangeColor(0,15);
                }
            } while (!check_gender(player_gender));


    // Prepare a statement to insert a new player into the Players table
        try {
            // Open the database
            Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

            // Prepare a statement to insert a new player into the Players table
            Statement query(db, "INSERT INTO Player (Id, Name, Email, \"Phone number\", Password, Gender) VALUES (?, ?, ?, ?, ?, ?)");

            int integer_id = stoi(player_id);;
            int integer_phoneNum = stoi(player_phone_number);;
            // Bind parameters to the statement
            query.bind(1, integer_id);
            query.bind(2, player_name);
            query.bind(3, player_email);
            query.bind(4, integer_phoneNum);
            query.bind(5, player_password);
            query.bind(6, string(1, player_gender)); ///check

            // Execute the statement
            query.exec();
            ChangeColor(0,2);
            cout << "Welcome, " << player_name << "! You are now logged in as a Manager." << endl;
            ChangeColor(0,15);
            // Close the database (optional if you're done with the database)


        } catch (std::exception &e) {
            // Handle exceptions (e.g., print error message)
            cerr << "SQLite exception: " << e.what() << endl;
        }
    return player_id;
    }

string player_login(){
    string player_id, player_password, name;
    bool id_exists = false;
    do {
        cout << "Enter your ID (up to 9 digits): ";
        cin >> player_id;
        system("CLS");
        if (!check_id(player_id)) {
            ChangeColor(0,4);
            cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
            ChangeColor(0,15);
        }
        if (!check_existing_id(player_id)) {
            try {
                cout << "Enter your Password: ";
                cin >> player_password;
                system("CLS");
                // Open the database
                SQLite::Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

                // Prepare SQL query to retrieve the name and password based on the ID
                SQLite::Statement query(db, "SELECT Name, Password FROM Player WHERE Id = ?");
                query.bind(1, player_id); // Bind the ID parameter

                // Execute the query
                if (query.executeStep()) {
                    // Retrieve the name and password from the result set
                    name = query.getColumn(0).getText();
                    string stored_password = query.getColumn(1).getText();

                    // Check if the entered password matches the stored password
                    if (player_password == stored_password) {
                        // Password is correct
                        ChangeColor(0,2);
                        std::cout << "Login Successfully, " << name << " welcome to the field system!" << std::endl;
                        ChangeColor(0,15);
                        id_exists = true; // Set id_exists to true to exit the loop
                    } else {
                        // Password is incorrect
                        ChangeColor(0,4);
                        std::cout << "Error: Incorrect password. Please try again." << std::endl;
                        ChangeColor(0,15);
                    }
                } else {
                    // Player ID not found in the database
                    ChangeColor(0,4);
                    std::cout << "Error: Player ID not found." << std::endl;
                    ChangeColor(0,15);
                }
            } catch (std::exception& e) {
                // Handle exceptions (e.g., print error message)
                std::cerr << "SQLite exception: " << e.what() << std::endl;
            }
        } else {
            ChangeColor(0,4);
            std::cout << "Error: Player ID does not exist." << std::endl;
            ChangeColor(0,15);
        }
    } while (!check_id(player_id) || !id_exists);
    return player_id;
}

bool schedule_game(string player_id) {
    bool is_start_time_valid = false, is_end_time_valid = false, is_time_possible = false;
    bool is_valid_date = false;
    string order_id, chosen_field_id, manager_id, start_time_str, end_time_str, order_date;
    string order_start_time, order_end_time;
    int day, month, year;
    int current_year, current_month, current_day;
    try {
        Database db("FieldManagement.db", OPEN_READONLY); // Open your SQLite database
        // choose from available cities

        string chosen_city = choose_city_from_list(db);

        // choose from available field types
        string chosen_game_type = choose_field_type_from_list(db);

        cout << "Chosen city: " << chosen_city << endl;
        cout << "Chosen game type: " << chosen_game_type << endl;

        chosen_field_id = choose_field_id(chosen_city, chosen_game_type);

        manager_id = getManagerIdByFieldId(chosen_field_id);

        order_id = getNextOrderIdFromDatabase(db);

        do {
            cout << "Enter order Date, first enter day, then month, then year.\n"
                    "(format: DD/MM/YYYY): " << endl;
            getline(cin, order_date);
            system("CLS");

            is_valid_date = check_date(order_date);

            if (!is_valid_date) {
                ChangeColor(0, 4);
                cout << "Invalid day for the given month and year." << endl;
                ChangeColor(0, 15);
            } else {
                get_current_date(current_day, current_month, current_year);
                Date input_date = parse_date(order_date); // Assuming parse_date function parses the date string
                Date current_date(current_day, current_month, current_year);

                if (input_date < current_date) {
                    ChangeColor(0,4);
                    cout << "Invalid date. Please enter a date on or after today." << endl;
                    ChangeColor(0,15);
                    is_valid_date = false; // Set to false to continue the loop
                } else {
                    is_valid_date = true; // Set to true if date is valid and not before the current date
                }
            }
        } while (!is_valid_date);

            do {
                cout << "Enter order *start* time enter hours and then minutes\n"
                             "(format: HH:MM, hours between 8 am \n"
                             "to 8 pm, minutes as 0, 15, 30, or 45): " << endl;
                cin >> start_time_str;
                cout << "Enter order *end* time enter hours and then minutes\n"
                             "(format: HH:MM, hours between 8 am \n"
                             "to 8 pm, minutes as 0, 15, 30, or 45): " << std::endl;
                cin >> end_time_str;
                // Check if the provided times are valid

                is_start_time_valid = check_time_format(start_time_str);
                is_end_time_valid = check_time_format(end_time_str);

                if (!is_start_time_valid || !is_end_time_valid) {
                    ChangeColor(0,4);
                    cout << "Invalid time format. Please enter a valid time." << endl;
                    ChangeColor(0,15);
                    cout << "\n" << endl;
                    continue; // Restart the loop to get valid input
                }
                if (start_time_str >= end_time_str) {
                    ChangeColor(0,4);
                    cout << "Start time must be before end time. Please enter valid times." << endl;
                    ChangeColor(0,15);
                    cout << endl;
                    continue; // Restart the loop to get valid input
                }
                // Check if the provided times overlap with existing orders
                if (check_time_exist(start_time_str, end_time_str, order_date)) {
                    ChangeColor(0,4);
                    cout << "Time overlap with existing orders. Please enter a different time." << endl;
                    ChangeColor(0,15);
                    cout << "\n" << endl;
                } else {
                    // Valid time input without overlap
                    ChangeColor(0,2);
                    cout << "Valid time!" << endl;
                    ChangeColor(0,15);
                    break; // Exit the loop as valid input is provided
                }
            } while (true);

            // Format the start time to string
        } catch (exception & e)
        {
            cerr << "SQLite exception: " << e.what() << endl;
        }
        // Prepare a statement to insert a new order into the orders table
        try {
            // Open the database
            Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

            // Prepare a statement to insert a new order into the Orders table
            Statement query(db,
                            "INSERT INTO Orders (OrderId, Orderdate, OrderStartTime, OrderFinishTime, ManagerId, PlayerId, FieldId) VALUES (?, ?, ?, ?, ?, ?, ?)");
            parseDateString(order_date, day, month, year);
            Date order_new_date(day, month, year);
            string order_date_str = date_to_sqlite_string(order_new_date);
            int integer_id = stoi(order_id);
            int integer_field_id = stoi(chosen_field_id);
            int integer_player_id = stoi(player_id);
            int integer_manager_id = stoi(manager_id);
            // Bind parameters to the statement
            query.bind(1, integer_id);
            query.bind(2, order_date_str);
            query.bind(3, start_time_str);
            query.bind(4, end_time_str);
            query.bind(5, integer_manager_id);
            query.bind(6, integer_player_id);
            query.bind(7, integer_field_id);

            // Execute the statement
            query.exec();

            // Close the database (optional if you're done with the database)
        } catch (std::exception &e) {
            // Handle exceptions (e.g., print error message)
            std::cerr << "SQLite exception: " << e.what() << std::endl;
        }
        ChangeColor(0,2);
        cout << "Schedule successful" << endl;
        ChangeColor(0,15);
        return true;

    }

bool view_previous_games(string playerId)
{
    int orderCount = 0;
    string orderId, orderDate, fieldId;
    try
    {
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Assuming your orders table has columns 'OrderID', 'Orderdate', 'FieldId', and 'PlayerId' as strings
        SQLite::Statement query(db, "SELECT OrderId, Orderdate, FieldId FROM Orders WHERE PlayerId = ? AND date(Orderdate) < date('now')");

        query.bind(1, playerId);

        std::cout << "Orders before current date for player " << playerId << ":\n";

        while (query.executeStep())
        {
            // Retrieve OrderID, Orderdate, and FieldId as strings
            orderId = query.getColumn(0).getString();
            orderDate = query.getColumn(1).getString();
            fieldId = query.getColumn(2).getString();

            // Print the retrieved data
            std::cout << "Order ID: " << orderId << ", Field ID: " << fieldId << ", Date: " << orderDate << "\n";
            orderCount++; // Increment order count
        }

        // Check if the player has no orders
        if (orderCount == 0) {
            ChangeColor(0,4);
            std::cout << "You don't have any orders.\n";
            ChangeColor(0,15);
            return false;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true;
}

bool isValidRating(double rating)
{
    return (rating >= 1.0 && rating <= 5.0);
}

bool field_rate(string playerId) {
    // Call view_previous_games to display orders before rating

    if(!view_previous_games(playerId))
    {
        return false;
    }
    string selectedFieldId;
    double newRating;
    double combinedAverageRating;

    try {
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        // Retrieve the list of fields
        SQLite::Statement getFieldQuery(db, "SELECT * FROM Fields");
        ChangeColor(0,14);
        std::cout << "Available Fields:\n";
        ChangeColor(0,15);
        // Iterate over the results and print each field
        while (getFieldQuery.executeStep()) {
            std::cout << "FieldId: " << getFieldQuery.getColumn(0).getString() << "FieldType: " << getFieldQuery.getColumn(1).getString() << "City: " <<getFieldQuery.getColumn(2).getString() << std::endl;
        }
        // Take input for the selected field and rating
        std::cout << "Enter the Field ID you want to rate: " << endl;
        getline(cin, selectedFieldId);

        // Check if the selectedFieldId exists in the Fields table
        SQLite::Statement checkFieldQuery(db, "SELECT COUNT(*) FROM Fields WHERE FieldId = ?");
        checkFieldQuery.bind(1, selectedFieldId);

        if(checkFieldQuery.executeStep() && checkFieldQuery.getColumn(0).getInt() > 0) {
            // Field ID exists in the Fields table

            // Check if the field has existing ratings in FieldRate table
            SQLite::Statement checkQuery(db, "SELECT SUM(FieldRate), COUNT(*) FROM Fields WHERE FieldId = ?");
            checkQuery.bind(1, selectedFieldId);

            // Directly use currentRatingCount in the calculation
            if (checkQuery.executeStep() && checkQuery.getColumn(0).getInt() > 0) {
                // Field has existing ratings, directly use current count in the calculation
                double currentRatingSum = static_cast<double>(checkQuery.getColumn(0).getInt());

                // Take input for the new rating

                std::cout << "Enter the new rating for the field (1 to 5): " << endl;
                std::cin >> newRating;

                if (!isValidRating(newRating)) {
                    ChangeColor(0,4);
                    std::cerr << "Invalid rating. Please provide a rating between 1 and 5.\n";
                    ChangeColor(0,15);
                    return false;
                }

                // Calculate the new average rating (add new rating and divide by 2 times the existing count)
                combinedAverageRating = (currentRatingSum + newRating) / 2;

                // Update the Fields table with the new combined average rating
                SQLite::Statement updateFieldRate(db, "UPDATE Fields SET FieldRate = ? WHERE FieldId = ?");
                updateFieldRate.bind(1, combinedAverageRating);
                updateFieldRate.bind(2, selectedFieldId);
                updateFieldRate.exec();
                ChangeColor(0,2);
                std::cout << "Rating successfully recorded for player " << playerId << " and field " << selectedFieldId << ".\n";
                ChangeColor(0,15);
                return true;
            }
            else {
                // No existing ratings, set the average to the new rating
                SQLite::Statement insertQuery(db, "INSERT INTO Fields (PlayerId, FieldId, FieldRate) VALUES (?, ?, ?)");
                insertQuery.bind(1, playerId);
                insertQuery.bind(2, selectedFieldId);
                insertQuery.bind(3, combinedAverageRating);
                insertQuery.exec();
                ChangeColor(0,2);
                std::cout << "Rating successfully recorded for player " << playerId << " and field " << selectedFieldId << ".\n";
                ChangeColor(0,15);
                return true;
            }
        } else {
            // Field ID does not exist in the Fields table
            ChangeColor(0,4);
            std::cerr << "Invalid Field ID. Please select a valid Field ID.\n";
            ChangeColor(0,15);
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

void view_upcoming_orders(string playerId) {
    try {
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Assuming your orders table has columns 'PlayerId', 'Orderdate', 'FieldId', and 'OrderID' as strings
        SQLite::Statement query(db, "SELECT * FROM Orders WHERE PlayerId = ? AND date(Orderdate) > date('now')");

        query.bind(1, playerId);
        cout << "Your future orders: " << endl;
        // Execute the query and print the results
        while (query.executeStep()) {

            std::cout << "Order ID: " << query.getColumn("OrderId").getText()
                      << ", Field ID: " << query.getColumn("FieldId").getText()
                      << ", Order Date: " << query.getColumn("Orderdate").getText() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void parseDateString(const string& dateString, int& day, int& month, int& year) {
    std::istringstream iss(dateString);
    char delimiter;
    iss >> day >> delimiter >> month >> delimiter >> year;
}

bool edit_player_details(string player_id){
    try {
        bool update = false;
        int choice;

        // Open a database file
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Retrieve existing player details (optional)
        SQLite::Statement selectQuery(db, "SELECT Id, Name, Email, \"Phone number\", Password FROM Player WHERE Id=?");
        selectQuery.bind(1, player_id);

        if (selectQuery.executeStep()) {
            // Display current player details (optional)
            cout << "Current Player Details:"
                 << "\nID: " << selectQuery.getColumn(0).getText()
                 << "\nName: " << selectQuery.getColumn(1).getText()
                 << "\nEmail: " << selectQuery.getColumn(2).getText()
                 << "\nPhone: " << selectQuery.getColumn(3).getText()
                 << "\nPassword: " << selectQuery.getColumn(4).getText() << endl;
        } else {
            ChangeColor(0,4);
            cout << "Player not found." << endl;
            ChangeColor(0,15);
            return false;
        }

        // Ask the user which details they want to change
        while (true) {
            cout << "Select the detail to change:\n"
                 << "1. Name\n"
                 << "2. Email\n"
                 << "3. Phone number\n"
                 << "4. Password\n"
                 << "5. Exit\n"
                 << "Enter your choice (1-5): ";

            // Check if input is a valid integer between 1 and 5
            if (cin >> choice && choice >= 1 && choice <= 5) {
                break; // Valid choice, exit the loop
            } else {
                ChangeColor(0,4);
                cout << "Invalid input. Please enter a valid choice (1-5)." << endl;
                ChangeColor(0,15);

                // Clear the error state and ignore the invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cleanBuffer();

        // Get new details from the user based on their choice
        string new_value;
        switch (choice) {
            case 1: {
                cout << "Enter new name: " << endl;
                getline(cin,new_value);
                // Add validation
                if (check_name(new_value)) {
                    SQLite::Statement updateQueryName(db, "UPDATE Player SET Name=? WHERE Id=?");
                    updateQueryName.bind(1, new_value);
                    updateQueryName.bind(2, player_id);
                    updateQueryName.exec();
                    update = true;
                    ChangeColor(0,2);
                    cout << "Name is updated!" << endl;
                    ChangeColor(0,15);
                }
                else{
                    ChangeColor(0,4);
                    cout << "invalid input!, Name not updated!" << endl;
                    ChangeColor(0,15);
                }
                break;
            }

            case 2: {
                cout << "Enter new email: " << endl;
                getline(cin,new_value);
                // Add validation
                if (check_email(new_value)) {
                    SQLite::Statement updateQueryEmail(db, "UPDATE Player SET Email=? WHERE Id=?");
                    updateQueryEmail.bind(1, new_value);
                    updateQueryEmail.bind(2, player_id);
                    updateQueryEmail.exec();
                    update = true;
                    ChangeColor(0,2);
                    cout << "Email is updated!" << endl;
                    ChangeColor(0,15);
                }
                else{
                    ChangeColor(0,4);
                    cout << "invalid input!, Email not updated!" << endl;
                    ChangeColor(0,15);
                }
                break;
            }

            case 3: {
                cout << "Enter new phone number: " << endl;
                getline(cin,new_value);
                // Add validation
                if (check_phone_number(new_value)) {
                    SQLite::Statement updateQueryPhone(db, "UPDATE Player SET \"Phone number\"=? WHERE Id=?");
                    updateQueryPhone.bind(1, new_value);
                    updateQueryPhone.bind(2, player_id);
                    updateQueryPhone.exec();
                    update = true;
                    ChangeColor(0,2);
                    cout << "Phone number is updated!" << endl;
                    ChangeColor(0,15);
                }
                else{
                    ChangeColor(0,4);
                    cout << "invalid input!, Phone number not updated!" << endl;
                    ChangeColor(0,15);
                }
                break;
            }

            case 4: {
                cout << "Enter new password: " << endl;
                getline(cin,new_value);
                // Add validation
                if (check_password(new_value)) {
                    SQLite::Statement updateQueryPassword(db, "UPDATE Player SET Password=? WHERE Id=?");
                    updateQueryPassword.bind(1, new_value);
                    updateQueryPassword.bind(2, player_id);
                    updateQueryPassword.exec();
                    update = true;
                    ChangeColor(0,2);
                    cout << "Password is updated!" << endl;
                    ChangeColor(0,15);
                }
                else{
                    ChangeColor(0,4);
                    cout << "invalid input!, Password not updated!" << endl;
                    ChangeColor(0,15);
                }
                break;
            }

            case 5: {
                cout << "Exiting without making changes." << endl;
                return false;
            }

            default: {
                ChangeColor(0,4);
                cout << "Invalid choice. No changes made." << endl;
                ChangeColor(0,15);
                return false;
            }
        }
        if(update) {
            ChangeColor(0,2);
            cout << "Player details updated successfully." << endl;
            ChangeColor(0,15);
            return true;
        }
    } catch (const std::exception &e) {
        cerr << "Error updating Player details: " << e.what() << endl;
        return false;
        }
    return false;
}

Date parse_date(const std::string& date_str) {
    std::istringstream iss(date_str);
    char delimiter;
    int day, month, year;
    iss >> day >> delimiter >> month >> delimiter >> year;
    return Date(day, month, year);
}



