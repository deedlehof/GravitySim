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
	int id = 0;
	for (int i = 0; i < numNodes; i += 1){
		Point startPoint = Point(rand() % winSize + 1,
									rand() % winSize + 1);

		int startMass = rand() % MAX_INIT_MASS + 1;

		//Vector2 startVel(rand() % MAX_INIT_VELOCITY,
		//					rand() % MAX_INIT_VELOCITY);
		Vector2 startVel(0.0, 0.0);

		Node *newNode = new Node(id, startPoint, startMass, startVel);
		nodes.push_back(newNode);
		id += 1;
	}
	/*
		Point p1 = Point(50, 50);
		int m1 = 15;
		Vector2 v1(0.0, 0.0);
		Node *n1 = new Node(0, p1, m1, v1);
		nodes.push_back(n1);

		Point p2 = Point(75, 75);
		int m2 = 4;
		Vector2 v2(-1.0, 0.0);
		Node *n2 = new Node(1, p2, m2, v2);
		nodes.push_back(n2);

		Point p3 = Point(25, 25);
		int m3 = 4;
		Vector2 v3(1, 0.0);
		Node *n3 = new Node(2, p3, m3, v3);
		nodes.push_back(n3);
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

	if (root){
		delete root;
		root = new Quad(Point(0, 0), Point(winSize, winSize));
	}

	insertNodesIntoQuad();

	painter.setPen(Qt::blue);
	painter.setBrush(Qt::white);
	vector<Point> topCorners;
	vector<Point> botCorners;
	root->getBounds(topCorners, botCorners);
	for (int i =0; i < topCorners.size(); i += 1){
		int width = botCorners[i].x - topCorners[i].x;
		int height = botCorners[i].y - topCorners[i].y;
		painter.drawRect(topCorners[i].x, topCorners[i].y, width, height);
	}

	updateNodesForces();

	painter.setPen(Qt::white);
	painter.setBrush(Qt::black);

	for (int i = 0; i < numNodes; i += 1){
		nodes[i]->updateVelocity();
		nodes[i]->updatePosition();
		int radius = nodes[i]->getRadius();
		painter.drawEllipse(nodes[i]->getX() - radius, nodes[i]->getY() - radius,
						radius*2, radius*2);
	}
	/*
	nodes[0]->print();
	nodes[0]->resetForce();
	nodes[1]->print();
	nodes[1]->resetForce();
	cout << endl;
	*/
}
