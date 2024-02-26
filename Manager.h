//
// Created by sgvch on 25/02/2024.
//
#include <string>
#include "Date.h"
using namespace std;


#ifndef FIELDPROJECT_MANAGER_H
#define FIELDPROJECT_MANAGER_H

    string manager_register();
    string manager_login();
    bool addField(); //fix
    bool deleteField(long field_id_to_delete);
    bool edit_manager_details();
    float view_rate();
    bool mark_dates_as_unavailable();
    void view_field_orders(long field_id);
    void view_orders_by_date(const Date& other_date);







#endif //FIELDPROJECT_MANAGER_H
