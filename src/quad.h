#ifndef QUAD_H
#define QUAD_H

#include <cmath>
#include "node.h"

using namespace std;

class Quad {

	public:
		Quad();
		Quad(Point _topLeft, Point _botRight);
		void insert(Node *newNode);
		Node* search(Point p);
		bool inBoundary(Point p);

	private:
		//Holds two corners of node boundry
		Point topLeft;
		Point botRight;
		//Node details
		Node *qnode;
		//Children of this tree
		Quad *topLeftTree;
		Quad *topRightTree;
		Quad *botLeftTree;
		Quad *botRightTree;

		Point childrenCOM; //children's center of mass
		int childrenTotalMass;
		//used for calculating center of mass
		Point childrenMassDistance;

		void updateCOM(Point pos, int mass);
};

#endif
