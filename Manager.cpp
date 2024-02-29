//
// Created by sgvch on 25/02/2024.
//

#include "Manager.h"
#include "Validation.h"


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
