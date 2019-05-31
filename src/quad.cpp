#include "node.h"
#include "quad.h"

using namespace std;

Quad::Quad(){
	topLeft = Point(0, 0);
	botRight = Point(0, 0);
	qnode = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;

	childrenCOM.x = 0;
	childrenCOM.y = 0;
	childrenMassDistance.x = 0;
	childrenMassDistance.y = 0;
	childrenTotalMass = 0;
}

Quad::Quad(Point _topLeft, Point _botRight){
	topLeft = _topLeft;
	botRight = _botRight;
	qnode = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;

	childrenCOM.x = 0;
	childrenCOM.y = 0;
	childrenMassDistance.x = 0;
	childrenMassDistance.y = 0;
	childrenTotalMass = 0;
}

void Quad::insert(Node *newNode){
	if (newNode == NULL){
		return;
	}

	//if new node isn't in quad boundry, stop
	if (!inBoundary(newNode->getPos())){
		return;
	}

	//quad can't be subdivided more
	if (abs(topLeft.x - botRight.x) <= 1 &&
			abs(topLeft.y - botRight.y) <= 1){
		if (qnode == NULL){
			qnode = newNode;
		}
		return;
	}

	if ((topLeft.x + botRight.x) / 2 >= newNode->getX()){
		//check if insert at topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= newNode->getY()){
			//if no node at position then subdivide into new quad
			if (topLeftTree == NULL){
				topLeftTree = new Quad(
						Point(topLeft.x, topLeft.y),
						Point((topLeft.x + botRight.x) / 2, botRight.y));
			}
			//insert newNode into botLeftTree
			botLeftTree->insert(newNode);
		} else {//insert into botLeftTree
			//if no node at position then subdivide into new quad
			if (botLeftTree == NULL){
				botLeftTree = new Quad(
						Point(topLeft.x, (topLeft.y + botRight.y) / 2),
						Point((topLeft.x + botRight.x) / 2, botRight.y));
			}
			botLeftTree->insert(newNode);
		}
	} else {
		if ((topLeft.y + botRight.y) / 2 >= newNode->getY()){
			if (topRightTree == NULL){
				topRightTree = new Quad(
						Point((topLeft.x + botRight.x) / 2, topLeft.y),
						Point(botRight.x, (topLeft.y + botRight.y) / 2));
			}
			topRightTree->insert(newNode);
		} else {
			if (botRightTree == NULL){
				botRightTree = new Quad(
						Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2),
						Point(botRight.x, botRight.y));
			}
			botRightTree->insert(newNode);
		}
	}
}

Node* Quad::search(Point p){
	//check if current quad can contain it
	if (!inBoundary(p)){
		return NULL;
	}

	//We are at a quad of unit length
	if (qnode != NULL){
		return qnode;
	}

	if ((topLeft.x + botRight.x) / 2 >= p.x){
		//go down topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= p.y){
			if (topLeftTree == NULL){
				return NULL;
			}
			return topLeftTree->search(p);
		} else { //go down botLeftTree

			if (botLeftTree == NULL){
				return NULL;
			}
			return botLeftTree->search(p);
		}
	} else {
		//go down topRightTree
		if ((topLeft.y + botRight.y) / 2 >= p.y){
			if (topRightTree == NULL){
				return NULL;
			}
			return topRightTree->search(p);
		} else { //go down botRightTree
			if (botRightTree == NULL){
				return NULL;
			}
			return botRightTree->search(p);
		}
	}
}

bool Quad::inBoundary(Point p){
	return (p.x >= topLeft.x &&
			p.x <= botRight.x &&
			p.y >= topLeft.y &&
			p.y <= botRight.y);
}

void Quad::updateCOM(Point pos, int mass){
	childrenMassDistance.x += mass * pos.x;
	childrenMassDistance.y += mass * pos.y;
	childrenTotalMass += mass;
	childrenCOM.x = childrenMassDistance.x / childrenTotalMass;
	childrenCOM.y = childrenMassDistance.y / childrenTotalMass;
}

