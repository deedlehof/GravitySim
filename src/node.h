#ifndef NODE_H
#define NODE_H

using namespace std;

//const float GRAV_CONST = 6.674e-11;
const float GRAV_CONST = 6e-10;
const int UPDATES_PER_SEC = 10;
const int TIMESTEP = 24 * 3600;

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

	friend class Quad;

	public:
		Node(int _id, Vector2 _pos, float _mass, Vector2 _vel);
		int getID();
		double getX();
		double getY();
		float getRadius();
		Vector2 getPos();
		float getMass();
		Vector2 getVelocity();
		void addForce(float objMass, Vector2 objPos);
		bool attemptCollide(Node *collision);
		void resetForce();
		void updatePosition();
		void updateVelocity();
		void print();


	private:
		Vector2 position;
		float mass;
		Vector2 velocity;
		Vector2 netForce;
		int id;
};


#endif
