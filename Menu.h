//
// Created by sgvch on 26/02/2024.
//

#include "Manager.h"
#include "Player.h"
#include "Field.h"
#include "Order.h"
#include "DataAccessLayer.h"

using namespace std;
#ifndef FIELDPROJECT_MENU_H
#define FIELDPROJECT_MENU_H

enum manager_Or_player {manager = 1 , player, exit1};
enum reg_or_login {reg = 1, login};
enum player_options {schedule_game_player = 1, cancel_game, search_field_by_type, search_field_by_city, edit_details_player, view_future_games, view_games_history, rate_a_field, quit1};
enum manager_options {add_field = 1, delete_field, edit_details_manager, view_future_games_by_date, view_future_games_by_field, make_unavailable_dates, view_rate_manager, quit2};


void first_menu();
void player_menu(string player_id);
void manager_menu(string manager_id);
void player_reg_or_login_menu();
void manager_reg_or_login_menu();





#endif //FIELDPROJECT_MENU_H
