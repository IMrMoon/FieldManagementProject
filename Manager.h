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

    void view_field_orders(std::string manager_id) ;
    void view_orders_by_date(std::string manager_id);
void mark_dates_as_unavailable(std::string manager_id, int field_id, std::string order_date, std::string start_time, std::string end_time);






#endif //FIELDPROJECT_MANAGER_H
