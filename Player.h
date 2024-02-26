//
// Created by sgvch on 25/02/2024.
//

#include "Order.h"
#include "SQLiteCpp/SQLiteCpp.h"
using namespace SQLite;
#ifndef FIELDPROJECT_PLAYER_H
#define FIELDPROJECT_PLAYER_H


    
    string player_register();
    string player_login();
    bool schedule_game();
    bool delete_game_order(Date date, time_t order_time, string field_type);
    void view_fields_by_fieldType();
    void view_fields_by_city();
    bool edit_player_details();
    void view_player_games();
    void view_previous_games();
    bool field_rate();




#endif //FIELDPROJECT_PLAYER_H
