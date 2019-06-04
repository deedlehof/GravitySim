#ifndef NODE_H
#define NODE_H

using namespace std;

const float GRAV_CONST = 1.0;
const int UPDATES_PER_SEC = 1;

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
	float x, y;

	Vector2(float _x, float _y){
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

class Node{
	public:
		Node(Point _pos, int _mass, Vector2 _vel);
		int getX();
		int getY();
		Point getPos();
		int getMass();
		Vector2 getVelocity();
		void addForce(int objMass, Point objPos);
		void resetForce();
		void updatePosition();
		void updateVelocity();
		void print();

	private:
		Point position;
		int mass;
		Vector2 velocity;
		Vector2 netForce;
};


#endif
