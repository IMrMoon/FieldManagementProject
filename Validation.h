//
// Created by sgvch on 26/02/2024.
//
#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
#include <string>
#include <regex> // For regular expressions
using namespace std;
using namespace SQLite;
#ifndef FIELDMANAGEMENTPROJECT_VALIDATION_H
#define FIELDMANAGEMENTPROJECT_VALIDATION_H

///validation for every input
bool check_id(const string& id);
bool check_existing_id(const string& id);
bool check_name(const string& name);
bool check_email(const string& email);
bool check_existing_email(const string& email);
bool check_password(const string& password);
bool check_phone_number(const string& password);
bool check_existing_phone_number(const string& phone_number);
bool check_gender(char gender);


#endif //FIELDMANAGEMENTPROJECT_VALIDATION_H
