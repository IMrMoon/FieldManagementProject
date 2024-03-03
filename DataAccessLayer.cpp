//
// Created by sgvch on 25/02/2024.
//
#include "Color.h"
#include "DataAccessLayer.h"
#include "Date.h"


set<string> get_available_cities() {
    set<string> cities;

    try {
        Database db("FieldManagement.db", OPEN_READONLY); // Open your SQLite database

        // Retrieve available cities from the database
        Statement query(db, "SELECT DISTINCT City FROM Fields");
        cout << "Available Cities:" << endl;
        while (query.executeStep()) {
            string fields_city = query.getColumn(0).getText();
            cout << "- " << fields_city << endl;
            cities.insert(fields_city);
        }

        // Prompt the user to choose a city
        string chosen_city;
        do {
            cout << "Enter the city you want to choose: ";
            cin >> chosen_city;

            if (cities.find(chosen_city) == cities.end()) {
                cout << "Invalid city. Please choose from the available cities." << endl;
            }
        } while (cities.find(chosen_city) == cities.end());

        // Print fields details for the chosen city
        Statement fields_query(db, "SELECT FieldId, City, FieldType FROM Fields WHERE City = ?");
        fields_query.bind(1, chosen_city);
        cout << "Fields for city " << chosen_city << ":" << endl;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0).getInt();
            string city = fields_query.getColumn(1).getText();
            string field_type = fields_query.getColumn(2).getText();
            cout << "Field ID: " << field_id << ", City: " << city << ", Field Type: " << field_type << endl;
        }
    } catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return cities;
}

// Function to retrieve a set of unique game types from the fields table
set<string> get_available_game_types() {

    Database db("FieldManagement.db", OPEN_READONLY); // Open your SQLite database
    // Function to get available game types from the database
    set<string> game_types;

    try {
        string chosen_game_type;
        do {

        SQLite::Statement query(db, "SELECT DISTINCT Fieldtype FROM Fields");
        ChangeColor(0,7);
        cout << "Available game types:" << endl;
        while (query.executeStep()) {
            string game_type = query.getColumn(0).getText();
            cout << "- " << game_type << endl;
            game_types.insert(game_type);
        }
        ChangeColor(0,15);

            cout << "Enter the game type you want to choose: ";
            cin >> chosen_game_type;

            if (game_types.find(chosen_game_type) == game_types.end()) {
                ChangeColor(0,4);
                cout << "Invalid game type. Please choose from the available game types." << endl;
                ChangeColor(0,15);
            }
        } while (game_types.find(chosen_game_type) == game_types.end());

        // Print fields details for the chosen game type
        SQLite::Statement fields_query(db, "SELECT FieldId, City, Fieldtype FROM Fields WHERE Fieldtype = ?");
        fields_query.bind(1, chosen_game_type);
        ChangeColor(0,7);
        cout << "Fields for game type " << chosen_game_type << ":" << endl;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0).getInt();
            string city = fields_query.getColumn(1).getText();
            string field_type = fields_query.getColumn(2).getText();
            cout << "Field ID: " << field_id << ", City: " << city << ", Field Type: " << field_type << endl;
        }
        ChangeColor(0,15);

    } catch (exception &e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
    return game_types;
}

string getNextOrderIdFromDatabase(Database& db) {
    // Prepare SQL query to get the maximum order_id
    Statement query(db, "SELECT MAX(OrderId) FROM Orders");

    // Execute the query
    if (query.executeStep()) {
        // Retrieve the maximum order_id (last inserted ID)
        int max_order_id = query.getColumn(0).getInt();

        // Increment the last inserted ID to get the next available order ID
        return to_string(max_order_id + 1);
    }

    // If there are no orders in the database, start with order ID 1
    return "1";
}

string getManagerIdByFieldId(const string& fieldId) {
    string managerId;

    try {
        // Open the database
        Database db("FieldManagement.db");

        // Prepare SQL query to retrieve ManagerId based on field_id
        Statement query(db, "SELECT ManagerId FROM Fields WHERE FieldId = ?");
        query.bind(1, fieldId); // Bind the field_id parameter

        // Execute the query
        if (query.executeStep()) {
            // Retrieve the ManagerId from the result set
            managerId = query.getColumn(0).getString();
        }
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }

    return managerId;
}

void print_available_cities(Database& db) {
    try {
        Statement query(db, "SELECT DISTINCT City FROM Fields");
        ChangeColor(0,7);
        cout << "Available cities:" << endl;
        while (query.executeStep()) {
            string city = query.getColumn(0).getText();
            cout << "- " << city << endl;
        }
        ChangeColor(0,15);
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}
// Function to print available field types from the Fields table
void print_available_field_types(Database& db) {
    try {
        Statement query(db, "SELECT DISTINCT Fieldtype FROM Fields");

        cout << "Available field types:" << endl;
        while (query.executeStep()) {
            string field_type = query.getColumn(0).getText();
            cout << "- " << field_type << endl;
        }
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

bool get_and_choose_player_orders(string player_id) { ///player cancel game
    string order_id;
    string order_date;
    string order_start_time;
    string order_end_time;
    try {
        // Open the database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare SQL query to fetch orders for the given player_id
        SQLite::Statement query(db, "SELECT OrderId, Orderdate, OrderStartTime, OrderFinishTime FROM Orders WHERE PlayerId = ?");
        query.bind(1, player_id);

        int count = 0;
        ChangeColor(0,7);
        // Execute the query and fetch orders
        while (query.executeStep()) {
            ++count;
            order_id = query.getColumn(0).getString();
            order_date = query.getColumn(1).getString();
            order_start_time = query.getColumn(2).getString();
            order_end_time = query.getColumn(3).getString();

            // Print order details
            cout << count << ". Order ID: " << order_id << ", Date: " << order_date
                 << ", Start Time: " << order_start_time << ", End Time: " << order_end_time << endl;
        }
        ChangeColor(0,15);
        if (count == 0) {
            ChangeColor(0,4);
            cout << "No orders found for player with ID: " << player_id << endl;
            ChangeColor(0,15);
            return false; // Return empty string indicating no order chosen
        }

        // Ask the player to choose an order
        int choice;
        while (true) {
            cout << "Choose an order by entering the corresponding number: ";

            // Check if input is a valid integer
            if (cin >> choice) {
                // Validate the choice
                if (choice >= 1 && choice <= count) {
                    break; // Valid choice, exit the loop
                } else {
                    ChangeColor(0,4);
                    cout << "Invalid choice. Please choose a valid order." << endl;
                    ChangeColor(0,15);
                }
            } else {
                // Clear the error state and ignore the invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ChangeColor(0,4);
                cout << "Invalid input. Please enter a valid integer." << endl;
                ChangeColor(0,15);
            }
        }
        system("CLS");

        // Fetch the chosen order ID
        query.reset(); // Reset the query to the beginning
        for (int i = 0; i < choice; ++i) {
            query.executeStep();
        }
        string chosen_order_id = query.getColumn(0).getString();

        // Delete the chosen order from the database
        SQLite::Statement delete_query(db, "DELETE FROM Orders WHERE OrderId = ?");
        delete_query.bind(1, chosen_order_id);
        delete_query.exec();
        ChangeColor(0,2);
        cout << "Order Number: [" << chosen_order_id << "] successfully deleted." << endl;
        ChangeColor(0,15);

         // Return the chosen order ID
    } catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
        return false; // Return empty string indicating an error occurred
    }return true;
}

string get_field_id(string manager_id) {

    try {
        // Open your SQLite database
        Database db("FieldManagement.db", OPEN_READONLY);

        // Prepare the SQL query to select fields based on city and game type
        string query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
        Statement query(db, query_str);
        query.bind(1, manager_id);
        ChangeColor(0,7);
        // Display available fields and prompt the user to choose a field ID
        cout << "Available fields for manager: " << manager_id << ":" << endl;
        while (query.executeStep()) {
            string field_id = query.getColumn(0).getString();
            cout << "Field ID: " << field_id  <<  endl;
        }
        ChangeColor(0,15);
        // Prompt the manager to choose a field ID
        string field_id;
        bool valid_choice = false;
        do {
            cout << "Enter the Field ID you want to choose: ";
            cin >> field_id;
            clean_DAL_buffer();
            system("CLS");

            // Validate the user input against available field IDs
            query.reset(); // Reset the query to execute it again
            while (query.executeStep()) {
                string id = query.getColumn(0).getString();
                if (field_id == id) {
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

        return field_id;
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
        // Return an empty string or handle the error as needed
        return "";
    }
}

void clean_DAL_buffer(){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getNextFieldIdFromDatabase(Database& db)
{
    Statement query(db, "SELECT MAX(FieldId) FROM Fields");

    // Execute the query
    if (query.executeStep()) {
        // Retrieve the maximum field_id (last inserted ID)
        int max_field_id = query.getColumn(0).getInt();

        // Increment the last inserted ID to get the next available order ID
        return to_string(max_field_id + 1);
    }

    // If there are no Fields in the database, start with field ID 1
    return "1";
}

string getCityNameFromManagerTable(Database& db, string manager_id)
{
    // Prepare SQL query to get the city_name based on manager_id from the Manager table
    string sql = "SELECT City FROM Manager WHERE Id = ?";
    Statement query(db, sql);
    query.bind(1, manager_id);

    // Execute the query
    if (query.executeStep()) {
        // Retrieve the city_name
        return query.getColumn("City").getText();
    }

    // If no result is found, return an empty string or handle it based on your requirements
    return "";
}