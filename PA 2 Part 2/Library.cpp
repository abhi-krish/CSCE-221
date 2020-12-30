#include "Library.h"
#include "TemplatedDLList.h"
#include "Record.h"
#include <cctype>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<Record> Library::search(string title) {
    vector<Record> ret;
    int counter = 0;
    char value = toupper(title[0]);
    int x = int(value) - 65;
    DLListNode<Record>* hold = book_db.at(x).first_node();
    while (hold->next != nullptr) {
        if (hold->obj.get_title() == title) {
            ret.push_back(hold->obj);
            break;
        }
        hold = hold->next;
    }
    return ret;
}

int Library::import_database(string filename) {
    int counter = 0;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Did not open the file" << endl;
        return -1;
    }
    Record rec;
    while (ifs >> rec) {
        int x = (int)(toupper(rec.get_title()[0]))-65;
        book_db.at(x).insert_first(rec);
        counter++;
    }
    return counter;
}

int Library::export_database(string filename) {
    int counter = 0;
    ofstream ofs;
    ofs.open(filename);
    for (int i = 0; i < 26; i++) {
        DLListNode<Record>* hold = book_db.at(i).first_node();
        while (hold->next != nullptr) {
            ofs << hold->obj << endl;
            counter++;
            hold = hold->next;
        }
    }
    return counter;
}

void Library::print_database() {
    for (int i = 0; i < 26; i++) {
        DLListNode<Record>* node = book_db.at(i).first_node();
        while (node->next != nullptr) {
            cout << node->obj << endl;
            node = node->next;
        }
    }
}

bool Library::add_record(Record book) {
    int x = int(toupper(book.get_title()[0])) - 65;
    book_db.at(x).insert_last(book);
    return true;
}

void Library::remove_record(Record book) {
    cout << "They reached here!!" << endl;
    int x = int(toupper(book.get_title()[0])) - 65;
    DLListNode<Record>* node = book_db.at(x).first_node();
    while (node->next != nullptr) {
        if (node->obj == book) {
            Record removed = book_db.at(x).remove_after(*node->prev);
        }
        node = node->next;
    }
}

char Library::prompt_yes_no() {
    bool check = true;
    char answer;
    while (check == true) {
        cout << "Enter Y or N: " << endl;
        cin >> answer;
        if (answer == 'Y' || answer == 'N') {
            return answer;
            check = false;
        }
        else {
            cout << "Enter Y or N: " << endl;
            cin >> answer;
            check = true;
        }
    }
    return answer;
}

int Library::prompt_menu(vector<string> prom) {
    int index = 1;
    for (int i = 0; i < prom.size(); i++) {
        cout << index << ". " << prom.at(i) << endl;
        index++;
    }
    int value;
    cin >> value;
    if(value == prom.size()) {
        return value - 1;
    }
    else {
        return value - 1;
    }
}

Record Library::prompt_record() {
    string randDom;
    getline(cin, randDom);
    string sTitle;
    cout << "Enter the title: ";
    getline(cin, sTitle);
    string sAuth;
    cout << "Enter the Author: ";
    getline(cin, sAuth);
    string sI;
    cout << "Enter the ISBN: ";
    getline(cin, sI);
    string sYear;
    cout << "Enter the Year: ";
    getline(cin, sYear);
    string sEdi;
    cout << "Enter the Edition: ";
    getline(cin, sEdi);

    Record ret;
    ret.set_title(sTitle);
    ret.set_author(sAuth);
    ret.set_ISBN(sI);
    ret.set_year(sYear);
    ret.set_edition(sEdi);
    return ret;
}

string Library::prompt_title() {
    string title;
    cout << "Enter the title: ";
    getline(cin, title);
    return title;
}

string Library::prompt_string(string prompt) {
    cout << prompt << endl;
    string answer;
    getline(cin, answer);
    return answer;
}