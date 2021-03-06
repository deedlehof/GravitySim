#ifndef NODE_H
#define NODE_H

#include "shared_structs.h"

using namespace std;

const float GRAV_CONST = 6.67e-11;

class Node{

	public:
		Node(int _id, Vector2 _pos, float _mass, float _density, Vector2 _vel);
		Node(int _id, Vector2 _pos, float _mass, float _density, Vector2 _vel, NodeColor _nColor);
		//getters and setters
		int getID();
		double getX();
		double getY();
		float getRadius();
		Vector2 getPos();
		float getMass();
		float getDensity();
		Vector2 getVelocity();
		NodeColor getColor();
		//force, velocity, position functions
		void addForce(float objMass, Vector2 objPos);
		void resetForce();
		void updatePosition();
		void updatePosition(int timeStep);
		bool attemptCollide(Node *collision);
		//cosmetic
		void print();


	private:
		void updateVelocity(int timeStep);
		float calcRadius();

		Vector2 position;
		float mass;
		float density;
		Vector2 velocity;
		Vector2 netForce;
		int id;
		float radius;

		NodeColor nColor;
};


#endif
