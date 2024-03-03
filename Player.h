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
    bool edit_player_details(string player_id);
    void view_upcoming_orders(string playerId);
    bool field_rate(string playerId);
    bool view_previous_games(string playerId);
    bool isValidRating(double rating);
    void parseDateString(const std::string& dateString, int& day, int& month, int& year);
    Date parse_date(const std::string& date_str);




#endif //FIELDPROJECT_PLAYER_H
