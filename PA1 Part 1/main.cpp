#include <iostream>

using std::string;
using namespace std;

enum class Stress_ball_colors {red, blue, yellow, green};
enum class Stress_ball_sizes {small, medium, large};

class Stress_ball {

    private:
    Stress_ball_colors color;
    Stress_ball_sizes size;

    public: 

    Stress_ball() {
        color = Stress_ball_colors(rand() % 4);
        size = Stress_ball_sizes(rand() % 3);
    }

    Stress_ball(Stress_ball_colors c, Stress_ball_sizes s):color(c), size(s) {
        
    };

    Stress_ball_colors get_color() {
        return color;
    }

    Stress_ball_sizes get_size() {
        return size;
    }

    bool operator==(Stress_ball& stress_ball) {
        if(this->color == stress_ball.get_color() && this->size == stress_ball.get_size()) {
            return true;
        }
        else {
            return false;
        }
    }

};


 string change_size(Stress_ball_sizes s) {
    switch(s) {
        case Stress_ball_sizes::small: 
            return "small";
            break;
        case Stress_ball_sizes::medium: 
            return "medium";
            break;
        case Stress_ball_sizes::large: 
            return "large";
            break;
    }
}

string change_color(Stress_ball_colors c) {
    switch(c) {
        case Stress_ball_colors::red: 
            return "red";
            break;
        case Stress_ball_colors::blue: 
            return "blue";
            break;
        case Stress_ball_colors::yellow: 
            return "yellow";
            break;
        case Stress_ball_colors::green: 
            return "green";
            break;
    }
}



std::ostream& operator<<(std::ostream& os, Stress_ball& stress_ball) {
    os << change_color(stress_ball.get_color()) << "," << change_size(stress_ball.get_size());
    return os;
}

