#include <cmath>
#include <iostream>
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

void Node::addForce(int objMass, Point objPos){
	int xDist, yDist;
	float xForce, yForce;

	xDist = objPos.x - position.x;
	yDist = objPos.x - position.x;

	//uses F = G * m1 * m2 / r^2
	xForce = GRAV_CONST * mass * objMass / pow(xDist, 2);
	yForce = GRAV_CONST * mass * objMass / pow(yDist, 2);

	//forces are given a sign for direction
	if (xDist < 0){
		xForce *= -1;
	}

	if (yDist < 0){
		yForce *= -1;
	}

	netForce.x += xForce;
	netForce.y += yForce;
}

void Node::updateVelocity(){
	//Vf = Ft / m + Vi
	velocity.x = netForce.x * (1 / UPDATES_PER_SEC) / mass + velocity.x;
	velocity.y = netForce.y * (1 / UPDATES_PER_SEC) / mass + velocity.y;
}

void Node::updatePosition(){
	//Xf = V*t + Xi
	position.x = velocity.x * (1 / UPDATES_PER_SEC) + position.x;
	position.y = velocity.y * (1 / UPDATES_PER_SEC) + position.y;
}

void Node::print(){
	cout << "POSITION" << endl;
	cout << "X: " << position.x << endl;
	cout << "Y: " << position.y << endl;
	cout << "MASS: " << mass << endl;
	cout << "VELOCITY" << endl;
	cout << "X: " << velocity.x << endl;
	cout << "Y: " << velocity.y << endl;
	cout << "FORCE" << endl;
	cout << "X: " << netForce.x << endl;
	cout << "Y: " << netForce.y << endl;
}
