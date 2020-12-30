//implementation of record class

#include "Record.h"
#include <iostream>
#include <string>

using namespace std;

string Record::get_title() const {
    return this->title;
}
string Record::get_author() const {
    return this->author;
}
string Record::get_edition() const {
    return this->edition;
}
string Record::get_ISBN() const {
    return this->ISBN;
}
string Record::get_year() const {
    return this->year;
}
void Record::set_title(string t) {
    title = t;
}
void Record::set_author(string a) {
    author = a;
}
void Record::set_ISBN(string i) {
    ISBN = i;
}
void Record::set_year(string y) {
    year = y;
}
void Record::set_edition(string e) {
    edition = e;
}

istream& operator>>(istream& iss, Record& rec) {
    string blank;
    string hold;
    string sTitle;
    string sAuthor;
    string sEdition;
    string sISBN;
    string sYear;
    getline(iss, blank);
    getline(iss, sTitle);
    getline(iss, sAuthor);
    getline(iss, sISBN);
    getline(iss, sYear);
    getline(iss, sEdition);
    if (blank != "") {
    }
    else {
        rec.set_title(sTitle);
        rec.set_author(sAuthor);
        rec.set_ISBN(sISBN);
        rec.set_year(sYear);
        rec.set_edition(sEdition);
        return iss;
    }
    return iss;
}

ostream& operator<<(std::ostream& os, Record& rec) {
    os << rec.get_title() << endl;
    os << rec.get_author() << endl;
    os << rec.get_ISBN() << endl;
    os << rec.get_year() << endl;
    os << rec.get_edition() << endl;
    return os;
}

bool operator==(const Record& r1, const Record& r2) {
    if (r1.get_title() == r2.get_title() && r1.get_author() == r2.get_author() && r1.get_ISBN() == r2.get_ISBN()) {
        return true;
    }
    else
        return false;
}
