#include "node.h"

using namespace std;

Node::Node(Point _pos, int _mass, Vector2 _vel){
	position = _pos;
	mass = _mass;
	velocity = _vel;
}

int Node::getX(){
	return position.x;
}

int Node::getY(){
	return position.y;
}

Point Node::getPos(){
	return position;
}

int Node::getMass(){
	return mass;
}

Vector2 Node::getVelocity(){
	return velocity;
}



