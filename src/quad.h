#ifndef QUAD_H
#define QUAD_H

#include <cmath>
#include <vector>
#include "node.h"
#include "shared_structs.h"

using namespace std;

//default 0.5
//value of 0 will make algorithm run force calc for each node
const float BODY_THRESHOLD = 0.5;

class Quad {
	public:
		Quad();
		Quad(Point _topLeft, Point _botRight);
		~Quad();
		bool insert(Node *newNode);
		Node* search(Vector2 p);
		bool inBoundary(Vector2 p);
		void updateNodeForce(Node *fNode);
		void getBounds(vector<Point> &topCorners, vector<Point> &botCorners);

	private:
		void updateCOM(Vector2 pos, int mass);
		void subdivide();

		//Holds two corners of node boundry
		Point topLeft;
		Point botRight;
		//Nodes in quad
		Node *node;
		//Children of this tree
		Quad *topLeftTree;
		Quad *topRightTree;
		Quad *botLeftTree;
		Quad *botRightTree;
		//children's center of mass
		Vector2 COM;
		int totalMass;
		//used for calculating center of mass
		Vector2 nodeMassDistance;

};

#endif
