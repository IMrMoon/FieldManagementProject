//
// Created by sgvch on 25/02/2024.
//

#include <string>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Date.h"


using namespace SQLite;
#ifndef FIELDPROJECT_PLAYER_H
#define FIELDPROJECT_PLAYER_H


    
    string player_register();
    string player_login();
    bool schedule_game(string player_id);
    bool delete_game_order(Date date, time_t order_time, string field_type);
    void view_fields_by_fieldType();
    void view_fields_by_city();
    bool edit_player_details();
    void view_player_games();
    void view_previous_games();
    bool field_rate();
    void set_text_color(int color);




#endif //FIELDPROJECT_PLAYER_H
