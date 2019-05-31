#include "node.h"
#include "quad.h"

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

	numNodesInQuad = 0;
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

	numNodesInQuad = 0;
}

bool Quad::insert(Node *newNode){
	//if new node isn't in quad boundry, stop
	if (!inBoundary(newNode->getPos())){
		return false;
	}

	//the node will be inserted somewhere in this quad or
	//it's children so update its com, mass, and nodeMassDistance
	updateCOM(newNode->getPos(), newNode->getMass());

	//if there is space in this quad and there are no subdivisions
	if(numNodesInQuad < MAX_NODE_CAP && topLeftTree == NULL){
		nodes[numNodesInQuad] = newNode;
		numNodesInQuad += 1;
		return true;
	}

	//otherwise, subdivide and add the point to whichever subtree will accept it
	if (topLeftTree == NULL){
		subdivide();
	}

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
	for (int i = 0; i < numNodesInQuad; i+= 1){
		if (nodes[i]->getPos() == p){
			return nodes[i];
		}
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

