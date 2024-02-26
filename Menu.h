//
// Created by sgvch on 26/02/2024.
//

#include "Manager.h"
#include "Player.h"
#include "Field.h"
#include "Order.h"
#include "DataAccessLayer.h"
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;
#ifndef FIELDPROJECT_MENU_H
#define FIELDPROJECT_MENU_H

void first_menu();
void player_menu(string& player_id);
void manager_menu(string& manager_id);
void player_reg_or_login_menu();
void manager_reg_or_login_menu();
void set_text_color(int color);




#endif //FIELDPROJECT_MENU_H
