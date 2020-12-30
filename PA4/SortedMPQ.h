#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include "MPQ.h"
using namespace std;
/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ: MPQ<T> {

	list<T> l;
    
    public:
    
    T remove_min(){
    	T value = min();
		l.pop_front();
		return value;
    }
    T min(){
    	if (is_empty())
    		throw 20;
    	return l.front();
    }
    bool is_empty(){
    	return l.size() == 0;
    }
    void insert(const T& data){
        l.insert(lower_bound(l.begin(), l.end(), data), data);
    }
    
};

#endif