#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
/*
 * Binary Heap class
 */
template <typename T>
class BinaryHeap {
    public:
        void insert(const T& data){
            //std::cout << data << std::endl;
            size++;
            elements.push_back(data);
            up_heap(size-1);

            // for (auto i :elements){
            //     std::cout << i << " ";
            // }
            // std::cout << std::endl;
        }
        bool is_empty(){
            return elements.size() == 0;
        }
        T min() {
            if (is_empty())
                throw 10;
            return elements[0];
        }
        T remove_min(){
            size--;
            T val = min();
            swap(0, elements.size() - 1);
            elements.pop_back();
            down_heap(0);

            // for (auto i :elements){
            //     std::cout << i << " ";
            // }
            // std::cout << std::endl;

            return val;
        }
    private:
        std::vector<T> elements; //{0};
        int size = 0;
        void down_heap(int i);
        void up_heap(int i);

        //Pre-implemented helper functions
        void swap(int a, int b) { T c(elements[a]); elements[a] = elements[b]; elements[b] = c;}
        int right_child(int i) {return 2*i + 2;}
        int left_child(int i) {return 2*i + 1;}
        int parent(int i) {return floor((i-1)/2);}
        bool is_internal(int i) {return left_child(i) < size || right_child(i) < size;}
        bool is_leaf(int i) {return left_child(i) >= size && right_child(i) >= size;}
};

/*
 * Restores the binary heap property starting from a node that is smaller than its parent
 * O(log n)
 */
template <typename T>
void BinaryHeap<T>::up_heap(int i){
    int parent_index = parent(i);
    /*
     * Can be computed iteratively or recursively
     */
    if (parent_index >= 0 && i > 0){
        if (elements[i] < elements[parent_index])
            swap(i, parent_index);
        up_heap(parent_index);
    }
}

/*
 * Restores the binary heap property starting from an node that is larger than its children
 * O(log n)
 */
template <typename T>
void BinaryHeap<T>::down_heap(int i){
    int right_index = right_child(i);
    int left_index = left_child(i);
    /*
     * Can be computed iteratively or recursively
     */

    if (left_index < size &&  elements[left_index] < elements[i] ){
        // cout << "i " << i << ":"<<elements[i] << 
        //     " left_index " << left_index << ":" << elements[left_index] << endl; 
        swap(i, left_index);
        down_heap(left_index);

    }

    if (right_index < size &&  elements[right_index] < elements[i] ){
        // cout << "i " << i << ":"<<elements[i] << 
        // " right_index " << right_index << ":" << elements[right_index] << endl;
        swap(i, right_index);
        down_heap(right_index);
    }



}
#endif