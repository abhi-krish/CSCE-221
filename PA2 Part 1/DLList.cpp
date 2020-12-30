// implementation of the DLList class
#include "DLList.h"

DLList::DLList() {
  header.next = &trailer;
  trailer.prev = &header;
}

DLList::DLList(const DLList& dll) {

  header.next = &trailer;
  trailer.prev = &header;
  DLListNode* iter2 = dll.header.next;
  while (iter2->next != nullptr) {
    insert_last(iter2->obj);
    iter2 = iter2->next;
  }
}
DLList::DLList(DLList&& dll) {
  if(dll.is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
  } else {
    this->header.next = dll.header.next;
    this->trailer.prev = dll.trailer.prev;
    dll.header.next->prev = &this->header;
    dll.trailer.prev->next = &this->trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
}

DLList::~DLList() {
  if(header.next == nullptr || header.next == &trailer) {
    header.next = &trailer;
    trailer.prev = &header;
  } 
  else {
    DLListNode* iter = header.next;
    DLListNode* holding = iter;
    while(iter->next != nullptr) {
        iter = iter->next;
        delete holding;
        holding = iter;
    }
    header.next = &trailer;
    trailer.prev = &header;
  }
}

DLList& DLList::operator=(const DLList& dll) {
  if (this != &dll) {
    DLListNode* iter = header.next;
    DLListNode* hold = iter;
    while(iter->next != nullptr) {
        delete hold;
        iter = iter->next;
        hold = iter;
    }
    header.next = &trailer;
    trailer.prev = &header;
    DLListNode* iter2 = dll.header.next;
    while (iter2->next != nullptr) {
      insert_last(iter2->obj);
      iter2 = iter2->next;
    }
  }
  return *this;
}

DLList& DLList::operator=(DLList&& dll) {
  if (this != &dll) {
    dll.~DLList();
    header.next = dll.header.next;
    trailer.prev = dll.trailer.prev;
    dll.header.next->prev = &header;
    dll.trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
  return *this;
}

DLListNode* DLList::first_node() const {
    return header.next;
}

const DLListNode* DLList::after_last_node() const {
  return &trailer;
}

bool DLList::is_empty() const {
  if (header.next == &trailer) {
    return true;
  } else {
    return false;
  }
}

int DLList::first() const {
  return header.next->obj;
}

int DLList::last() const {
  return trailer.prev->obj;
}

void DLList::insert_first(int obj) {
  if (header.next == &trailer) {
    DLListNode* node = new DLListNode(obj, &header, &trailer);
    header.next = node;
    trailer.prev = node;
  } 
  else {
    DLListNode* node = new DLListNode(obj, &header, header.next);
    DLListNode* holder  = header.next;
    holder->prev = node;
    header.next = node;
  }
}

int DLList::remove_first() {
  if (header.next != &trailer) {
    int fObj;
    DLListNode* holder = header.next;
    header.next = holder->next;
    holder->next->prev = &header;
    fObj = holder->obj;
    delete holder;
    return fObj;
  } 
  else {
    throw("Empty");
  }
}

void DLList::insert_last(int obj) {
    if (header.next == &trailer) {
      DLListNode* node = new DLListNode(obj, &header, &trailer);
      header.next = node;
      trailer.prev = node;
    } else {
      DLListNode* holder = trailer.prev;
      DLListNode* node = new DLListNode(obj, holder, &trailer);
      holder->next = node;
      trailer.prev = node;
    }
  }
int DLList::remove_last() {
  if (header.next != &trailer) {
    DLListNode* holder = trailer.prev->prev;
    int val = trailer.prev->obj;
    delete trailer.prev;
    trailer.prev = holder;
    holder->next = &trailer;
    return val;
  } 
  else {
    throw("Nothing to remove");
  }
}

void DLList::insert_after(DLListNode &p, int obj) {
  DLListNode* add = new DLListNode(obj, nullptr, nullptr);
  DLListNode* iter = &header;
  DLListNode* hold1;
  DLListNode* hold2;
  while(iter->next != nullptr) {
    if  (iter->obj == p.obj) {
      hold1 = iter;
      hold2 = iter->next;
      hold1->next = add;
      hold2->prev = add;
      add->next = hold2;
      add->prev = hold1;
      break;
    }
    iter = iter->next;
  }
}

void DLList::insert_before(DLListNode &p, int obj) {
  DLListNode* add = new DLListNode(obj, nullptr, nullptr);
  DLListNode* iter = &header;
  DLListNode* hold1;
  DLListNode* hold2;
  while(iter->next != nullptr) {
    if  (iter->obj == p.obj) {
      hold1 = iter->prev;
      hold2 = iter;
      hold1->next = add;
      hold2->prev = add;
      add->next = hold2;
      add->prev = hold1;
      break;
    }
    iter = iter->next;
  }
}

int DLList::remove_after(DLListNode &p) {
  int objRemove;
  DLListNode* iter = header.next;
  DLListNode* hold1;
  DLListNode* remove;
  DLListNode* hold2;
  if (header.next == &trailer) {
    throw("No object to remove");
  }
  while(iter->next != nullptr) {
    if  (iter->obj == p.obj) {
      if (iter->next == &trailer) {
        throw("Cannot remove trailer");
        break;
      }
      remove = iter->next;
      hold1 = remove->prev;
      hold2 = remove->next;
      hold1->next = hold2;
      hold2->prev = hold1;
      objRemove = remove->obj;
      delete remove;
      return objRemove;
      break;
    }
    iter = iter->next;
  }
  throw("Object not found");
  return -1;
}
int DLList::remove_before(DLListNode &p) {
  DLListNode* iter = header.next;
  int objRemove;
  DLListNode* hold1;
  DLListNode* remove;
  DLListNode* hold2;
  if (header.next == &trailer) {
    throw("No object to remove");
  }
  while(iter->next != nullptr) {
    if  (iter->obj == p.obj) {
      if (iter->next == &trailer) {
        throw("Cannot remove trailer");
        break;
      }
      remove = iter->prev;
      hold1 = remove->prev;
      hold2 = remove->next;
      hold1->next = hold2;
      hold2->prev = hold1;
      objRemove = remove->obj;
      delete remove;
      return objRemove;
      break;
    }
    iter = iter->next;
  }
  return -1;
}


ostream& operator<<(ostream& out, const DLList& dll) {
  DLListNode *iter = dll.first_node();
  while(iter->next != nullptr) {
    out << iter->obj << ", ";
    iter = iter->next;
  }
  return out;
}