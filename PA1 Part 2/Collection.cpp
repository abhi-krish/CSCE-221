#include "Stress_ball.h"
#include "Collection.h"
#include <iostream>
#include <string>
using namespace std;



Collection::Collection()	{
	this->array = nullptr;
	this->size = 0;
	this->capacity = 0;
}

Collection::Collection(int cap)	{
	this->array = new Stress_ball[cap];
	this->size = 0;
	this->capacity = cap;
}

void Collection::make_empty()	{
	delete [] this->array;
	array = nullptr;
	size = 0;
	capacity = 0;
}

Collection::~Collection()	{
	make_empty();
}

void Collection::resize()	{	
	if (this->capacity == 0)	{
		Stress_ball * temp = new Stress_ball[8];
		capacity = 8;
		array = move(temp);
		
	}
	else	{
		Stress_ball * temp = new Stress_ball[capacity*2];
		for (int i=0; i<size; i++)	{
			temp[i] = this->array[i];
			capacity *= 2;
		}
		array = move(temp);
	}
	
	
	
}


Collection::Collection(const Collection& c)	{
	this->array = new Stress_ball[c.capacity];
	for (int i=0; i<c.size; i++)	{
		this->array[i] = c.array[i];
	}
	this->size = c.size;
	this->capacity = c.capacity;
}

Collection::Collection(Collection && c)	{
	
	this->array = c.array;
	c.array = nullptr;
	this->size = c.size;
	this->capacity = c.capacity;
	c.size = 0;
	c.capacity = 0;
	
}

Collection& Collection::operator=(Collection && c)	{
	if (this != &c)	{
		this->array = c.array;
		c.array = nullptr;
		this->size = c.size;
		this->capacity = c.capacity;
		c.size = 0;
		c.capacity = 0;
	}
	return *this;
}

Collection& Collection::operator=(const Collection& c)	{
	if (this != &c)	{
		delete [] this->array;
		this->array = new Stress_ball[c.capacity];
		for (int i=0; i<c.size; i++)	{
			this->array[i] = c.array[i];
		}
		this->size = c.size;
		this->capacity = c.capacity;
	}
	return *this;
}


void Collection::insert_item(const Stress_ball& sb)	{ 
	if (size == capacity)	{
		resize();
	}
	this->array[size] = sb;
	size++;
}
bool Collection::contains(const Stress_ball& sb) const {
	for (int i=0; i<this->size; i++)	{
		if (array[i] == sb)	{
			return true;
		}
	}
	return false;
}

Stress_ball Collection::remove_any_item()	{
	if (is_empty())	{
		throw runtime_error("The array is empty.");
	}
	int random = rand()%size;
	Stress_ball holder = array[random];
	remove_this_item(array[random]);
	return holder;
}

void Collection::remove_this_item(const Stress_ball& sb)	{
	if (is_empty())	{
		throw runtime_error("The array is empty.");
	}
	for (int i=0;i<this->size;i++)	{
		if (array[i] == sb)	{
			for (int j=i;j<this->size-1;j++)	{
				array[j] = array[j+1]; 
			}
			size-=1;
		}

	}
}

bool Collection::is_empty() const	{
	if (this->array == nullptr)	{
		return true;
	}
	return false;
}
int Collection::total_items() const	{
	return size;
}
int Collection::total_items(Stress_ball_sizes s) const {
	int total = 0;
	for (int i=0; i<this->size; i++)	{
		if (s == (this->array[i]).get_size())	{
			total++;
		}
	}
	return total;
}
int Collection::total_items(Stress_ball_colors t) const {
	int total = 0;
	for (int i=0; i<this->size; i++)	{
		if (t == this->array[i].get_color())	{
			total++;
		}
	}
	return total;
}
void Collection::print_items() const {
	if (this->is_empty())	{
		cout << "The array is empt." << endl;
		
	}
	for (int i=0; i<this->size; i++)	{
		cout << this->array[i] << endl;
	}
}

Stress_ball& Collection::operator[](int i)	{
	if (i>=size)	{
		throw out_of_range("Out of range exception.");
	}
	return array[i];
}
	
const Stress_ball& Collection::operator[](int i)  const	{
	if (i>=size)	{
		throw out_of_range("Out of range exception.");
	}
	return array[i];
}


std::istream& operator>>(istream& is, Collection& c)	{
	string temp_col;
	string temp_sz;
	Stress_ball_colors color;
	Stress_ball_sizes size;
	is >> temp_col;
	is >> temp_sz;

	if (temp_sz == "small")	{
		size = Stress_ball_sizes::small;
	}
	else if (temp_sz == "medium")	{
		size = Stress_ball_sizes::medium;
	}
	else if (temp_sz == "large")	{
		size = Stress_ball_sizes::large;
	}
	if (temp_col == "red")	{
		color = Stress_ball_colors::red;
	}
	else if (temp_col == "blue")	{
		color = Stress_ball_colors::blue;
	}
	else if (temp_col == "yellow")	{
		color = Stress_ball_colors::yellow;
	}
	else if (temp_col == "green")	{
		color = Stress_ball_colors::green;
	}

	
	Stress_ball temp_ball(color, size);
	c.insert_item(temp_ball);
	return is;

}
ostream& operator <<(ostream& os, const Collection& c)	{
	for (int i=0; i<c.total_items(); i++)	{
		os << c[i] << endl;
	}
	return os;

}
Collection make_union(const Collection& c1, const Collection& c2)	{
	Collection temp(c1.total_items() + c2.total_items());
	for (int i=0; i<c1.total_items(); i++)	{
		temp.insert_item(c1[i]);
	}
	for (int i=0; i<c2.total_items(); i++)	{
		temp.insert_item(c2[i]);
	}

	return temp;

}
void swap(Collection& c1, Collection& c2)	{
	Collection temp(move(c1));
	c1 = move(c2);
	c2 = move(temp);
}
void sort_by_size(Collection& c, Sort_choice sort)	{
	if (c.total_items() <= 1)	{
		return;
	}
	int option = 0;
	switch(sort){
		case Sort_choice::bubble_sort	: 
			option = 1;
			break;
		case Sort_choice::insertion_sort: 
			option = 2;
			break;
		case Sort_choice::selection_sort: 
			option = 3;
			break;
	}
	if (option == 1)	{ 
		bool tell = false;
		for (int i=c.total_items()-1; i>0; i--)	{
			bool tell = false;
			for (int j=0; j<i; j++)	{
				
				if (c[j+1].get_size() < c[j].get_size())	{
					Stress_ball temp = Stress_ball(c[j+1]); 
					c[j+1]= c[j];
					c[j] = temp;
					tell = true;
				}
			}
			if (tell == false)	{
				return;
			}
		}
		return;
	}
	if (option == 2)	{
		Stress_ball temp;
		for (int i=1; i<c.total_items(); i++)	{
			for (int j=i; j>0; j--)	{
				if (c[j].get_size()<(c[j-1].get_size()))	{
					temp = c[j];
					c[j] = c[j-1];
					c[j-1] = temp;

				}
			}
		}
		return;
	}
	if (option == 3)	{
		int ind = 0;
		Stress_ball largest = c[0];
		Stress_ball temp;
		for (int i=c.total_items(); i>1; i--)	{
			largest = c[0];
			ind = 0;
			for (int j=0; j<i; j++)	{
				if (c[j].get_size()>largest.get_size())	{
					largest = c[j];
					ind = j;
				}
			}
			temp = c[i-1];
			c[i-1] = largest;
			c[ind] = temp;
		}
		return;
	}
}
