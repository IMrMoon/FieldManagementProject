//
// Created by sgvch on 25/02/2024.
//
#include "Manager.h"
#include "Player.h"
#include "Field.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <set>
#include <vector>
using namespace SQLite;
using namespace std;
#ifndef FIELDPROJECT_DATAACCESSLAYER_H
#define FIELDPROJECT_DATAACCESSLAYER_H


set<string> get_available_cities();
set<string> get_available_game_types();
string getNextOrderIdFromDatabase(Database& db);
string getManagerIdByFieldId(const string& fieldId);
void print_available_cities(Database& db);
void print_available_field_types(Database& db);
bool get_and_choose_player_orders(string player_id);
string get_field_id(string manager_id);
void clean_DAL_buffer();


#endif //FIELDPROJECT_DATAACCESSLAYER_H
