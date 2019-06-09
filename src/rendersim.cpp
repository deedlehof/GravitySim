#include <iostream> //io
#include <stdlib.h> //random num
#include <time.h> //rand seed
#include <QTimer> //updates sim
#include <QColor> //setting node color

#include "rendersim.h"

using namespace std;

RenderSim::RenderSim(){
	RenderSim(DEFAULT_NODE_NUM, DEFAULT_WIN_SIZE);
}

RenderSim::RenderSim(int _numNodes, int _winSize){
	//set object vars
	numNodes = _numNodes;
	winSize = _winSize;
	root = new Quad(Point(0, 0), Point(winSize, winSize));
	//default the time step to one day per update
	//each node creation method can update this
	timeStep = 24 * 3600;
	//if true rendersim will display extra info in sim
	debug = false;

	//set random seed
	srand(time(NULL));

	//get millisecond sleep time (const from node.h)
	int msSleep = 1000 / UPDATES_PER_SEC;

	createNodes();
	//createSolarSystem();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(msSleep);

}

void RenderSim::createSolarSystem(){
		//the 'sun'
		Vector2 center(winSize / 2, winSize / 2);
		int m1 = 10000;
		Vector2 v1(0.0, 0.0);
		NodeColor yellowNC(255, 255, 0);
		Node *n1 = new Node(0, center, m1, v1, yellowNC);
		nodes.push_back(n1);


		Vector2 p2(center.x, center.y - 40);
		int m2 = 10;
		Vector2 v2(0.000125, 0.0);
		NodeColor redNC(153, 0, 0);
		Node *n2 = new Node(1, p2, m2, v2, redNC);
		nodes.push_back(n2);

		n2 = new Node(2, {center.x, center.y + 90}, 13,
							{-0.00009, 0.0}, {0, 0, 200});
		nodes.push_back(n2);

}

void RenderSim::createNodes(){
	int id = 0;
	for (int i = 0; i < numNodes; i += 1){
		Vector2 startPoint(rand() % winSize + 1,
									rand() % winSize + 1);

		float startMass = (rand() % MAX_INIT_MASS + 1) + 100;

		//Vector2 startVel(((float)rand() / RAND_MAX * MAX_INIT_VELOCITY),
		//					((float)rand() / RAND_MAX * MAX_INIT_VELOCITY));
		Vector2 startVel(0.0, 0.0);

		NodeColor startColor(rand() % 256, rand() % 256, rand() % 256);

		Node *newNode = new Node(id, startPoint, startMass, startVel, startColor);
		nodes.push_back(newNode);
		id += 1;
	}
}

void RenderSim::createTestNodes(){
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
	list<Node*>::iterator it = nodes.begin();
	while (it != nodes.end()){
		if (*it){
			root->updateNodeForce(*it);
			it++;
		} else {
			cout << "DANGER! ATTEMPT TO UPDATE NON-EXISTANT NODE!\n";
			it = nodes.erase(it);
			numNodes -= 1;
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
	//if in debug, then show the quads
	if (debug) {
		painter.setPen(Qt::blue);
		painter.setBrush(Qt::white);
		vector<Point> topCorners;
		vector<Point> botCorners;
		//get the upper and lower corners of each quad
		root->getBounds(topCorners, botCorners);
		//draw each quad
		for (int i =0; i < topCorners.size(); i += 1){
			int width = botCorners[i].x - topCorners[i].x;
			int height = botCorners[i].y - topCorners[i].y;
			painter.drawRect(topCorners[i].x, topCorners[i].y, width, height);
		}
	}

	//calculate the force on each node
	updateNodesForces();

	painter.setPen(Qt::black);

	//update and draw each node
	for (auto const& node: nodes){
		//update the node's position and velocity
		//the update is with respect to the timestep passed
		node->updatePosition(timeStep);
		int radius = ceil(node->getRadius());

		NodeColor nColor= node->getColor();
		painter.setBrush(QColor(nColor.r, nColor.g, nColor.b));

		painter.drawEllipse(node->getX() - radius, node->getY() - radius,
						radius*2, radius*2);

		//force isn't cumulative over updates
		//reset it to the default
		node->resetForce();
	}
}
