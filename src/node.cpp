#include <cmath>
#include <iostream>
#include "node.h"

using namespace std;

Node::Node(int _id, Vector2 _pos, float _mass, Vector2 _vel){
	id = _id;
	position = _pos;
	mass = _mass;
	velocity = _vel;
}

Node::Node(int _id, Vector2 _pos, float _mass, Vector2 _vel, NodeColor _nColor){
	id = _id;
	position = _pos;
	mass = _mass;
	velocity = _vel;
	nColor = _nColor;
}

int Node::getID(){
	return id;
}

double Node::getX(){
	return position.x;
}

double Node::getY(){
	return position.y;
}

Vector2 Node::getPos(){
	return position;
}

//TODO FIX
float Node::getRadius(){
	return 5;
}

float Node::getMass(){
	return mass;
}

Vector2 Node::getVelocity(){
	return velocity;
}

NodeColor Node::getColor(){
	return nColor;
}

bool Node::attemptCollide(Node *collision){
	//distances in AU
	float xDist = position.x - collision->getX();
	float yDist = position.y - collision->getY();
	float distanceSquared = xDist * xDist + yDist * yDist;
	float threshold = pow(getRadius() + collision->getRadius(), 2);

	//test if the distance between the nodes
	//is greater than the distance if they were touching
	if (distanceSquared > threshold){
		return false;
	}

	//the points are touching, collide them
	float colliderMass = collision->getMass();
	float totalMass = mass + colliderMass;

	velocity.x = (velocity.x * mass + collision->getVelocity().x * colliderMass) / totalMass;
	velocity.y = (velocity.y * mass + collision->getVelocity().y * colliderMass) / totalMass;

	mass = totalMass;

	nColor = nColor + collision->getColor();

	return true;
}

void Node::addForce(float objMass, Vector2 objPos){
	double xDist, yDist;
	double xForce, yForce;

	xDist = objPos.x - position.x;
	yDist = objPos.y - position.y;

	float distSquared = xDist * xDist + yDist * yDist;

	if (distSquared == 0){
		xForce = 0;
		yForce = 0;
	} else {
		float totalForce = GRAV_CONST * mass * objMass / distSquared;
		float theta = atan2(yDist, xDist);
		xForce = cos(theta) * totalForce;
		yForce = sin(theta) * totalForce;
	}

	netForce.x += xForce;
	netForce.y += yForce;
}

void Node::resetForce(){
	netForce.x = 0;
	netForce.y = 0;
}

void Node::updateVelocity(){
	//Vf = Ft / m + Vi
	velocity.x += netForce.x / mass * TIMESTEP;
	velocity.y += netForce.y / mass * TIMESTEP;
}

void Node::updatePosition(){
	//Xf = V*t + Xi
	position.x += round(velocity.x * TIMESTEP);
	position.y += round(velocity.y * TIMESTEP);
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
