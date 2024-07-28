/* Program name: date.h
 * Author: Adolphe Dimandja
 * Date last updated: 7/28/2024
 * Purpose: Header file for the Date class, which includes member variables for month, day, and year, and methods for various operations.
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int month;
    int day;
    int year;

    bool isValidDate(int m, int d, int y) const;
    bool isLeapYear(int y) const;

public:
    Date(int m = 1, int d = 1, int y = 2000);

    int getMonth() const;
    int getDay() const;
    int getYear() const;

    void setMonth(int m);
    void setDay(int d);
    void setYear(int y);

    Date operator+(int days) const;
    friend Date operator+(int days, const Date& date);
    Date operator-(int days) const;
    friend Date operator-(int days, const Date& date);

    Date& operator++();       // Pre-increment
    Date operator++(int);     // Post-increment
    Date& operator--();       // Pre-decrement
    Date operator--(int);     // Post-decrement

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;

    friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

#endif // DATE_H
