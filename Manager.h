//
// Created by sgvch on 25/02/2024.
//
#include <string>
#include "Date.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <iostream>
using namespace SQLite;
using namespace std;


#ifndef FIELDPROJECT_MANAGER_H
#define FIELDPROJECT_MANAGER_H

    string manager_register();
    string manager_login();
    bool addField(string manager_id);
    bool deleteField(string manager_id);
    bool edit_manager_details(string manager_id);
    float view_rate();
    void mark_dates_as_unavailable(string manager_id);
    void view_field_orders(string manager_id);
    void view_orders_by_date(string manager_id);







#endif //FIELDPROJECT_MANAGER_H
