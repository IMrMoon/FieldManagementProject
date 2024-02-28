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


set<string> get_available_cities(Database& db);
set<string> get_available_game_types(Database& db);
string getNextOrderIdFromDatabase(Database& db);
string getManagerIdByFieldId(const string& fieldId);
void print_available_cities(Database& db);
void print_available_field_types(Database& db);

#endif //FIELDPROJECT_DATAACCESSLAYER_H
