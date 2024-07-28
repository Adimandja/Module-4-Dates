/* Program name: date.cpp
 * Author: Adolphe Dimandja
 * Date last updated: 7/28/2024
 * Purpose: Implementation file for the Date class, which includes methods for various operations and operator overloading.
 */

#include "date.h"
#include <iostream>
#include <iomanip>

const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool Date::isLeapYear(int y) const {
    if (y % 4 != 0) return false;
    if (y % 100 != 0) return true;
    if (y % 400 != 0) return false;
    return true;
}

bool Date::isValidDate(int m, int d, int y) const {
    if (y < 0) return false;
    if (m < 1 || m > 12) return false;

    int days = daysInMonth[m - 1];
    if (m == 2 && isLeapYear(y)) days++;

    return d >= 1 && d <= days;
}

Date::Date(int m, int d, int y) {
    if (isValidDate(m, d, y)) {
        month = m;
        day = d;
        year = y;
    } else {
        std::cerr << "Invalid date. Setting to January 1, 2000.\n";
        month = 1;
        day = 1;
        year = 2000;
    }
}

int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
int Date::getYear() const { return year; }

void Date::setMonth(int m) {
    if (isValidDate(m, day, year)) {
        month = m;
    } else {
        std::cerr << "Invalid month value.\n";
    }
}

void Date::setDay(int d) {
    if (isValidDate(month, d, year)) {
        day = d;
    } else {
        std::cerr << "Invalid day value.\n";
    }
}

void Date::setYear(int y) {
    if (isValidDate(month, day, y)) {
        year = y;
    } else {
        std::cerr << "Invalid year value.\n";
    }
}

Date Date::operator+(int days) const {
    Date newDate = *this;
    newDate.day += days;

    while (newDate.day > daysInMonth[newDate.month - 1] + (newDate.month == 2 && isLeapYear(newDate.year))) {
        newDate.day -= daysInMonth[newDate.month - 1] + (newDate.month == 2 && isLeapYear(newDate.year));
        newDate.month++;
        if (newDate.month > 12) {
            newDate.month = 1;
            newDate.year++;
        }
    }

    return newDate;
}

Date operator+(int days, const Date& date) {
    return date + days;
}

Date Date::operator-(int days) const {
    Date newDate = *this;
    newDate.day -= days;

    while (newDate.day < 1) {
        newDate.month--;
        if (newDate.month < 1) {
            newDate.month = 12;
            newDate.year--;
        }
        newDate.day += daysInMonth[newDate.month - 1] + (newDate.month == 2 && newDate.isLeapYear(newDate.year));
    }

    return newDate;
}

Date operator-(int days, const Date& date) {
    return date - days;
}

Date& Date::operator++() {
    *this = *this + 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    *this = *this + 1;
    return temp;
}

Date& Date::operator--() {
    *this = *this - 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    *this = *this - 1;
    return temp;
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

std::istream& operator>>(std::istream& in, Date& date) {
    int m, d, y;
    in >> m >> d >> y;
    if (!date.isValidDate(m, d, y)) {
        std::cerr << "Invalid date. Setting to January 1, 2000.\n";
        date.month = 1;
        date.day = 1;
        date.year = 2000;
    } else {
        date.month = m;
        date.day = d;
        date.year = y;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << std::setfill('0') << std::setw(4) << date.year << '-'
        << std::setw(2) << date.month << '-'
        << std::setw(2) << date.day;
    return out;
}
