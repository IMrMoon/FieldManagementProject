//
// Created by sgvch on 25/02/2024.
//
#pragma once
#include <iostream>
using namespace std;
#ifndef FIELDPROJECT_DATE_H
#define FIELDPROJECT_DATE_H


class Date {
private:
    int day, month, year;
public:
    Date();
    Date(int day, int month, int year);
    //Date(Date& other);
    //void operator+=(Date& other);
    bool operator==(Date& other);
    bool operator>(Date& other);
    bool operator<(Date& other);
    friend ostream& operator<<(ostream& os, const Date& other) {
        os << "[" << other.day << "/" << other.month << "/" << other.year << "]";
        return os;
    }
    friend istream& operator>>(istream& is, Date& other) {
        is >> other.day >> other.month >> other.year;
        return is;
    }
    int getDay() const{ return this->day; }
    int getMonth() const{ return this->month; }
    int getYear() const{ return this->year; }






    void printDate();
    int HowManyDays();
    bool Isleapyear();
};



#endif //FIELDPROJECT_DATE_H
