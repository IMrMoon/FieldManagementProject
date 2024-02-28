//
// Created by sgvch on 25/02/2024.
//
#include "DataAccessLayer.h"
#include "Date.h"



//#include "DataAccessLayer.h"


set<string> get_available_cities(Database& db) {
    set<string> cities;

    try {
        Statement query(db, "SELECT DISTINCT city FROM fields");

        while (query.executeStep()) {
            cities.insert(query.getColumn(0).getText());
        }
    } catch (exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }

    return cities;
}
// Function to retrieve a set of unique game types from the fields table
set<string> get_available_game_types(Database& db) {
    set<string> game_types;

    try {
        Statement query(db, "SELECT DISTINCT game_type FROM fields");

        while (query.executeStep()) {
            string game_type = query.getColumn(0).getText();
            game_types.insert(game_type);
        }
    } catch (exception& e) {
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