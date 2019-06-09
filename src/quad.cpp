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

Quad::~Quad(){
	//node will be cleaned up in another place
	//the tree is rebuilt multiple times with
	//the same nodes
	if (topLeftTree){
		delete topLeftTree;
		delete topRightTree;
		delete botLeftTree;
		delete botRightTree;
	}
}

//used for debugging
//gets the corners of the quads
void Quad::getBounds(vector<Point> &topCorners, vector<Point> &botCorners){
	topCorners.push_back(topLeft);
	botCorners.push_back(botRight);

	//if not a leaf then recursively call on children
	if (topLeftTree) {
		topLeftTree->getBounds(topCorners, botCorners);
		topRightTree->getBounds(topCorners, botCorners);
		botLeftTree->getBounds(topCorners, botCorners);
		botRightTree->getBounds(topCorners, botCorners);
	}
}

bool Quad::insert(Node *newNode){
	//if new node isn't in quad boundry, stop
	if (!inBoundary(newNode->getPos())){
		return false;
	}

	//might need later
	/*
	if ((botRight.x - topLeft.x) < 1){
		return false;
	}
	*/

	//if quad is leaf
	if (!topLeftTree){
		//no node in leaf, insert it
		if (!node) {
			node = newNode;
			return true;
		} else { //already has node, turn quad into internal
			//check for collision
			if (node->attemptCollide(newNode)) { return false; }

			subdivide();
			if (!insert(node)) return false;
			node = NULL;
		}
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

Node* Quad::search(Vector2 p){
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
	//don't subdivide if subtree alread exists
	if (topLeftTree != NULL){
		return;
	}

	//create new quads
	topLeftTree = new Quad(
			Point(topLeft.x, topLeft.y),
			Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2));
	topRightTree = new Quad(
			Point((topLeft.x + botRight.x) / 2 + 1, topLeft.y),
				Point(botRight.x, (topLeft.y + botRight.y) / 2));
	botLeftTree = new Quad(
			Point(topLeft.x, (topLeft.y + botRight.y) / 2 + 1),
			Point((topLeft.x + botRight.x) / 2, botRight.y));
	botRightTree = new Quad(
			Point((topLeft.x + botRight.x) / 2 + 1, (topLeft.y + botRight.y) / 2 + 1),
			Point(botRight.x, botRight.y));
}

bool Quad::inBoundary(Vector2 p){
	return (p.x >= topLeft.x &&
			p.x <= botRight.x &&
			p.y >= topLeft.y &&
			p.y <= botRight.y);
}

void Quad::updateCOM(Vector2 pos, int mass){
	nodeMassDistance.x += mass * pos.x;
	nodeMassDistance.y += mass * pos.y;
	totalMass += mass;
	COM.x = nodeMassDistance.x / totalMass;
	COM.y = nodeMassDistance.y / totalMass;
}

void Quad::updateNodeForce(Node *fNode){
	if (node) {
		//update force if node is not updating node
		if (fNode->getID() != node->getID()){
			fNode->addForce(node->getMass(), node->getPos());
		}
	} else if (topLeftTree){
		//run the algorithm on all of the children
		topLeftTree->updateNodeForce(fNode);
		topRightTree->updateNodeForce(fNode);
		botLeftTree->updateNodeForce(fNode);
		botRightTree->updateNodeForce(fNode);
	}
}
