#ifndef MPQ_H
#define MPQ_H

//Abstract Minimum Priority Queue Class
template<typename T>
class MPQ{
public:
    virtual T remove_min() = 0;
    virtual T min() = 0;
    virtual bool is_empty() = 0;
    virtual void insert(const T& data) = 0;
};
#endif