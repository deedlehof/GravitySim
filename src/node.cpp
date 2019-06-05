#include <cmath>
#include <iostream>
#include "node.h"

using namespace std;

Node::Node(int _id, Point _pos, int _mass, Vector2 _vel){
	id = _id;
	position = _pos;
	mass = _mass;
	velocity = _vel;
}

int Node::getID(){
	return id;
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

int Node::getRadius(){
	return ceil(mass/2);
}

int Node::getMass(){
	return mass;
}

Vector2 Node::getVelocity(){
	return velocity;
}

bool Node::attemptCollide(Node *collision){
	int xDist = position.x - collision->getX();
	int yDist = position.y - collision->getY();
	int distanceSquared = xDist * xDist + yDist * yDist;
	int threshold = pow(getRadius() + collision->getRadius(), 2);

	//test if the distance between the nodes
	//is greater than the distance if they were touching
	if (distanceSquared > threshold){
		return false;
	}

	//the points are touching, collide them
	int colliderMass = collision->getMass();
	int totalMass = mass + colliderMass;

	//updates nodes values
	position.x = round((position.x * mass + collision->getX() * colliderMass) / totalMass);
	position.y = round((position.y * mass + collision->getY() * colliderMass) / totalMass);

	velocity.x = (velocity.x * mass + collision->getVelocity().x * colliderMass) / totalMass;
	velocity.y = (velocity.y * mass + collision->getVelocity().y * colliderMass) / totalMass;

	mass = totalMass;

	return true;
}

void Node::addForce(int objMass, Point objPos){
	int xDist, yDist;
	float xForce, yForce;

	xDist = objPos.x - position.x;
	yDist = objPos.y - position.y;

	int distSquared = xDist * xDist + yDist * yDist;

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
