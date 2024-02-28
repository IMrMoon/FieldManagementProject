//
// Created by sgvch on 25/02/2024.
//
#define RESET 7
#define CYAN 9
#define RED 4
#define GREEN 2
#include "Player.h"
#include <limits>

#include "Validation.h"


//void set_text_color(int color) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, color);
//}


string player_register() {
        string player_id, player_name, player_email, player_phone_number, player_password;
        char player_gender;
        bool id_exists = false;
        bool email_exists = false;
        bool phone_number_exists = false;
        do {
            cout << "Enter Player ID (up to 9 digits): ";
            cin >> player_id;
            if (!check_id(player_id)) {
                cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
            }
            else if(!check_existing_id(player_id)){
                cout << "Invalid ID. this ID already exist, try again." << std::endl;
                id_exists = true;
            } else {
                id_exists = false;
            }
        } while (!check_id(player_id) || id_exists);

        // Clearing input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do {
            // Getting name
            std::cout << "Enter Player Name with upper case in first name and last name: ";
            getline(cin, player_name);
            if (!check_name(player_name)) {
                cout
                        << "Invalid Name. Please enter a valid Name with upper "
                           "case in first letter in first name and upper case in first letter in last name."<< std::endl;
            }
        } while (!check_name(player_name));

        do {
            // Getting email
            cout << "Enter player Email in format: user@example.com ";
            getline(cin, player_email);
            if (!check_email(player_email)) {
                cout << "Invalid Email. Please enter a valid Email in the format: user@example.com." << std::endl;
            }
            else if(!check_existing_email(player_email)){
                cout << "Invalid Email. this Email already exist, try again." << std::endl;
                email_exists = true;
            } else {
                email_exists = false;
            }
        } while (!check_email(player_email) || email_exists);

        do {
            // Getting phone number
            cout
                    << "Enter player password at least one uppercase letter and "
                       "at least one lowercase letter and numbers and minimum size 7";
            getline(cin, player_password);
            if (!check_password(player_password)) {
                cout
                        << "Invalid Password. Please enter a valid Password at least one "
                           "uppercase letter and at least one lowercase letter and numbers and minimum size 7."
                        << std::endl;
            }
        } while (!check_password(player_password));

        do {
            // Getting password
            cout << "Enter Player PhoneNumber no more than 10 digits: ";
            getline(cin, player_phone_number);
            if (!check_phone_number(player_phone_number)) {
                cout << "Invalid Phone Number. Please enter a "
                        "valid phone number no more than 10 digits." << std::endl;
            }
            if(!check_existing_phone_number(player_phone_number)){
                cout << "Invalid Phone number. this Phone number already exist, try again." << std::endl;
            }
        } while (!check_phone_number(player_phone_number));

        do {
            // Getting password
            cout << "Enter Player Gender: M/F ";
            cin >> player_gender;
            //player_gender = toupper(player_gender); //////check
                if (!check_gender(player_gender)) {
                    cout << "Invalid Gender. Please enter a valid Gender (M/F)." << endl;
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
        if (!check_id(player_id)) {
            cout << "Invalid ID. Please enter a valid ID consisting of up to 9 digits." << std::endl;
        }
        if (!check_existing_id(player_id)) {
            try {
                cout << "Enter your Password: ";
                cin >> player_password;
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
                        //set_text_color(GREEN);
                        std::cout << "Login Successfully, " << name << " welcome to the field system!" << std::endl;
                        //set_text_color(RESET);
                        id_exists = true; // Set id_exists to true to exit the loop
                    } else {
                        // Password is incorrect
                        //set_text_color(RED);
                        std::cout << "Error: Incorrect password. Please try again." << std::endl;
                        //set_text_color(RESET);
                    }
                } else {
                    // Player ID not found in the database
                    //set_text_color(RED);
                    std::cout << "Error: Player ID not found." << std::endl;
                    //set_text_color(RESET);
                }
            } catch (std::exception& e) {
                // Handle exceptions (e.g., print error message)
                std::cerr << "SQLite exception: " << e.what() << std::endl;
            }
        } else {
            //set_text_color(RED);
            std::cout << "Error: Player ID does not exist." << std::endl;
            //set_text_color(RESET);
        }
    } while (!check_id(player_id) || !id_exists);
    return player_id;
}

bool schedule_game(string player_id) {
    bool is_start_time_valid = false, is_end_time_valid = false, is_time_exist = false;
    bool is_valid_date = false;
    string order_id, chosen_field_id, manager_id, start_time_str, end_time_str, order_date;
    //Date order_date;
    string order_start_time, order_end_time;
    int day, month, year;
    char slash1, slash2;
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

            do {
                cout << "Enter order *start* time enter hours and then minutes\n"
                             "(format: HH MM, hours between 8 am \n"
                             "to 8 pm, minutes as 0, 15, 30, or 45): " << endl;
                cin >> start_time_str;
                cout << "Enter order *end* time enter hours and then minutes\n"
                             "(format: HH MM, hours between 8 am \n"
                             "to 8 pm, minutes as 0, 15, 30, or 45): " << std::endl;
                cin >> end_time_str;
                // Check if the provided times are valid

                if (check_time_format(start_time_str)) {
                    is_start_time_valid = true;
                } else {
                    std::cout << "Invalid start time. Please enter a valid start time." << std::endl;
                }

                if (check_time_format(end_time_str)) {
                    is_end_time_valid = true;
                } else {
                    std::cout << "Invalid end time. Please enter a valid end time." << std::endl;
                }
                if (check_time_exist(start_time_str, end_time_str, order_date)) {
                    is_time_exist = true;
                    cout << "Invalid time, already exist. Please enter a valid time." << endl;
                }

            } while (!is_start_time_valid && !is_end_time_valid && is_time_exist);

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

            int integer_id = stoi(order_id);
            int integer_field_id = stoi(chosen_field_id);
            int integer_player_id = stoi(player_id);
            int integer_manager_id = stoi(manager_id);
            // Bind parameters to the statement
            query.bind(1, integer_id);
            query.bind(2, order_date);
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
        //set_text_color(GREEN);
        cout << "Schedule successful" << endl;
        //set_text_color(RESET);
        return true;

    }



