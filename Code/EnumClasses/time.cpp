#include <iostream>
#include <array>

/** Coding conventions

 1.    <name>_t : typedef/using statement
 2.    <Name> : Enum class or enum class element
 3.    <name>_class : class name
 4.    <name> : (local) object/variable name or member function name
 5.    m_<name> : data member name

 6.    curly braces for scoping should be in a new line and not followed
       by any statement, except (optionally) for member functions mabe of
       a most a sigle return statement.

 7.    Arithmetic and logic operators and assignments should be
       surrounded by at least one space.

 8.    classes and structs should be formatted as follow

       class class_name {
           data members

           constructors

           operators

           member functions
       };
*/

using day_t = int; // Now, day_t is a typedef, and Year has a
                   // conversion operator to int, which not explicit,
                   // so it will be possible to pass a year_class
                   // object as a day. This may be lead to potential
                   // errors. We implemented a check to see that the
                   // day is compatible with the month, so this would
                   // be catched as a runtime error (years can only be
                   // 4 digits). The error message could be confusing
                   // for the user, though.

// Using enum classes for the months may be not optimal, since we need
// also additional functionality for printing the month name. Maybe a
// class, like the year_class may be better.
enum class Month {Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};


/** Function to translate a Month element in a string
 */
std::string month_str(Month m) {
    // The following array coulsd have be placed in the global scope,
    // but by putting it here we made the code less sparse. By making
    // it static we avoided potential initialization overheds every
    // time we call the function. In this case the price is paid only
    // once.
    static std::array<std::string, 12> _month_str{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "Decemper"};

    return _month_str[static_cast<int>(m)];
}

/**
   Class that implement a year value
 */
class year_class {
    static const int first = 2000;
    static const int last = 2100;

    int value;

public:
    year_class() : value{first} {}
    year_class(int v) : value{v} {
        if (v<first or v>last) {
            throw(std::runtime_error("year_class is not valid at construction\n"));
        }
    }

    operator int() {return value;}

    bool is_valid(int y) const {
        return (y >= first) and (y <= last);
    }

    bool is_leap() const {
        return (value%4==0) and not (value%400==0);
    }
};


class date_type
{
    year_class m_year = 2000;
    Month m_month = Month::Jan;
    day_t m_day = 1;

public:
    date_type (year_class y, Month m, day_t d)
        : m_year(y)
        , m_month(m)
        , m_day(d)
    {
        int maxdays = m_year.is_leap()?29:28;
        switch (m_month)
            {
            case Month::Jan:
            case Month::Mar:
            case Month::May:
            case Month::Jul:
            case Month::Aug:
            case Month::Oct:
            case Month::Dec:
                if (m_day < 1 or m_day > 31)
                    {
                        throw(std::runtime_error(month_str(m_month) + " has 31 days: day " + std::to_string(m_day) + " is invalid\n"));
                    }
                break;
            case Month::Feb:
                if (m_day < 1 or m_day > maxdays)
                    {
                        throw(std::runtime_error(month_str(m_month) + " has " + std::to_string(maxdays) + " days: day " + std::to_string(m_day) + " is invalid\n"));
                    }
                break;
            case Month::Apr:
            case Month::Jun:
            case Month::Sep:
            case Month::Nov:
                if (m_day < 1 or m_day > 30)
                    {
                        throw(std::runtime_error(month_str(m_month) + " has 31 days: day " + std::to_string(m_day) + " is invalid\n"));
                    }
                break;
            default:
                throw(std::runtime_error("Invalid month somehow: " + std::to_string(static_cast<int>(m_month)) + "\n"));
        }
    }

    year_class year() const {return m_year;}
    Month month() const {return m_month;}
    day_t day() const {return m_day;}
};

// Printing the date in a fixed format
std::ostream& operator<<(std::ostream& s, date_type date) {
    return s << date.year() << "-" << static_cast<int>(date.month()) << "-" << date.day();
}



int main() {

    std::cout << "Setting a time\n";


    date_type date(2017, Month::Aug, 15);

    std::cout << date << "\n";

    try {
        date_type date(2117, Month::Aug, 15);
    }
    catch (std::runtime_error const& e) {
        std::cout << "------> Wrong year\n";
        std::cout << e.what();
    }

    try {
        date_type date(2017, static_cast<Month>(100), 15);
    }
    catch (std::runtime_error const& e) {
        std::cout << "------> Wrong month\n";
        std::cout << e.what();
    }

    try {
        date_type date(2017, Month::Feb, 30);
    }
    catch (std::runtime_error const& e) {
        std::cout << "------> Wrong day of the month\n";
        std::cout << e.what();
    }
}
