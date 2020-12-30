#ifndef UNSORTEDMPQ_H
#define UNSORTEDMPQ_H

#include <stdexcept>
#include <vector>
#include <algorithm>
#include "MPQ.h"
using namespace std;

/*
 * Minimum Priority Queue based on a vector
 */
template <typename T>
class UnsortedMPQ: MPQ<T> {
   	vector<T> v;
    
    public:
    
    T remove_min(){
    	T value = min();
		auto it = find(v.begin(), v.end(), value);
		if (it != v.end()) {
		  v.erase(it);
		}
		return value;
    }
    T min(){
    	if (is_empty())
    		throw 10;
    	return *min_element(v.begin(), v.end());
    }
    bool is_empty(){
    	return v.size() == 0;
    }
    void insert(const T& data){
    	v.push_back(data);
    }
};

#endif