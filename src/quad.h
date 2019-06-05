#ifndef QUAD_H
#define QUAD_H

#include <cmath>
#include <vector>
#include "node.h"

using namespace std;

//default 0.5
//value of 0 will make algorithm run force calc for each node
const float BODY_THRESHOLD = 0.5;

class Quad {

	friend class RenderSim;

	public:
		Quad();
		Quad(Point _topLeft, Point _botRight);
		~Quad();
		bool insert(Node *newNode);
		Node* search(Point p);
		bool inBoundary(Point p);
		void updateNodeForce(Node *fNode);
		void getBounds(vector<Point> &topCorners, vector<Point> &botCorners);

	private:
		void updateCOM(Point pos, int mass);
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

		Point COM; //children's center of mass
		int totalMass;
		//used for calculating center of mass
		Point nodeMassDistance;

};

#endif
