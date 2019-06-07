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

	//createNodes();
	createSolarSystem();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(msSleep);

}

void RenderSim::createSolarSystem(){
		//the 'sun'
		Vector2 center(winSize / 2, winSize / 2);
		int m1 = 10000;
		Vector2 v1(0.0, 0.0);
		Node *n1 = new Node(0, center, m1, v1);
		nodes.push_back(n1);


		Vector2 p2(center.x, center.y - 40);
		int m2 = 10;
		Vector2 v2(0.000125, 0.0);
		Node *n2 = new Node(1, p2, m2, v2);
		nodes.push_back(n2);

		n2 = new Node(2, {center.x, center.y + 90}, 13, {-0.00009, 0.0});
		nodes.push_back(n2);

		//n2 = new Node(3, {250, 420}, 9, {-0.00007, 0.0});
		//nodes.push_back(n2);
}

void RenderSim::createNodes(){
	/*
	Vector2 p1(250, 250);
	int m1 = 300;
	Vector2 v1(0.0, 0.0);
	Node *n1 = new Node(0, p1, m1, v1);
	nodes.push_back(n1);
	*/
	///*
	int id = 0;
	for (int i = 0; i < numNodes; i += 1){
		Vector2 startPoint(rand() % winSize + 1,
									rand() % winSize + 1);

		float startMass = (rand() % MAX_INIT_MASS + 1) + 100;

		Vector2 startVel(((float)rand() / RAND_MAX * MAX_INIT_VELOCITY),
							((float)rand() / RAND_MAX * MAX_INIT_VELOCITY));
		//Vector2 startVel(0.0, 0.0);

		Node *newNode = new Node(id, startPoint, startMass, startVel);
		nodes.push_back(newNode);
		id += 1;
	}
	//*/
	/*
		Vector2 p1(250, 250);
		int m1 = 1000;
		Vector2 v1(0.0, 0.0);
		Node *n1 = new Node(0, p1, m1, v1);
		nodes.push_back(n1);

		Vector2 p2(250, 210);
		int m2 = 100;
		Vector2 v2(0.0001, 0.0);
		//Vector2 v2(0.00001, 0.0);
		//Vector2 v2(0.0, 0.0);
		Node *n2 = new Node(1, p2, m2, v2);
		nodes.push_back(n2);

		//Point p3 = Point(25, 25);
		//int m3 = 4;
		//Vector2 v3(1, 0.0);
		//Node *n3 = new Node(2, p3, m3, v3);
		//nodes.push_back(n3);
	*/
}

void RenderSim::insertNodesIntoQuad(){
	list<Node*>::iterator it = nodes.begin();
	while (it != nodes.end()){
		if (!root->insert(*it)){
			it = nodes.erase(it);
			numNodes -= 1;
		} else {
			it++;
		}
	}
}

void RenderSim::updateNodesForces(){
	list<Node*>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it){
		if (*it){
			root->updateNodeForce(*it);
		} else {
			cout << "DANGER! DANGER! ATTEMPT TO DO BAD THINGS!" << endl;
		}
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
	/*
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
	*/
	updateNodesForces();

	painter.setPen(Qt::white);
	painter.setBrush(Qt::black);

	for (auto const& node: nodes){
		if (node){
			node->updateVelocity();
			node->updatePosition();
			int radius = ceil(node->getRadius());
			painter.drawEllipse(node->getX() - radius, node->getY() - radius,
							radius*2, radius*2);
			node->resetForce();
		}
	}
	/*
	nodes[0]->print();
	nodes[0]->resetForce();
	nodes[1]->print();
	nodes[1]->resetForce();
	cout << endl;
	*/
}
