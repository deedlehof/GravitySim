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
		Node(int _id, Vector2 _pos, float _mass, Vector2 _vel, NodeColor _nColor);

		int getID();
		double getX();
		double getY();
		float getRadius();
		Vector2 getPos();
		float getMass();
		Vector2 getVelocity();
		NodeColor getColor();

		void addForce(float objMass, Vector2 objPos);
		void resetForce();
		void updatePosition();
		void updateVelocity();
		bool attemptCollide(Node *collision);

		void print();


	private:
		Vector2 position;
		float mass;
		Vector2 velocity;
		Vector2 netForce;
		int id;

		NodeColor nColor;
};


#endif
