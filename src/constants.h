#ifndef CONSTANTS_H
#define CONSTANTS_H

//CALCULATION
//universal gravitational constant
const float GRAV_CONST = 6.674e-11;
//length of an astronomical unit in kilometers
const unsigned long AU = 149.6e6;
//mass scaling factor
const int MASS_SCALE_POW = 20;

//SIMULATION
//the number of updates per second
const int UPDATES_PER_SEC = 20;
//how much time passes for each update
const int TIMESTEP = 24 * 3600;
//how much the distances are scaled to fit on screen (arbitrary)
const double PIXELS_PER_AU = 100;


//SHARED STRUCTURES
struct Point{
	int x, y;

	Point(int _x, int _y){
		x = _x;
		y = _y;
	}

	Point(){
		x = y = 0;
	}

	bool operator==(const Point& rhs){
		return ((this->x == rhs.x) && (this->y == rhs.y));
	}
	bool operator!=(const Point& rhs){
		return ((this->x != rhs.x) || (this->y != rhs.y));
	}
};

struct Vector2{
	double x, y;

	Vector2(double _x, double _y){
		x = _x;
		y = _y;
	}

	Vector2(){
		x = y = 0.0;
	}

	bool operator==(const Vector2& rhs){
		return ((this->x == rhs.x) && (this->y == rhs.y));
	}

	bool operator!=(const Vector2& rhs){
		return ((this->x != rhs.x) || (this->y != rhs.y));
	}
};

#endif
