#ifndef NODE_H
#define NODE_H

using namespace std;

struct Point{
	int x, y;

	Point(int _x, int _y){
		x = _x;
		y = _y;
	}

	Point(){
		x = y = 0;
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
};

class Node{
	public:
		Node(Point _pos, int _mass, Vector2 _vel);
		int getX();
		int getY();
		Point getPos();
		int getMass();
		Vector2 getVelocity();

	private:
		Point position;
		int mass;
		Vector2 velocity;

};


#endif
