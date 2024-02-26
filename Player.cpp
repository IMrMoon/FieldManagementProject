//
// Created by sgvch on 25/02/2024.
//

#include <limits>
#include "Validation.h"
#include <cctype>
#include "Player.h"

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
            if (!check_gender(player_gender)) {
                cout << "Invalid Gender. Please enter a valid Gender M/F." << std::endl;
                phone_number_exists = true;
            } else {
                phone_number_exists = false;
            }
        } while (!check_phone_number(player_phone_number) || phone_number_exists);


    // Prepare a statement to insert a new player into the Players table
        try {
            // Open the database
            Database db("FieldManagement.db", OPEN_READWRITE | OPEN_CREATE);

            // Prepare a statement to insert a new player into the Players table
            Statement query(db,
                            "INSERT INTO Player (Id, Name, Email, \"Phone number\", Password, Gender) VALUES (?, ?, ?, ?, ?, ?)");

            int integer_id = stoi(player_id);;
            int integer_phoneNum = stoi(player_phone_number);;
            // Bind parameters to the statement
            query.bind(1, integer_id);
            query.bind(2, player_name);
            query.bind(3, player_email);
            query.bind(4, integer_phoneNum);
            query.bind(5, player_password);
            query.bind(6, player_gender);

            // Execute the statement
            query.exec();

            // Close the database (optional if you're done with the database)


        } catch (std::exception &e) {
            // Handle exceptions (e.g., print error message)
            std::cerr << "SQLite exception: " << e.what() << std::endl;
        }
    return player_id;
    }

string player_login(){

}

