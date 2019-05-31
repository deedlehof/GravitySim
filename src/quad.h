#ifndef QUAD_H
#define QUAD_H

#include <cmath>
#include "node.h"

using namespace std;


class Quad {

	public:
		Quad();
		Quad(Point _topLeft, Point _botRight);
		bool insert(Node *newNode);
		Node* search(Point p);
		bool inBoundary(Point p);
		void updateTree();

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
