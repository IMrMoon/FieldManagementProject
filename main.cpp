//
// Created by sgvch on 26/02/2024.
//
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include "Player.h"
#include "Menu.h"
using namespace std;
using namespace SQLite;

int main(){
    Database db("FieldManagement.db", OPEN_READWRITE|OPEN_CREATE);
    first_menu();
return 0;
}