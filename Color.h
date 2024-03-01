//
// Created by sgvch on 29/02/2024.
//
#include <windows.h>
#ifndef FIELDMANAGEMENTPROJECT_COLOR_H
#define FIELDMANAGEMENTPROJECT_COLOR_H
#include <string>
using namespace std;
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void ChangeColor(int textColor,int backgroundColor);

void centerAlign(const std::string& text, int totalWidth);


#endif //FIELDMANAGEMENTPROJECT_COLOR_H
