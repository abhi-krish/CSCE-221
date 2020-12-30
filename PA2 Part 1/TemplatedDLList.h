// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H
#include <iostream>
#include <stdexcept>
using namespace std;


template <typename T>
class DLList;

template <typename T>
struct DLListNode {
    T obj;
    DLListNode<T>* prev, * next;
    DLListNode(T e = T(), DLListNode* p = nullptr, DLListNode* n = nullptr) : obj(e), prev(p), next(n) {}
};

template <typename T>
class DLList {
private:

    DLListNode<T> header, trailer;

public:

    DLList() {
        header.next = &trailer;
        trailer.prev = &header;
    }
    DLList(const DLList<T>& dll) {
        header.next = &trailer;
        trailer.prev = &header;
        DLListNode<T>* iter2 = dll.header.next;
        while (iter2->next != nullptr) {
            insert_last(iter2->obj);
            iter2 = iter2->next;
        }
    }
    DLList(DLList<T>&& dll) {
        if (dll.is_empty() == true) {
            header.next = &trailer;
            trailer.prev = &header;
        }
        else {
            this->header.next = dll.header.next;
            this->trailer.prev = dll.trailer.prev;
            dll.header.next->prev = &this->header;
            dll.trailer.prev->next = &this->trailer;
            dll.header.next = &dll.trailer;
            dll.trailer.prev = &dll.header;
        }
    }
    ~DLList() {
        DLListNode<T>* iter = header.next;
        DLListNode<T>* holding = iter;
        while (iter->next != nullptr) {
            delete holding;
            iter = iter->next;
            holding = iter;
        }
    }
    DLList<T>& operator=(const DLList<T>& dll) {
        if (this != &dll) {
            DLListNode<T>* iter = header.next;
            DLListNode<T>* holding = iter;
            while (iter->next != nullptr) {
                delete holding;
                iter = iter->next;
                holding = iter;
            }
            header.next = &trailer;
            trailer.prev = &header;
            DLListNode<T>* iter2 = dll.header.next;
            while (iter2->next != nullptr) {
                insert_last(iter2->obj);
                iter2 = iter2->next;
            }
        }
        return *this;
    }
    DLList<T>& operator=(DLList<T>&& dll) {
        if (this != &dll) {
            DLListNode<T>* iter = header.next;
            DLListNode<T>* holding = iter;
            while (iter->next != nullptr) {
                delete holding;
                iter = iter->next;
                holding = iter;
            }
            DLListNode<T>* iter2 = dll.header.next;
            while (iter2->next != nullptr) {
                insert_last(iter2->obj);
                iter2 = iter2->next;
            }
        }
        return *this;
    }
    DLListNode<T>* first_node() const { return header.next; }
    const DLListNode<T>* after_last_node() const { return &trailer; }
    bool is_empty() const { return header.next == &trailer; }
    T first() const {
        return header.next->obj;
    }
    T last() const {
        return trailer.prev->obj;
    }
    void insert_first(T obj) {
        if (header.next == &trailer) {
            DLListNode<T>* newNode = new DLListNode<T>(obj, &header, &trailer);
            header.next = newNode;
            trailer.prev = newNode;
        }
        else {
            DLListNode<T>* newNode = new DLListNode<T>(obj, &header, header.next);
            DLListNode<T>* holding = header.next;
            holding->prev = newNode;
            header.next = newNode;
        }
    }
    T remove_first() {
        if (header.next != &trailer) {
            T firstObj;
            DLListNode<T>* holding = header.next;
            header.next = holding->next;
            holding->next->prev = &header;
            firstObj = holding->obj;
            delete holding;
            return firstObj;
        }
        else {
            throw("List empty");
        }
    }
    void insert_last(T obj) {
        if (header.next == &trailer) {
            DLListNode<T>* newNode = new DLListNode<T>(obj, &header, &trailer);
            header.next = newNode;
            trailer.prev = newNode;
        }
        else {
            DLListNode<T>* holding1 = trailer.prev;
            DLListNode<T>* newNode = new DLListNode<T>(obj, holding1, &trailer);
            holding1->next = newNode;
            trailer.prev = newNode;
        }
    }
    T remove_last() {
        if (header.next != &trailer) {
            DLListNode<T>* holding = trailer.prev->prev;
            T val = trailer.prev->obj;
            delete trailer.prev;
            trailer.prev = holding;
            holding->next = &trailer;
            return val;
        }
        else {
            throw("List empty");
        }
    }
    void insert_after(DLListNode<T>& p, T obj) {
        bool found = false;
        DLListNode<T>* toAdd = new DLListNode<T>(obj, nullptr, nullptr);
        DLListNode<T>* iter = &header;
        DLListNode<T>* holding1;
        DLListNode<T>* holding2;
        while (iter->next != nullptr) {
            if (iter->obj == p.obj) {
                holding1 = iter;
                holding2 = iter->next;
                holding1->next = toAdd;
                holding2->prev = toAdd;
                toAdd->next = holding2;
                toAdd->prev = holding1;
                found = true;
                break;
            }
            iter = iter->next;
        }
        if (!found) {
            throw("Item not found");
        }
    }

    void insert_before(DLListNode<T>& p, T obj) {
        bool found = false;
        DLListNode<T>* toAdd = new DLListNode<T>(obj, nullptr, nullptr);
        DLListNode<T>* iter = &header;
        DLListNode<T>* holding1;
        DLListNode<T>* holding2;
        while (iter->next != nullptr) {
            if (iter->obj == p.obj) {
                holding1 = iter->prev;
                holding2 = iter;
                holding1->next = toAdd;
                holding2->prev = toAdd;
                toAdd->next = holding2;
                toAdd->prev = holding1;
                found = true;
                break;
            }
            iter = iter->next;
        }
        if (!found) {
            throw("Item not found");
        }
    }
    T remove_after(DLListNode<T>& p) {
        bool found = false;
        T objRemove;
        DLListNode<T>* iter = &header;
        DLListNode<T>* holding1;
        DLListNode<T>* toRemove;
        DLListNode<T>* holding2;
        if (header.next == &trailer) {
            throw("Invalid item to remove");
        }
        while (iter->next != nullptr) {
            if (iter->obj == p.obj) {
                found = true;
                toRemove = iter->next;
                if (toRemove == &trailer) {
                    throw("Invalid item to remove");
                    break;
                }
                holding1 = toRemove->prev;
                holding2 = toRemove->next;
                holding1->next = holding2;
                holding2->prev = holding1;
                objRemove = toRemove->obj;
                delete toRemove;
                return objRemove;
                break;
            }
            iter = iter->next;
        }
        if (!found) {
            throw("Item not found");
        }
    }

    T remove_before(DLListNode<T>& p) {
        bool found = false;
        DLListNode<T>* iter = &header;
        T objRemove;
        DLListNode<T>* holding1;
        DLListNode<T>* toRemove;
        DLListNode<T>* holding2;
        if (iter->next == &trailer) {
            throw("Invalid item to remove");
        }
        while (iter->next != nullptr) {
            if (iter->obj == p.obj) {
                toRemove = iter->prev;
                if (toRemove == &header) {
                    throw("Invalid item to remove");
                    break;
                }
                holding1 = toRemove->prev;
                holding2 = toRemove->next;
                holding1->next = holding2;
                holding2->prev = holding1;
                objRemove = toRemove->obj;
                delete toRemove;
                return objRemove;
                break;
            }
            iter = iter->next;
        }
        if (!found) {
            throw("Item not found");
        }
        return -1;
    }
};


template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll) {
    DLListNode<T>* iter = dll.first_node();
    while (iter->next != nullptr) {
        out << iter->obj << ", ";
        iter = iter->next;
    }
    return out;
}

#endif