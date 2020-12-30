#include <iostream>
#include "Jeans.h"

Jeans::Jeans()	{
    color = Jeans_colors(rand() % 4);
    size = Jeans_sizes(rand() % 4);
}
Jeans::Jeans(Jeans_colors col, Jeans_sizes siz)	{
	color = col;
	size = siz;
}
Jeans_colors Jeans::get_color()	const{
	return color;
}
Jeans_sizes Jeans::get_size() const	{
	return size;
}

bool Jeans::operator==(const Jeans& sb)	{ 
	if (get_color()==sb.get_color() && get_size() == sb.get_size())	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Jeans& sb) {
	
	if (sb.get_color() == Jeans_colors(0))
		os << "(white, ";
	else if (sb.get_color() == Jeans_colors(1))
		os << "(black, ";
	else if (sb.get_color() == Jeans_colors(2))
		os << "(blue, ";
	else
		os << "(grey, ";
	if (sb.get_size() == Jeans_sizes(0))
		os << "small)";
	else if (sb.get_size() == Jeans_sizes(1))
	    os << "medium)";
	else if (sb.get_size() == Jeans_sizes(2))
		os << "large)";
    else {
        os << "xlarge)";
    }
	return os;
}
