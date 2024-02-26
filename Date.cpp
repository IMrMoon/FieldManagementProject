#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

Date::Date() {
    this->day = 1;
    this->month = 1;
    this->year = 1;
}

Date::Date(int day, int month, int year) {
    try {
        if (year < 1000) {
            cout << "Bad year";
            throw year;
        }
        this->year = year;
        if (this->Isleapyear() && month == 2) {//if it is a leap year and the month isnt feburary then the leap year doesnt matter//
            if (day > 28 || day < 1) {
                cout << "Bad day you entered a leap year which means in feburay there are only 28 days\n";
                throw day;
            }
        }
        if (month < 1 || month > 12) {
            throw month;
        }
        this->month = month;

        if (day<1 || day>this->HowManyDays()) {
            cout << "You have entered a bad day the day for the month you chose should be between 1 to " << this->HowManyDays() << endl;
            throw day;
        }
        this->day = day;
    }
    catch (int a) {
        cout << "Wrong input so you get default parameters:\n";
        this->day = 1;
        this->month = 1;
        this->year = 1996;
    }




}


bool Date::operator==(Date& other) {
    if (this->year != other.year)
        return false;
    if (this->month != other.month)
        return false;
    if (this->day != other.day)
        return false;
    return true;
}

bool Date::operator>(Date& other) {
    if (this->year > other.year)
        return true;
    if (this->year == other.year) {
        if (this->month > other.month)
            return true;
        if (this->month == other.month) {
            if (this->day > other.day)
                return true;
        }
    }
    return false;
}


bool Date::operator<(Date& other) {
    if (this->year < other.year) {
        return true;
    }

    if (this->year == other.year) {
        if (this->month < other.month) {
            return true;
        }
        if (this->month == other.month) {
            if (this->day < other.day) {
                return true;
            }
        }
    }
    return false;

}

void Date::printDate() {
    cout << "The date is-->" << this->day << "/" << this->month << "/" << this->year << endl;

}

int Date::HowManyDays() {
    switch (this->month) {
        case 1:
            return 31;
        case 2:
            if (this->Isleapyear()) {
                return 29;
            }
            else
                return 28;
        case 3:
            return 31;
        case 5:
            return 31;
        case 7:
            return 31;
        case 8:
            return 31;
        case 10:
            return 31;
        case 12:
            return 31;
        default:
            return 30;
    }
}

bool Date::Isleapyear() {
    // leap year if perfectly divisible by 400
    if (this->year % 400 == 0) {
        return true;
    }
        // not a leap year if divisible by 100
        // but not divisible by 400
    else if (this->year % 100 == 0) {
        return false;
    }
        // leap year if not divisible by 100
        // but divisible by 4
    else if (this->year % 4 == 0) {
        return true;
    }
        // all other years are not leap years
    else {
        return false;
    }
}