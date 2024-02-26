//
// Created by sgvch on 26/02/2024.
//

#include "Validation.h"

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