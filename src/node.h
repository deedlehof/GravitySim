#ifndef NODE_H
#define NODE_H

#include "constants.h"

using namespace std;

class Node{

	friend class Quad;

	/* NODE CLASS
	Given:
		a unique id
		position in AU
		mass in MASS_SCALE adjusted form
		velocity
	*/

	public:
		Node(int _id, Vector2 _pos, float _mass, Vector2 _vel);
		int getID();
		double getX();
		double getY();
		float getRadius(); //RADIUS IN AU
		Vector2 getPos();
		float getMass(); //MASS IN MASS_SCALE ADJUSTED FORM
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
