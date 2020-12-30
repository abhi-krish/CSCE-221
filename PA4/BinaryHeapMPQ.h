#ifndef BINARYHEAP_MPQ_H
#define BINARYHEAP_MPQ_H

#include "BinaryHeap.h"
#include <stdexcept>
#include "MPQ.h"

/*
 * Minimum Priority Queue based on a binary heap
 */
template <typename T>
class BinaryHeapMPQ: MPQ<T> {
	BinaryHeap<T> b;
    
    public:
    
    T remove_min(){
    	return b.remove_min();
    }
    T min(){
    	if (is_empty())
    		throw 10;
    	return b.min();
    }
    bool is_empty(){
    	return b.is_empty();
    }
    void insert(const T& data){
    	b.insert(data);
    }

    
};

#endif