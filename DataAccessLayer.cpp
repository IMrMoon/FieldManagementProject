//
// Created by sgvch on 25/02/2024.
//
#include "DataAccessLayer.h"
#include "Date.h"


set<string> get_available_cities() {
    set<string> cities;

    Database db("FieldManagement.db", OPEN_READONLY); // Open your SQLite database
    // Function to get available game types from the database

    try {
        SQLite::Statement query(db, "SELECT DISTINCT City FROM Fields");

        cout << "Available Cities:" << endl;
        while (query.executeStep()) {
            string fields_cities = query.getColumn(0).getText();
            cout << "- " << fields_cities << endl;
            cities.insert(fields_cities);
        }

        string chosen_city;
        do {
            cout << "Enter the game type you want to choose: ";
            cin >> chosen_city;

            if (cities.find(chosen_city) == cities.end()) {
                cout << "Invalid game type. Please choose from the available game types." << endl;
            }
        } while (cities.find(chosen_city) == cities.end());

        // Print fields details for the chosen game type
        SQLite::Statement fields_query(db, "SELECT FieldId, City, Fieldtype FROM Fields WHERE City = ?");
        fields_query.bind(1, chosen_city);

        cout << "Fields for game type " << chosen_city << ":" << endl;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0).getInt();
            string city = fields_query.getColumn(1).getText();
            string field_type = fields_query.getColumn(2).getText();
            cout << "Field ID: " << field_id << ", City: " << city << ", Field Type: " << field_type << endl;
        }

    } catch (exception &e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
    return cities;
}
// Function to retrieve a set of unique game types from the fields table
set<string> get_available_game_types() {

    Database db("FieldManagement.db", OPEN_READONLY); // Open your SQLite database
    // Function to get available game types from the database
    set<string> game_types;

    try {
        SQLite::Statement query(db, "SELECT DISTINCT Fieldtype FROM Fields");

        cout << "Available game types:" << endl;
        while (query.executeStep()) {
            string game_type = query.getColumn(0).getText();
            cout << "- " << game_type << endl;
            game_types.insert(game_type);
        }

        string chosen_game_type;
        do {
            cout << "Enter the game type you want to choose: ";
            cin >> chosen_game_type;

            if (game_types.find(chosen_game_type) == game_types.end()) {
                cout << "Invalid game type. Please choose from the available game types." << endl;
            }
        } while (game_types.find(chosen_game_type) == game_types.end());

        // Print fields details for the chosen game type
        SQLite::Statement fields_query(db, "SELECT FieldId, City, Fieldtype FROM Fields WHERE Fieldtype = ?");
        fields_query.bind(1, chosen_game_type);

        cout << "Fields for game type " << chosen_game_type << ":" << endl;
        while (fields_query.executeStep()) {
            int field_id = fields_query.getColumn(0).getInt();
            string city = fields_query.getColumn(1).getText();
            string field_type = fields_query.getColumn(2).getText();
            cout << "Field ID: " << field_id << ", City: " << city << ", Field Type: " << field_type << endl;
        }

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

        cout << "Available cities:" << endl;
        while (query.executeStep()) {
            string city = query.getColumn(0).getText();
            cout << "- " << city << endl;
        }
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

bool get_and_choose_player_orders(string player_id) {
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

        if (count == 0) {
            cout << "No orders found for player with ID: " << player_id << endl;
            return false; // Return empty string indicating no order chosen
        }

        // Ask the player to choose an order
        int choice;
        cout << "Choose an order by entering the corresponding number: ";
        cin >> choice;

        // Validate the choice
        if (choice < 1 || choice > count) {
            cout << "Invalid choice. Please choose a valid order." << endl;
            return false; // Return empty string indicating no order chosen
        }

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

        cout << "Order with ID " << chosen_order_id << " successfully deleted." << endl;

         // Return the chosen order ID
    } catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
        return false; // Return empty string indicating an error occurred
    }return true;
}

