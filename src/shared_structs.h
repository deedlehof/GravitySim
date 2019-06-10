#ifndef SHARED_STRUCTS_H
#define SHARED_STRUCTS_H

//CALCULATION
//universal gravitational constant
//const float GRAV_CONST = 6.674e-11;
//length of an astronomical unit in kilometers
//const unsigned long AU = 149.6e6;

//SIMULATION
//the number of updates per second
//const int UPDATES_PER_SEC = 20;
//how much time passes for each update
//const int TIMESTEP = 24 * 3600;
//how much the distances are scaled to fit on screen (arbitrary)
//const double PIXELS_PER_AU = 100;


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

struct NodeColor{
	unsigned short r, g, b;

	NodeColor(){
		r = 0;
		g = 0;
		b = 0;
	}

	NodeColor(unsigned short _r, unsigned short _g, unsigned short _b){
		if (_r > 255) 	_r %= 255;
		if (_g > 255) 	_g %= 255;
		if (_b > 255) 	_b %= 255;
		r = _r;
		g = _g;
		b = _b;
	}

	NodeColor operator+(const NodeColor &c2){
		NodeColor tmp;
		tmp.r = (r + c2.r) / 2;
		tmp.g = (g + c2.g) / 2;
		tmp.b = (b + c2.b) / 2;
		return tmp;
	}

	void operator=(const NodeColor &c2){
		r = c2.r;
		g = c2.g;
		b = c2.b;
	}
};

#endif
