#include "node.h"
#include "quad.h"
#include <iostream>

using namespace std;

Quad::Quad(){
	topLeft = Point(0, 0);
	botRight = Point(0, 0);
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;

	COM.x = 0;
	COM.y = 0;
	nodeMassDistance.x = 0;
	nodeMassDistance.y = 0;
	totalMass = 0;

	node = NULL;
}

Quad::Quad(Point _topLeft, Point _botRight){
	topLeft = _topLeft;
	botRight = _botRight;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;

	COM.x = 0;
	COM.y = 0;
	nodeMassDistance.x = 0;
	nodeMassDistance.y = 0;
	totalMass = 0;

	node = NULL;
}

bool Quad::insert(Node *newNode){
	//if new node isn't in quad boundry, stop
	if (!inBoundary(newNode->getPos())){
		return false;
	}

	//TODO USE THIS TO DETERMINE IF TWO NODES OVERLAP, COLLISION

	//WHEN MAKING NEW NODES USE THE FALSE RETURN AS
	//A SIGN TO INSERT ANOTHER, EXTRA NODE TO MAKE
	//ACTUAL NODE NUMBER CORRECT
	//check that quad isn't too small
	if (abs(topLeft.x - botRight.x) < 1){
		return false;
	}

	//if there is space in this quad and there are no subdivisions
	if (node == NULL && topLeftTree == NULL){
		node = newNode;
		return true;
	}

	//otherwise, subdivide and add the point to whichever subtree will accept it
	if (topLeftTree == NULL){
		subdivide();
	}

	//move the node stored in this quad down into leaves
	//return false if operation fails
	if (node != NULL){
		updateCOM(node->getPos(), node->getMass());

		if (!(topLeftTree->insert(node) ||
				topRightTree->insert(node) ||
				botLeftTree->insert(node) ||
				botRightTree->insert(node)))	{
			return false;
		}
		node = NULL;
	}

	//the node will be a children so update quads com, mass, and nodeMassDistance
	updateCOM(newNode->getPos(), newNode->getMass());

	if (topLeftTree->insert(newNode)) return true;
	if (topRightTree->insert(newNode)) return true;
	if (botLeftTree->insert(newNode)) return true;
	if (botRightTree->insert(newNode)) return true;

	//should never get here
	return false;
}

Node* Quad::search(Point p){
	//check if current quad can contain it
	if (!inBoundary(p)){
		return NULL;
	}

	//check if point is one of quads nodes
	if (node && node->getPos() == p){
		return node;
	}

	//check for subtrees, if none return NULL
	if(topLeftTree == NULL){
		return NULL;
	}

	Node *retNode;
	//recursively check subtrees
	if ((retNode = topLeftTree->search(p))) return retNode;
	if ((retNode = topRightTree->search(p))) return retNode;
	if ((retNode = botLeftTree->search(p))) return retNode;
	if ((retNode = botRightTree->search(p))) return retNode;

	return NULL;
}

void Quad::subdivide(){
	if (topLeftTree == NULL){
		topLeftTree = new Quad(
				Point(topLeft.x, topLeft.y),
				Point((topLeft.x + botRight.x) / 2, botRight.y));
	}

	if (topRightTree == NULL){
		topRightTree = new Quad(
				Point((topLeft.x + botRight.x) / 2, topLeft.y),
					Point(botRight.x, (topLeft.y + botRight.y) / 2));
	}
	if (botLeftTree == NULL){
		botLeftTree = new Quad(
				Point(topLeft.x, (topLeft.y + botRight.y) / 2),
				Point((topLeft.x + botRight.x) / 2, botRight.y));
	}
	if (botRightTree == NULL){
		botRightTree = new Quad(
				Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2),
				Point(botRight.x, botRight.y));
	}
}

bool Quad::inBoundary(Point p){
	return (p.x >= topLeft.x &&
			p.x <= botRight.x &&
			p.y >= topLeft.y &&
			p.y <= botRight.y);
}

void Quad::updateCOM(Point pos, int mass){
	nodeMassDistance.x += mass * pos.x;
	nodeMassDistance.y += mass * pos.y;
	totalMass += mass;
	COM.x = nodeMassDistance.x / totalMass;
	COM.y = nodeMassDistance.y / totalMass;
}

void Quad::updateNodeForce(Node *fNode){
	//a node shouldn't be updated with it's own force
	if (node && fNode->getPos() == node->getPos()){
		return;
	}

	//quad is empty, return
	if (!node && !topLeftTree){
		return;
	}

	//if the node is external add quad's node to fNode's force
	if (node && !topLeftTree){
		fNode->addForce(node->getMass(), node->getPos());
		return;
	}

	//Otherwise, the node is internal
	//check if it is within threshold distance
	int distanceSquared = pow(fNode->getX() - COM.x, 2) +
							pow(fNode->getY() - COM.y, 2);

	int regionWidthSquared = pow(topLeft.x - botRight.x, 2);
	//cast one variable to float to aviod int division
	if ((float)regionWidthSquared / distanceSquared < BODY_THRESHOLD){
		//treat region as one large body
		fNode->addForce(totalMass, COM);
		return;
	} else {
		//run the algorithm on all of the children
		topLeftTree->updateNodeForce(fNode);
		topRightTree->updateNodeForce(fNode);
		botLeftTree->updateNodeForce(fNode);
		botRightTree->updateNodeForce(fNode);
	}
}
