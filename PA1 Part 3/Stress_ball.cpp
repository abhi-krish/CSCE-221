#include <iostream>
#include "Stress_ball.h"

Stress_ball::Stress_ball()	{
    color = Stress_ball_colors(rand() % 4);
    size = Stress_ball_sizes(rand() % 3);
}
Stress_ball::Stress_ball(Stress_ball_colors col, Stress_ball_sizes siz)	{
	color = col;
	size = siz;
}
Stress_ball_colors Stress_ball::get_color()	const{
	return color;
}
Stress_ball_sizes Stress_ball::get_size() const	{
	return size;
}

bool Stress_ball::operator==(const Stress_ball& sb)	{ 
	if (get_color()==sb.get_color() && get_size() == sb.get_size())	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Stress_ball& sb) {
	
	if (sb.get_color() == Stress_ball_colors(0))
		os << "(red, ";
	else if (sb.get_color() == Stress_ball_colors(1))
		os << "(blue, ";
	else if (sb.get_color() == Stress_ball_colors(2))
		os << "(green, ";
	else
		os << "(yellow, ";
	if (sb.get_size() == Stress_ball_sizes(0))
		os << "small)";
	else if (sb.get_size() == Stress_ball_sizes(1))
	    os << "medium)";
	else if (sb.get_size() == Stress_ball_sizes(2))
		os << "large)";
	return os;
}

