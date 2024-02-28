//
// Created by sgvch on 25/02/2024.
//

#include "Order.h"
#include "Date.h"
#include "DataAccessLayer.h"

//#include "DataAccessLayer.h"



std::string get_field_id(std::string manager_id) {
    std::string field_id;

    try {
        // Open the SQLite database
        SQLite::Database db("FieldManagement.db", SQLite::OPEN_READWRITE);

        // Prepare the SQL query to get the field ID managed by the specified manager
        std::string field_query_str = "SELECT FieldId FROM Fields WHERE ManagerId = ?";
        SQLite::Statement field_query(db, field_query_str);
        field_query.bind(1, manager_id);

        // Execute the query
        if (field_query.executeStep()) {
            // Retrieve the field ID from the result set
            field_id = field_query.getColumn(0).getString();
        } else {
            std::cout << "Manager ID: " << manager_id << " does not manage any fields." << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }

    return field_id;
}