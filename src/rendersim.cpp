#include <iostream> //io
#include <stdlib.h> //random num
#include <time.h> //rand seed
#include <QTimer> //updates sim

#include "rendersim.h"

using namespace std;

RenderSim::RenderSim(){
	RenderSim(DEFAULT_NODE_NUM, DEFAULT_WIN_SIZE);
}

//TODO fix memory leak
RenderSim::RenderSim(int _numNodes, int _winSize){
	numNodes = _numNodes;
	winSize = _winSize;
	root = new Quad(Point(0, 0), Point(winSize, winSize));

	//set random seed
	srand(time(NULL));

	//get millisecond sleep time (const from node.h)
	int msSleep = 1000 / UPDATES_PER_SEC;

	createNodes();
	//TODO DELETE
	//insertNodesIntoQuad();
	//updateNodesForces();
	//

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(msSleep);


}

void RenderSim::createNodes(){
	///*
	for (int i = 0; i < numNodes; i += 1){
		Point startPoint = Point(rand() % winSize + 1,
									rand() % winSize + 1);

		int startMass = rand() % MAX_INIT_MASS + 1;

		Vector2 startVel(rand() % MAX_INIT_VELOCITY,
							rand() % MAX_INIT_VELOCITY);

		Node *newNode = new Node(startPoint, startMass, startVel);
		nodes.push_back(newNode);
	}
	//*/
	/*
		Point p1 = Point(50, 50);
		int m1 = 8;
		Vector2 v1(0, 0);
		Node *n1 = new Node(p1, m1, v1);
		nodes.push_back(n1);

		Point p2 = Point(50, 25);
		int m2 = 4;
		Vector2 v2(0, 0);
		Node *n2 = new Node(p2, m2, v2);
		nodes.push_back(n2);
	*/
}

void RenderSim::insertNodesIntoQuad(){
	for (int i = 0; i < numNodes; i += 1){
		root->insert(nodes[i]);
	}
}

void RenderSim::updateNodesForces(){
	for (int i = 0; i < numNodes; i += 1){
		root->updateNodeForce(nodes[i]);
	}
}

QSize RenderSim::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize RenderSim::sizeHint() const {
	return QSize(winSize, winSize);
}

void RenderSim::paintEvent(QPaintEvent *){
	QPainter painter(this);
	//painter.setPen(Qt::blue);
	painter.setBrush(Qt::black);

	if (root){
		delete root;
		root = new Quad(Point(0, 0), Point(winSize, winSize));
	}
	insertNodesIntoQuad();
	updateNodesForces();

	for (int i = 0; i < numNodes; i += 1){
		nodes[i]->updateVelocity();
		nodes[i]->updatePosition();
		painter.drawEllipse(nodes[i]->getX(), nodes[i]->getY(),
						nodes[i]->getMass(), nodes[i]->getMass());
		nodes[i]->print();
		cout << endl;
		nodes[i]->resetForce();
	}
}
