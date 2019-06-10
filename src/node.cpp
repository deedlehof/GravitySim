#include <cmath>
#include <iostream>
#include "node.h"

using namespace std;

//color is optional, defaults to black
Node::Node(int _id, Vector2 _pos, float _mass, float _density, Vector2 _vel){
	id = _id;
	position = _pos;
	mass = _mass;
	density = _density;
	velocity = _vel;
	radius = calcRadius();
}

Node::Node(int _id, Vector2 _pos, float _mass, float _density, Vector2 _vel, NodeColor _nColor){
	id = _id;
	position = _pos;
	mass = _mass;
	density = _density;
	velocity = _vel;
	nColor = _nColor;
	radius = calcRadius();
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

float Node::getRadius(){
	return radius;
}

float Node::calcRadius(){
	return cbrt(mass / (4 * density));
}

float Node::getMass(){
	return mass;
}

float Node::getDensity(){
	return density;
}

Vector2 Node::getVelocity(){
	return velocity;
}

NodeColor Node::getColor(){
	return nColor;
}

bool Node::attemptCollide(Node *collision){
	double xDist = position.x - collision->getX();
	double yDist = position.y - collision->getY();
	double distanceSquared = xDist * xDist + yDist * yDist;
	double threshold = pow(getRadius() + collision->getRadius(), 2);

	//test if the distance between the nodes
	//is greater than the distance if they were touching
	if (distanceSquared > threshold){
		return false;
	}

	//the points are touching, collide them
	float colliderMass = collision->getMass();
	float totalMass = mass + colliderMass;

	//find the proportional sum of each nodes velocity
	velocity.x = (velocity.x * mass + collision->getVelocity().x * colliderMass) / totalMass;
	velocity.y = (velocity.y * mass + collision->getVelocity().y * colliderMass) / totalMass;

	mass = totalMass;
	density = (density * mass + collision->getDensity() * colliderMass) / totalMass;
	radius = calcRadius();

	nColor = nColor + collision->getColor();

	return true;
}

void Node::addForce(float objMass, Vector2 objPos){
	double xDist, yDist;
	double xForce, yForce;

	//distance between the two nodes
	xDist = objPos.x - position.x;
	yDist = objPos.y - position.y;

	float distSquared = xDist * xDist + yDist * yDist;

	//prevent division by zero
	//node will be cleaned up by collision
	if (distSquared == 0){
		xForce = 0;
		yForce = 0;
	} else {
		//total force on object
		float totalForce = GRAV_CONST * mass * objMass / distSquared;
		float theta = atan2(yDist, xDist);
		//force along each axis
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

void Node::updateVelocity(int timeStep){
	//Vf = Ft / m + Vi
	velocity.x += netForce.x / mass * timeStep;
	velocity.y += netForce.y / mass * timeStep;
}

void Node::updatePosition(){
	//call update with arbitrary timestep (one day)
	updatePosition(24*3600);
}

void Node::updatePosition(int timeStep){
	//update the nodes velocity
	updateVelocity(timeStep);
	//Xf = V*t + Xi
	position.x += velocity.x * timeStep;
	position.y += velocity.y * timeStep;
}

void Node::print(){
	cout << "====== " << id << " ======" << endl;
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
	cout << endl;
}
