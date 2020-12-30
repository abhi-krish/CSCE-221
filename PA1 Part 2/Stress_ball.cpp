#include <iostream>
#include "Stress_ball.h"

Stress_ball::Stress_ball()	{
	this->color = Stress_ball_colors(rand()%4);
	this->size = Stress_ball_sizes(rand()%3);
}

Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)	{
	this->color = c;
	this->size = s;
}

Stress_ball_colors Stress_ball::get_color()	const{
	return this->color;
}

Stress_ball_sizes Stress_ball::get_size() const	{
	return this->size;
}

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb)	{

	o << "(";


	switch(sb.get_color())	{
		case Stress_ball_colors::red	: o << "red";
			break;
		case Stress_ball_colors::blue	: o << "blue";
			break;
		case Stress_ball_colors::yellow	: o << "yellow";
			break;
		case Stress_ball_colors::green	: o << "green";
	}

	o << ", ";


	switch(sb.get_size())	{
		case Stress_ball_sizes::small	: o << "small";
			break;
		case Stress_ball_sizes::medium	: o << "medium";
			break;
		case Stress_ball_sizes::large	: o << "large";
	}

	o << ")";

	return o;
}

bool Stress_ball::operator==(const Stress_ball& sb)	{ 
	if ((this->get_color()==sb.get_color()) && (this->get_size() == sb.get_size()))	{
		return true;
	}
	return false;
}


