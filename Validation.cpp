//
// Created by sgvch on 26/02/2024.
//
#include "Color.h"
#include "Validation.h"
#include <sstream>


///validation check for register/login
bool check_id(const string& id) {
    if (id.length() != 9) {
        return false;
    }
    for (char c : id) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool check_name(const string& name){
    bool newWord = true; // Flag to track if the next character should be uppercase

    if (name.empty() || !isupper(name[0])) {
        return false;
    }

    for (char c : name) {
        if (isspace(c)) {
            newWord = true;
        } else {
            if (newWord) {
                if (!isupper(c)) {
                    return false; // First letter of each word should be uppercase
                }
                newWord = false;
            } else {
                if (!islower(c)) {
                    return false; // All other letters should be lowercase
                }
            }
        }
    }

    return true;
}

bool check_city(const string& city){
    bool newWord = true; // Flag to track if the next character should be uppercase

    if (city.empty() || !isupper(city[0])) {
        return false;
    }

    for(char c : city) {
        if (!isalpha(c)) { // Check if the character is not a letter
            return false;
        }
    }
    return true;
}

bool check_existing_city(string manager_city){
    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Prepare the SQL query to check if the manager city exists in the Manager table
        SQLite::Statement query(db, "SELECT COUNT(*) FROM Manager WHERE City = ?");
        query.bind(1, manager_city);

        // Execute the query
        if (query.executeStep()) {
            int count = query.getColumn(0).getInt();
            return false; // If count is 0, the city does not exist, so return true; otherwise, return false.
        }
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true; // Return true by default (error occurred or city doesn't exist)
}

bool check_email(const string& email){
    // Regular expression for basic email validation
    const regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

bool check_password(const string& password){
    // Regular expression for password validation
    const regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{7,}$)");
    return regex_match(password, passwordPattern);
}

bool check_gender(char gender){
    return (gender == 'M' || gender == 'F' || gender == 'f' || gender == 'm');
}

bool check_phone_number(const string& phoneNumber){
    // Regular expression for phone number validation
    const regex phoneNumberPattern("^05\\d{8}$");
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
    } catch (exception& e) {
        // Handle exceptions (e.g., print error message)
        cerr << "SQLite exception: " << e.what() << endl;
    }
    return true;
}

bool check_existing_email(const string& email){
    try {
        // Open the database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare a statement to select a player with the given email
        Statement query(db, "SELECT Email FROM Player WHERE Email = ?");
        query.bind(1, email);

        // Execute the query
        if (query.executeStep()) {
            // If the query returns a result, the email already exists
            return false;
        }
    } catch (exception& e) {
        // Handle exceptions (e.g., print error message)
        cerr << "SQLite exception: " << e.what() << endl;
    }
    return true;
}

bool check_existing_phone_number(const string& phone_number){
    try {
        // Open the database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare a statement to select a player with the given phone number
        Statement query(db, R"(SELECT "Phone number" FROM Player WHERE "Phone number" = ?)");
        int integer_phoneNum = stoi(phone_number);;
        query.bind(1, integer_phoneNum);

        // Execute the query
        if (query.executeStep()) {
            // If the query returns a result, the phone number already exists
            return false;
        }
    } catch (exception& e) {
        // Handle exceptions (e.g., print error message)
        cerr << "SQLite exception: " << e.what() << std::endl;
    }
    return true;
}

///validation checks for order new game
bool check_date(const string& date_str) {
    int curr_day, curr_month, curr_year;
    // Check if the date string contains '-'
    if (date_str.find('-') == string::npos) {
        return false; // '-' not found, invalid format
    }

    // Assuming the date string is in the format "YYYY-MM-DD"
    istringstream iss(date_str);
    int year, month, day;
    char dash1, dash2;
    // Try to extract year, month, and day
    if (!(iss >> year >> dash1 >> month >> dash2 >> day)) {
        return false; // Failed to extract year, month, and day
    }

    // Check if the extraction succeeded and if the format is correct
    if (dash1 != '-' || dash2 != '-' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
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
    // Check if the date is before the current date
    get_current_date(curr_year, curr_month, curr_day);
    if (year < curr_year ||
        (year == curr_year && month < curr_month) ||
        (year == curr_year && month == curr_month && day < curr_day)) {
        cout << "Invalid date. Please enter a date on or after today." << endl;
        return false; // Date is before the current date
    }

    return true; // Date format and values are valid
}


bool check_time_format(const string& time_str) {
    // Check if the time string has the correct format "hh:mm"
    istringstream iss(time_str);
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
        if (!isdigit(c) && c != ':') {
            return false; // Non-numeric character found
        }
    }

    return true; // Time format is valid
}

bool check_time_exist(const string& start_time_str, const string& finish_time_str, const string& date_str) {
    try {
        int day, month, year;
        parseDateString(date_str, day, month, year);
        Date new_date(day, month, year);
        string order_date_str = date_to_sqlite_string(new_date);
        // Convert start and finish time strings to total minutes since midnight
        int start_minutes = time_to_minutes(start_time_str);
        int finish_minutes = time_to_minutes(finish_time_str);

        // Define a set to store the time intervals
        set<pair<int, int>> intervals;

        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READONLY);

        // Prepare SQL query to retrieve existing orders for the specified date
        SQLite::Statement query(db, "SELECT OrderStartTime, OrderFinishTime FROM Orders WHERE Orderdate = ?");
        query.bind(1, order_date_str); // Bind the date string directly to the query

        // Execute the query and populate the set with time intervals
        if (query.executeStep()) {
            // Process the result set
            do {
                string order_start_time = query.getColumn(0).getText();
                string order_finish_time = query.getColumn(1).getText();
                intervals.insert({time_to_minutes(order_start_time), time_to_minutes(order_finish_time)});
            } while (query.executeStep());
        }

        // Check for overlap with the provided time interval
        pair<int, int> provided_interval = {start_minutes, finish_minutes};
        if (!intervals.empty()) {
            for (const auto &interval: intervals) {
                if (check_overlap(provided_interval, interval)) {
                    // Overlap detected
                    return true;
                }
            }
        }
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
    return false; // Return false by default (no conflicts or error occurred)
}

string choose_field_id(const string& city, const string& game_type) {
    try {
        bool valid_choice = false;
        string chosen_field_id;
        do {
        // Open your SQLite database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare the SQL query to select fields based on city and game type
        string query_str = "SELECT FieldId, Fieldtype FROM Fields WHERE City = ? AND Fieldtype = ?";
        Statement query(db, query_str);
        query.bind(1, city);
        query.bind(2, game_type);

        // Display available fields and prompt the user to choose a field ID
        ChangeColor(0,7);
        cout << "Available fields in " << city << " for " << game_type << ":" << endl;
        while (query.executeStep()) {
            string field_id = query.getColumn(0).getString();
            string game_type_string = query.getColumn(1).getString();
            cout << "Field ID: " << field_id << ", Game Type: " << game_type_string << endl;
        }
        ChangeColor(0,15);
        // Prompt the user to choose a field ID

            cout << "Enter the Field ID you want to choose: ";
            cin >> chosen_field_id;
            cleanBuffer();
            system("CLS");

            // Validate the user input against available field IDs
            query.reset(); // Reset the query to execute it again
            while (query.executeStep()) {
                string id = query.getColumn(0).getString();
                if (chosen_field_id == id) {
                    valid_choice = true;
                    break;
                }
            }
            if (!valid_choice) {
                ChangeColor(0,4);
                cout << "Invalid Field ID. Please choose from the available options." << endl;
                ChangeColor(0,15);
            }
        } while (!valid_choice);

        return chosen_field_id;
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
        // Return an empty string or handle the error as needed
        return "";
    }
}
// Function to convert Date struct to SQLite compatible date string
std::string date_to_sqlite_string(const Date& date) {
    return std::to_string(date.getYear()) + "-" +
           (date.getMonth() < 10 ? "0" : "") + std::to_string(date.getMonth()) + "-" +
           (date.getDay() < 10 ? "0" : "") + std::to_string(date.getDay());
}

// Function to get the current date
void get_current_date(int& day, int& month, int& year) {
    time_t t = std::time(nullptr); // Get the current time
    tm* now = std::localtime(&t);  // Convert it to local time

    // Extract year, month, and day components from the current time
    year = now->tm_year + 1900; // Years since 1900
    month = now->tm_mon + 1;     // Months are 0-based
    day = now->tm_mday;          // Day of the month
}

string choose_city_from_list(Database& db) {
    // Print available cities

    string chosen_city;
    bool valid_choice = false;
    do {
        print_available_cities(db);
        cout << "Enter the city you want to choose: ";
        getline(cin, chosen_city); // Read the entire line of input
        system("CLS");

        // Check if the chosen city exists in the Fields table
        try {
            Statement query(db, "SELECT COUNT(*) FROM Fields WHERE City = ?");
            query.bind(1, chosen_city);
            if (query.executeStep()) {
                int count = query.getColumn(0).getInt();
                if (count > 0) {
                    valid_choice = true;
                } else {
                    ChangeColor(0,4);
                    cout << "Invalid city. Please choose from the available options." << endl;
                    ChangeColor(0,15);
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
        system("CLS");

        // Check if the chosen field type exists in the Fields table
        try {
            Statement query(db, "SELECT COUNT(*) FROM Fields WHERE Fieldtype = ?");
            query.bind(1, chosen_field_type);
            if (query.executeStep()) {
                int count = query.getColumn(0).getInt();
                if (count > 0) {
                    valid_choice = true;
                } else {
                    ChangeColor(0,4);
                    cout << "Invalid field type. Please choose from the available options." << endl;
                    ChangeColor(0,15);
                }
            }
        } catch (exception& e) {
            cerr << "SQLite exception: " << e.what() << endl;
            return ""; // Return empty string on error
        }
    } while (!valid_choice);

    return chosen_field_type;
}

void cleanBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int time_to_minutes(const string& time_str) {
    int hours = stoi(time_str.substr(0, 2));
    int minutes = stoi(time_str.substr(3, 2));
    return hours * 60 + minutes;
}

// Function to check if two time intervals overlap
bool check_overlap(const pair<int, int>& interval1, const pair<int, int>& interval2) {
    return (interval1.first < interval2.second) && (interval2.first < interval1.second);
}


bool isDigitsOnly(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

