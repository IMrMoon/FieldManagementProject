//
// Created by sgvch on 26/02/2024.
//

#include "Validation.h"

///validation check for register/login
bool check_id(const string& id) {
    if (id.length() != 9) {
        return false;
    }
    for (char c : id) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool check_name(const string& name){
    bool newWord = true; // Flag to track if the next character should be uppercase

    if (name.empty() || !std::isupper(name[0])) {
        return false;
    }

    for (char c : name) {
        if (std::isspace(c)) {
            newWord = true;
        } else {
            if (newWord) {
                if (!std::isupper(c)) {
                    return false; // First letter of each word should be uppercase
                }
                newWord = false;
            } else {
                if (!std::islower(c)) {
                    return false; // All other letters should be lowercase
                }
            }
        }
    }

    return true;
}
bool check_email(const string& email){
    // Regular expression for basic email validation
    const std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailPattern);
}
bool check_password(const string& password){
    // Regular expression for password validation
    const std::regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{7,}$)");
    return std::regex_match(password, passwordPattern);
}
bool check_gender(char gender){
    return (gender == 'M' || gender == 'F' || gender == 'f' || gender == 'm');
}
bool check_phone_number(const string& phoneNumber){
    // Regular expression for phone number validation
    const regex phoneNumberPattern(R"(\d{1,10}$)");
    return regex_match(phoneNumber, phoneNumberPattern);
}
bool check_existing_id(const string& id) {
    try {
        // Open the database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare a statement to select a player with the given ID
        Statement query(db, "SELECT Id FROM Player WHERE Id = ?");
        int id_num = stoi(id);
        query.bind(1, id_num);

        // Execute the query
        if (query.executeStep()) {
            // If the query returns a result, the ID already exists
            return false;
        }
    } catch (std::exception& e) {
        // Handle exceptions (e.g., print error message)
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true;
}
bool check_existing_email(const string& email){
    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Prepare a statement to select a player with the given email
        SQLite::Statement query(db, "SELECT Email FROM Player WHERE Email = ?");
        query.bind(1, email);

        // Execute the query
        if (query.executeStep()) {
            // If the query returns a result, the email already exists
            return false;
        }
    } catch (std::exception& e) {
        // Handle exceptions (e.g., print error message)
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true;
}
bool check_existing_phone_number(const string& phone_number){
    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Prepare a statement to select a player with the given phone number
        SQLite::Statement query(db, R"(SELECT "Phone number" FROM Player WHERE "Phone number" = ?)");
        int integer_phoneNum = stoi(phone_number);;
        query.bind(1, integer_phoneNum);

        // Execute the query
        if (query.executeStep()) {
            // If the query returns a result, the phone number already exists
            return false;
        }
    } catch (std::exception& e) {
        // Handle exceptions (e.g., print error message)
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true;
}

///validation checks for order new game
bool check_date(const std::string& date_str) {
    // Check if the date string contains '/'
    if (date_str.find('/') == std::string::npos) {
        return false; // '/' not found, invalid format
    }

    // Assuming the date string is in the format "DD/MM/YYYY"
    std::istringstream iss(date_str);
    int day, month, year;
    char slash1, slash2;
    // Try to extract day, month, and year
    // Try to extract day, month, and year
    if (!(iss >> day >> slash1 >> month >> slash2 >> year)) {
        return false; // Failed to extract day, month, and year
    }

    // Check if the extraction succeeded and if the format is correct
    if (slash1 != '/' || slash2 != '/' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        return false; // Invalid format
    }

    // Check if the day is valid for the given month and year
    static const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_days = days_in_month[month];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        max_days = 29; // Leap year
    }
    if (day > max_days) {
        return false; // Invalid day for the given month and year
    }

    return true; // Date format and values are valid
}


bool check_time_format(const std::string& time_str) {
    // Check if the time string has the correct format "hh:mm"
    std::istringstream iss(time_str);
    int hours, minutes;
    char colon;

    // Try to extract hours and minutes
    if (!(iss >> hours >> colon >> minutes)) {
        return false; // Failed to extract hours and minutes
    }

    // Check if the extraction succeeded and if the format is correct
    if (colon != ':' || hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
        return false; // Invalid format
    }

    // Check additional conditions: hours between 8 am and 8 pm, minutes divisible by 15
    if (hours < 8 || hours >= 20 || minutes % 15 != 0) {
        return false; // Invalid format
    }

    // Check if the time string contains only numeric characters and a colon
    for (char c : time_str) {
        if (!std::isdigit(c) && c != ':') {
            return false; // Non-numeric character found
        }
    }

    return true; // Time format is valid
}
#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h> // Assuming you are using SQLiteCpp for SQLite database access

bool check_time_exist(const std::string& start_time_str, const std::string& finish_time_str, const std::string& date_str) {
    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Prepare SQL query to check if there's an order overlapping with the proposed time on the given date
        SQLite::Statement query(db, "SELECT COUNT(*) FROM Orders WHERE ((OrderStartTime < ? AND OrderFinishTime > ?) OR (OrderStartTime > ? AND OrderFinishTime < ?) OR (OrderStartTime < ? AND OrderFinishTime > ?)) AND Orderdate = ?");
        query.bind(1, start_time_str);
        query.bind(2, start_time_str);
        query.bind(3, start_time_str);
        query.bind(4, finish_time_str);
        query.bind(5, finish_time_str);
        query.bind(6, finish_time_str);
        query.bind(7, date_str);

        // Execute the query
        if (query.executeStep()) {
            int count = query.getColumn(0).getInt();
            return count > 0; // If count > 0, a conflicting order exists
        }
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return false; // Return false by default (no conflicts or error occurred)
}

string choose_field_id(const string& city, const string& game_type) {
    try {
        // Open your SQLite database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare the SQL query to select fields based on city and game type
        string query_str = "SELECT FieldId, Fieldtype FROM Fields WHERE City = ? AND Fieldtype = ?";
        Statement query(db, query_str);
        query.bind(1, city);
        query.bind(2, game_type);

        // Display available fields and prompt the user to choose a field ID
        std::cout << "Available fields in " << city << " for " << game_type << ":" << std::endl;
        while (query.executeStep()) {
            string field_id = query.getColumn(0).getString();
            string game_type_string = query.getColumn(1).getString();
            cout << "Field ID: " << field_id << ", Game Type: " << game_type_string << std::endl;
        }

        // Prompt the user to choose a field ID
        std::string field_id;
        bool valid_choice = false;
        do {
            std::cout << "Enter the Field ID you want to choose: ";
            std::cin >> field_id;
            cleanBuffer();

            // Validate the user input against available field IDs
            query.reset(); // Reset the query to execute it again
            while (query.executeStep()) {
                std::string id = query.getColumn(0).getString();
                if (field_id == id) {
                    valid_choice = true;
                    break;
                }
            }
            if (!valid_choice) {
                std::cout << "Invalid Field ID. Please choose from the available options." << std::endl;
            }
        } while (!valid_choice);

        return field_id;
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
        // Return an empty string or handle the error as needed
        return "";
    }
}
// Function to convert Date struct to SQLite compatible date string
string date_to_sqlite_string(const Date& date) {
    return to_string(date.getYear()) + "-" +
           (date.getMonth() < 10 ? "0" : "") + std::to_string(date.getMonth()) + "-" +
           (date.getDay() < 10 ? "0" : "") + std::to_string(date.getDay());
}
// Function to get the current date
void get_current_date(int& year, int& month, int& day) {
    time_t t = std::time(nullptr); // Get the current time
    tm* now = std::localtime(&t);  // Convert it to local time

    // Extract year, month, and day components from the current time
    year = now->tm_year + 1900; // Years since 1900
    month = now->tm_mon + 1;     // Months are 0-based
    day = now->tm_mday;          // Day of the month
}
// Function to convert time_t to SQLite compatible string format



std::string choose_city_from_list(SQLite::Database& db) {
    // Print available cities

    string chosen_city;
    bool valid_choice = false;
    do {
        print_available_cities(db);
        cout << "Enter the city you want to choose: ";
        cin >> chosen_city;
        cleanBuffer();

        // Check if the chosen city exists in the Fields table
        try {
            SQLite::Statement query(db, "SELECT COUNT(*) FROM Fields WHERE City = ?");
            query.bind(1, chosen_city);
            if (query.executeStep()) {
                int count = query.getColumn(0).getInt();
                if (count > 0) {
                    valid_choice = true;
                } else {
                    std::cout << "Invalid city. Please choose from the available options." << std::endl;
                }
            }
        } catch (exception& e) {
            cerr << "SQLite exception: " << e.what() << std::endl;
            return ""; // Return empty string on error
        }
    } while (!valid_choice);

    return chosen_city;
}

// Function to ask the player to choose a field type and validate the input
string choose_field_type_from_list(Database& db) {
    // Print available field types


    string chosen_field_type;
    bool valid_choice = false;
    do {
        print_available_field_types(db);
        cout << "Enter the field type you want to choose: ";
        cin >> chosen_field_type;
        cleanBuffer();

        // Check if the chosen field type exists in the Fields table
        try {
            SQLite::Statement query(db, "SELECT COUNT(*) FROM Fields WHERE Fieldtype = ?");
            query.bind(1, chosen_field_type);
            if (query.executeStep()) {
                int count = query.getColumn(0).getInt();
                if (count > 0) {
                    valid_choice = true;
                } else {
                    std::cout << "Invalid field type. Please choose from the available options." << std::endl;
                }
            }
        } catch (exception& e) {
            cerr << "SQLite exception: " << e.what() << std::endl;
            return ""; // Return empty string on error
        }
    } while (!valid_choice);

    return chosen_field_type;
}

void cleanBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to format time to string with seconds set to "00"
string formatTime(int hours, int minutes) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":00";
    return oss.str();
}

