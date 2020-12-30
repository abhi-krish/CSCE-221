#ifndef Collection_H
#define Collection_H
#include <string>
#include <iostream>
using namespace std;

enum class Sort_choice{bubble_sort, insertion_sort, selection_sort};
template<typename obj, typename F1, typename F2>
class Collection {

private:
    obj* array;
    int size;
    int capacity;

    void resize() {
        capacity = 2 * capacity;
        if (capacity == 0) {
        capacity = 2;
        }
        obj* temp = new obj[capacity];
        for (int i = 0; i < size; i++)
            temp[i] = array[i];
        delete[] array;
        array = temp;
    }
public:
    Collection() {
        array = nullptr;
        size = 0;
        capacity = 0;
    }

    Collection(int cap) {
        size = 0;
        capacity = cap;
        array = new obj[capacity];
    }

    Collection(const Collection& c) {
        size = c.size;
        capacity = c.capacity;
        array = new obj[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = c.array[i];
        }
    }

    Collection& operator=(const Collection& c) {
        if (this != &c) {
            if (array != nullptr) {
                delete[] array;
            }
            size = c.size;
            capacity = c.capacity;
            array = new obj[capacity];
            for (int i = 0; i < size; i++) {
                array[i] = c.array[i];
            }
        }
        return *this;
    }
    ~Collection() {
        make_empty();
    }

    Collection(Collection&& c) {
        size = c.size;
        capacity = c.capacity;
        array = c.array;

        c.array = nullptr;
        c.size = 0;
        c.capacity = 0;
    }

    Collection& operator=(Collection&& c) {
        if (this != &c) {
            if (array != nullptr) {
                delete[] array;
            }
            size = c.size;
            capacity = c.capacity;
            array = c.array;
        }
        c.capacity = 0;
        c.size = 0;
        c.array = nullptr;
        return *this;
    }

    void insert_item(const obj& sb) {
        if (size == capacity) {
            resize();
        }
        array[size] = sb;
        size++;
    }

    bool contains(const obj& sb) const {
        for (int i = 0; i < size; i++) {
            if (array[i] == sb) {
                return true;
            }
        }
        return false;
    }

    obj remove_any_item() {
        if (size == 0) {
			throw "collection empty";
		}
        int index = rand() % size;
        obj sb = array[index];
        for (int i = index + 1; i < size; i++){
			array[i - 1] = array[i];
		}
        size--;
        return sb;
    }

    void remove_this_item(const obj& sb) {
        if (size == 0)
            throw "Collection is empty";
        int index = 0;
        if (contains(sb)) {
            for (int i = index; i < size; i++) {
                if (array[i] == sb) {
                    index = i;
                    break;
                }
                for (int i = index + 1; i < size; i++)
                    array[i - 1] = array[i];
            }
            size--;
        }

    }

    void make_empty() {
        if (array != nullptr) {
            delete[] array;
            size = 0;
            capacity = 0;
        }
    }

    bool is_empty() const {
        if (size == 0) {
            return true;
		}
        return false;
    }

    int total_items() const {
        return size;
    }

    int total_items(F2 s) const {
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (array[i].get_size() == s)
                counter++;
        }
        return counter;
    }
    int total_items(F1 c) const {
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (array[i].get_color() == c)
                counter++;
        }
        return counter;
    }
    void print_items() const {
        for (int i = 0; i < size; i++) {
            cout << array[i] << endl;
        }
    }

    obj& operator[](int i) {
        return array[i];
    }
    const obj& operator[](int i) const {
        return array[i];
    }
};

template<typename obj, typename F1, typename F2>
ostream& operator<<(ostream& os, const Collection<obj, F1, F2>& c) {
    for (int i = 0; i < c.total_items(); i++) {
        os << c[i] << endl;
    }
    return os;
}

template<typename obj, typename F1, typename F2>
Collection<obj, F1, F2> make_union(const Collection<obj, F1, F2>& c1, const Collection<obj, F1, F2>& c2) {
    Collection<obj, F1, F2> c3;
    for (int i = 0; i < c1.total_items(); i++) {
        c3.insert_item(c1[i]);
    }
    for (int i = 0; i < c2.total_items(); i++) {
        c3.insert_item(c2[i]);
    }
    return c3;
}

template<typename obj, typename F1, typename F2>
void swap(Collection<obj, F1, F2>& c1, Collection<obj, F1, F2>& c2) {

    Collection<obj, F1, F2> temp(c1);

    c1 = Collection<obj, F1, F2>(c2);
    c2 = Collection<obj, F1, F2>(temp);

}

template<typename obj, typename F1, typename F2>
void sort_by_size(Collection<obj, F1, F2>& c, Sort_choice sort) {
    switch (sort)
    {
    case Sort_choice::bubble_sort: {
        bool flag = false;
        while (!flag) {

            flag = true;

            for (int i = 0; i < (c.total_items() - 1); i++) {

                int sz1 = 0;
                int sz2 = 0;

                if (c[i].get_size() == F2(0)) {
                    sz1 = 0;
                }
                else if (c[i].get_size() == F2(1)) {
                    sz1 = 1;
                }
                else {
                    sz1 = 2;
                }

                if (c[i + 1].get_size() == F2(0)) {
                    sz2 = 0;
                }
                else if (c[i + 1].get_size() == F2(1)) {
                    sz2 = 1;
                }
                else {
                    sz2 = 2;
                }

                if (sz2 < sz1) {
                    obj placeholding = c[i + 1];

                    c[i + 1] = c[i];
                    c[i] = placeholding;
                    flag = false;

                }

            }

        }
        break;
    }

    case Sort_choice::insertion_sort: {
        for (int i = 1; i < c.total_items(); i++) {
            int szinsert;
            int sz1;
            int sz2;

            if (c[i].get_size() == F2(0)) {
                szinsert = 0;
            }
            else if (c[i].get_size() == F2(1)) {
                szinsert = 1;
            }
            else {
                szinsert = 2;
            }
            for (int j = 0; j < (c.total_items() - 1); j++) {
                if (c[j].get_size() == F2(0)) {
                    sz1 = 0;
                }
                else if (c[j].get_size() == F2(1)) {
                    sz1 = 1;
                }
                else {
                    sz1 = 2;
                }

                if (c[j + 1].get_size() == F2(0)) {
                    sz2 = 0;
                }

                else if (c[j + 1].get_size() == F2(1)) {
                    sz2 = 1;
                }

                else {
                    sz2 = 2;
                }
                if (j == 0 && szinsert < sz1) {
                    obj hold = c[i];
                    for (int k = c.total_items(); j < k; k--)
                        c[k] = c[k - 1];
                    c[0] = hold;
                    break;
                }
                else if (sz1 <= szinsert && szinsert < sz2) {
                    obj temp = c[i];

                    for (int k = i; j < k; k--)
                        c[k] = c[k - 1];

                    c[j + 1] = temp;
                    break;
                }
            }
        }
        break;
    }

    case Sort_choice::selection_sort:
        int sz1, sz2;
        for (int i = 0; i < c.total_items(); i++) {
            if (c[i].get_size() == F2(0)) {
                sz1 = 0;
            }


            else if (c[i].get_size() == F2(1)) {
                sz1 = 1;
            }

            else {
                sz1 = 2;
            }

            int minimumsize = sz1;

            int minimumidex = i;

            for (int j = i; j < c.total_items(); j++) {
                if (c[j].get_size() == F2(0)) {
                    sz2 = 0;
                }
                else if (c[j].get_size() == F2(1)) {
                    sz2 = 1;
                }
                else {
                    sz2 = 2;
                }
                if (sz2 < minimumsize) {
                    minimumsize = sz2;
                    minimumidex = j;
                }
            }
            obj temporary = c[i];
            c[i] = c[minimumidex];
            c[minimumidex] = temporary;
        }
        break;
    }
}
#endif