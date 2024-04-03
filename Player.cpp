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
            else if(!check_existing_id_Player(player_id)){
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
    bool has_space = false;
        do {
            // Getting name
            std::cout << "Enter Player Name with upper case in first name and last name: " << endl;
            getline(cin, player_name);
            system("CLS");

            for (char c : player_name) {
                if (c == ' ') {
                    has_space = true;
                    break;
                }
            }

            if (!has_space) {
                ChangeColor(0, 4);
                cout << "Invalid Name. Please enter both the first name and last name separated by a space." << endl;
                ChangeColor(0, 15);
            }
            if (!check_name(player_name)) {
                ChangeColor(0,4);
                cout
                        << "Invalid Name. Please enter a valid Name with upper "
                           "case in first letter in first name and upper case in first letter in last name."<< std::endl;
                ChangeColor(0,15);
            }
        } while (!has_space || !check_name(player_name));

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
            cout << "Enter Player PhoneNumber exactly 10 digits and start with 05: " << endl;
            getline(cin, player_phone_number);
            system("CLS");
            if (!check_phone_number(player_phone_number)) {
                ChangeColor(0,4);
                cout << "Invalid Phone Number. Please enter a "
                        "valid phone number exactly 10 digits and start with 05." << std::endl;
                ChangeColor(0,15);
            }
            if(!check_existing_phone_number(player_phone_number)){
                ChangeColor(0,4);
                cout << "Invalid Phone number. this Phone number already exist, try again." << std::endl;
                ChangeColor(0,15);
            }
        } while (!check_phone_number(player_phone_number) && check_existing_phone_number(player_phone_number));

    string manager_gender;
    char gender;

    do {
        // Getting gender
        cout << "Enter Manager Gender: M/F: " << endl;
        cin >> manager_gender;

        // Check if the input is only one character
        if (manager_gender.length() != 1) {
            ChangeColor(0,4);
            cout << "Invalid input. Please enter only one character." << endl;
            ChangeColor(0,15);
            cin.clear(); // Clear the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining characters in the buffer
            continue; // Restart the loop to prompt the user again
        }

        // Convert the input to uppercase for case-insensitive comparison
        gender = toupper(manager_gender[0]);

        // Check if the input is 'M' or 'F'
        if (gender != 'M' && gender != 'F') {
            ChangeColor(0,4);
            cout << "Invalid Gender. Please enter either 'M' or 'F'." << endl;
            ChangeColor(0,15);
        }
    } while (gender != 'M' && gender != 'F');


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
        bool is_valid = true;
        for (char c : player_id) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
        if (!check_id(player_id)) {
            ChangeColor(0,4);
            cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
            ChangeColor(0,15);
        }
        if (!check_existing_id_Player(player_id)) {
            try {
                cout << "Enter your Password with At least one uppercase letter and one lowercase letter and a minimum length of 7: ";
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
    bool is_valid_date = false;
    string chosen_field_id, manager_id, order_date, start_time_str, end_time_str;
    int day, month, year;

    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

        // Choose from available cities and field types
        string chosen_city = choose_city_from_list(db);
        string chosen_game_type = choose_field_type_from_list(db);

        cout << "Chosen city: " << chosen_city << endl;
        cout << "Chosen game type: " << chosen_game_type << endl;

        // Choose a field ID based on city and game type
        chosen_field_id = choose_field_id(chosen_city, chosen_game_type);

        // Get manager ID for the chosen field
        manager_id = getManagerIdByFieldId(chosen_field_id);

        // Get the next order ID from the database
        string order_id = getNextOrderIdFromDatabase(db);

        // Input order date and validate
        do {
            cout << "Enter order Date first year, month, then day (format: YYYY-MM-DD): " << endl;
            getline(cin, order_date);
            system("CLS");
            is_valid_date = check_date(order_date);
            if (!is_valid_date) {
                ChangeColor(0,4);
                cout << "Invalid date format. Please enter a valid date." << endl;
                ChangeColor(0,15);
            }
        } while (!is_valid_date);

        // Input start and end times and validate
        do {
            cout << "Enter order start time (format: HH:MM): ";
            cin >> start_time_str;
            cout << "Enter order end time (format: HH:MM): ";
            cin >> end_time_str;
            is_valid_date = check_time_format(start_time_str) && check_time_format(end_time_str);
            if (!is_valid_date) {
                ChangeColor(0,4);
                cout << "Invalid time format. Please enter a valid time." << endl;
                ChangeColor(0,15);
            }
        } while (!is_valid_date);

        // Prepare a statement to insert a new order into the Orders table
        SQLite::Statement query(db, "INSERT INTO Orders (OrderId, Orderdate, OrderStartTime, OrderFinishTime, ManagerId, PlayerId, FieldId) VALUES (?, ?, ?, ?, ?, ?, ?)");

        // Parse order date
//        parseDateString(order_date, day, month, year);
//        Date order_new_date(day, month, year);
//        string order_date_str = date_to_sqlite_string(order_new_date);

        // Bind parameters to the statement
        query.bind(1, stoi(order_id));
        query.bind(2, order_date);
        query.bind(3, start_time_str);
        query.bind(4, end_time_str);
        query.bind(5, stoi(manager_id));
        query.bind(6, stoi(player_id));
        query.bind(7, stoi(chosen_field_id));

        // Execute the statement
        query.exec();

        ChangeColor(0,2);
        cout << "Schedule successful" << endl;
        ChangeColor(0,15);

        return true;
    } catch (const std::exception &e) {
        cerr << "SQLite exception: " << e.what() << endl;
        return false; // Return false indicating failure
    }
} ///fix time schedule

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

    if (!view_previous_games(playerId)) {
        return false;
    }

    string selectedFieldId;
    double newRating;
    double combinedAverageRating;

    try {
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Retrieve the list of fields
        SQLite::Statement getFieldQuery(db, "SELECT * FROM Fields");
        cout << "Available Fields:\n";
        while (getFieldQuery.executeStep()) {
            cout << "FieldId: " << getFieldQuery.getColumn(0).getString() << " FieldType: " << getFieldQuery.getColumn(1).getString() << " City: " << getFieldQuery.getColumn(2).getString() << endl;
        }

        // Take input for the selected field
        cout << "Enter the Field ID you want to rate: " << endl;
        cin >> selectedFieldId;

        // Check if the selectedFieldId exists in the Fields table
        SQLite::Statement checkFieldQuery(db, "SELECT COUNT(*) FROM Fields WHERE FieldId = ?");
        checkFieldQuery.bind(1, selectedFieldId);

        if (checkFieldQuery.executeStep() && checkFieldQuery.getColumn(0).getInt() > 0) {
            // Field ID exists in the Fields table

            // Take input for the new rating
            do {
                cout << "Enter the new rating for the field (1 to 5): " << endl;
                cin >> newRating;

                // Check if the input is a valid digit
                if (cin.fail() || newRating < 1 || newRating > 5) {
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input. Please enter a rating between 1 and 5." << endl;
                } else {
                    break;
                }
            } while (true);

            // Calculate the new combined average rating
            SQLite::Statement checkQuery(db, "SELECT SUM(FieldRate), COUNT(*) FROM Fields WHERE FieldId = ?");
            checkQuery.bind(1, selectedFieldId);

            if (checkQuery.executeStep() && checkQuery.getColumn(0).getInt() > 0) {
                double currentRatingSum = static_cast<double>(checkQuery.getColumn(0).getInt());
                int currentRatingCount = checkQuery.getColumn(1).getInt();

                // Calculate the new combined average rating
                combinedAverageRating = (currentRatingSum + newRating) / (currentRatingCount + 1);
            } else {
                // No existing ratings, set the average to the new rating
                combinedAverageRating = newRating;
            }

            // Update the FieldRate table with the new combined average rating
            SQLite::Statement updateQuery(db, "UPDATE Fields SET FieldRate = ? WHERE FieldId = ?");
            updateQuery.bind(1, combinedAverageRating);
            updateQuery.bind(2, selectedFieldId);
            updateQuery.exec();

            cout << "Rating successfully recorded for player " << playerId << " and field " << selectedFieldId << ".\n";
            return true;
        } else {
            // Field ID does not exist in the Fields table
            cerr << "Invalid Field ID. Please select a valid Field ID.\n";
            return false;
        }
    } catch (const std::exception &e) {
        cerr << "SQLite exception: " << e.what() << endl;
        return false;
    }
}

void view_upcoming_orders(string playerId) {
    int orderCount = 0;
    string orderId, orderDate, fieldId;
    try {

        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Print debugging information
        std::cout << "Executing query for player ID: " << playerId << std::endl;

        // Prepare the SQL query to select upcoming orders for the specified player
        SQLite::Statement query(db, "SELECT * FROM Orders WHERE PlayerId = ? AND date(Orderdate) > date('now')");


        query.bind(1, playerId);

        cout << "Your future orders: " << endl;

        // Iterate over each upcoming order
        bool hasOrders = false; // Flag to track if there are any upcoming orders
        while (query.executeStep()) {
            hasOrders = true; // Set flag to true indicating at least one order is found

            orderId = query.getColumn(0).getString();
            orderDate = query.getColumn(1).getString();
            fieldId = query.getColumn(6).getString();

            std::cout << "Order ID: " << orderId
                      << ", Field ID: " << fieldId
                      << ", Order Date: " << orderDate << std::endl;
        }

        // Check if there are no upcoming orders
        if (!hasOrders) {
            cout << "You don't have any upcoming orders." << endl;
        }
    } catch (const std::exception &e) {
        // Print error message if an exception occurs
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void parseDateString(const string& dateString, int& year, int& month, int& day) {
    std::istringstream iss(dateString);
    char delimiter;
    iss >> year >> delimiter >> month >> delimiter >> day;
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
                do {
                    cout << "Enter new name with upper case in first name and last name: ";
                    getline(cin, new_value);

                    if (check_name(new_value)) {
                        SQLite::Statement updateQueryName(db, "UPDATE Player SET Name=? WHERE Id=?");
                        updateQueryName.bind(1, new_value);
                        updateQueryName.bind(2, player_id);
                        updateQueryName.exec();
                        ChangeColor(0, 2);
                        cout << "Name is updated!" << endl;
                        ChangeColor(0, 15);
                        break;
                    } else {
                        ChangeColor(0, 4);
                        cout << "Invalid Name. Please enter a valid Name with upper case in first letter in first name and upper case in first letter in last name." << endl;
                        ChangeColor(0, 15);
                    }
                } while (true);

                break;
            }

            case 2: {
                do{
                cout << "Enter new email in format: user@example.com : " << endl;
                getline(cin, new_value);
                // Add validation
                if (check_email(new_value)) {
                    SQLite::Statement updateQueryEmail(db, "UPDATE Player SET Email=? WHERE Id=?");
                    updateQueryEmail.bind(1, new_value);
                    updateQueryEmail.bind(2, player_id);
                    updateQueryEmail.exec();
                    update = true;
                    ChangeColor(0, 2);
                    cout << "Email is updated!" << endl;
                    ChangeColor(0, 15);
                    break;
                } else {
                    ChangeColor(0,4);
                    cout << "Invalid email format. Please enter a valid email address." << endl;
                    ChangeColor(0,15);
                }
                } while (true); // Keep looping until a valid input is provided
                break;
            }

            case 3: {
                do{
                cout << "Enter new phone number exactly 10 digits and start with 05: " << endl;
                cin.ignore(); // Clear the input buffer before getline
                getline(cin, new_value);
                // Add validation
                if (check_phone_number(new_value)) {
                    SQLite::Statement updateQueryPhone(db, "UPDATE Player SET \"Phone number\"=? WHERE Id=?");
                    updateQueryPhone.bind(1, new_value);
                    updateQueryPhone.bind(2, player_id);
                    updateQueryPhone.exec();
                    update = true;
                    ChangeColor(0, 2);
                    cout << "Phone number is updated!" << endl;
                    ChangeColor(0, 15);
                    break;
                } else {
                    ChangeColor(0, 4);
                    cout << "Invalid phone number format. Please enter a valid phone number." << endl;
                    ChangeColor(0, 15);
                }
            }
                while (true); // Keep looping until a valid input is provided
                break;
        }


            case 4: {
                do {
                cout << "Enter new password at least one uppercase letter and \n"
                        "at least one lowercase letter and numbers and minimum size 7: " << endl;
                    cin.ignore(); // Clear the input buffer before getline
                    getline(cin, new_value);
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
                    break; // Exit the loop if a valid input is provided
                } else {
                    ChangeColor(0,4);
                    cout << "Invalid password format. Please enter a valid password." << endl;
                    ChangeColor(0,15);
                }
            } while (true); // Keep looping until a valid input is provided
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
    iss >> year >> delimiter >> month >> delimiter >> day;
    return Date(day, month, year);
}



