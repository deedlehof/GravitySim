#include <iostream> //io
#include <stdlib.h> //random num
#include <time.h> //rand seed
#include <QTimer> //updates sim
#include <QColor> //setting node color
#include <fstream> //reading nodes from file
#include <sstream> //break line into data

#include "rendersim.h"

using namespace std;

RenderSim::RenderSim(char* fileName){
	debug = false;

	//open file
	ifstream file(fileName);

	//test that file opened
	//error out if failed
	if (!file.is_open()){
		cout << "Failed to open file!" << endl;
		return;
	}

	//get header info
	file >> winSize;
	file >> scaleFactor;
	file >> timeStep;

	string line;
	numNodes = 0;

	double x, y, velx, vely;
	float mass, density;
	unsigned short r, g, b;

	//remove end line
	getline(file, line);

	//loop through nodes in file
	//create a node for each line in the file
	while (getline(file, line)){
		// the # char is for comments
		if (line[0] != '#') {
			//use stringstream to split each line into data
			stringstream liness(line);

			liness >> x >> y;
			Vector2 pos(x * scaleFactor, y * scaleFactor);

			liness >> velx >> vely;
			Vector2 vel(velx, vely);

			liness >> mass >> density;

			liness >> r >> g >> b;
			NodeColor col(r, g, b);

			Node *tmp = new Node(numNodes, pos, mass, density, vel, col);
			nodes.push_back(tmp);

			numNodes += 1;
		}
	}

	file.close();

	int msSleep = 1000 / UPDATES_PER_SEC;

	//generate initial quad
	root = new Quad(Point(0, 0), Point(winSize * scaleFactor, winSize * scaleFactor));

	//start drawing loop
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(msSleep);
}

RenderSim::RenderSim(int _numNodes, int _winSize){
	//set object vars
	numNodes = _numNodes;
	winSize = _winSize;
	//if true rendersim will display extra info in sim
	debug = false;

	//set random seed
	srand(time(NULL));

	//get millisecond sleep time (const from node.h)
	int msSleep = 1000 / UPDATES_PER_SEC;

//	createTestNodes();
	createNodes();
//	createSolarSystem();

	//quad must be generated after nodes
	//need the scale factor from node generation
	//to determine the outer most quad size
	root = new Quad(Point(0, 0), Point(winSize * scaleFactor, winSize * scaleFactor));

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(msSleep);

}

void RenderSim::createSolarSystem(){
	timeStep = 12 * 3600;
	scaleFactor = 1;

	//the 'sun'
	Vector2 center(winSize / 2, winSize / 2);
	int m1 = 10000;
	Vector2 v1(0.0, 0.0);
	NodeColor yellowNC(255, 255, 0);
	Node *n1 = new Node(0, center, m1, 5, v1, yellowNC);
	nodes.push_back(n1);


	Vector2 p2(center.x, center.y - 40);
	int m2 = 10;
	Vector2 v2(0.000125, 0.0);
	NodeColor redNC(153, 0, 0);
	Node *n2 = new Node(1, p2, m2, 1, v2, redNC);
	nodes.push_back(n2);

	n2 = new Node(2, {center.x, center.y + 90}, 13, 1,
						{-0.00009, 0.0}, {0, 0, 200});
	nodes.push_back(n2);

}

void RenderSim::createNodes(){
	timeStep = 24 * 3600 / (UPDATES_PER_SEC * ((float)numNodes / winSize));
//	timeStep = 12 * 3600;
	scaleFactor = 2;

	int id = 0;
	for (int i = 0; i < numNodes; i += 1){
		Vector2 startPoint((rand() % winSize + 1) * scaleFactor,
									(rand() % winSize + 1) * scaleFactor);

		float startMass = (rand() % MAX_INIT_MASS + 1) + 100;

		Vector2 startVel(((float)rand() / RAND_MAX * (MAX_INIT_VELOCITY * 2) - MAX_INIT_VELOCITY),
							((float)rand() / RAND_MAX * (MAX_INIT_VELOCITY * 2) - MAX_INIT_VELOCITY));
		//Vector2 startVel(0.0, 0.0);

		NodeColor startColor(rand() % 256, rand() % 256, rand() % 256);

		//Node *newNode = new Node(id, startPoint, startMass, 0.5, startVel, startColor);
		Node *newNode = new Node(id, startPoint, startMass, 3, startVel, startColor);
		nodes.push_back(newNode);
		id += 1;
	}
}

void RenderSim::createTestNodes(){
	timeStep = 24 * 3600;
	scaleFactor = 1;

	Vector2 p1(250, 250);
	int m1 = 1000;
	Vector2 v1(0.0, 0.0);
	Node *n1 = new Node(0, p1, m1, 0.5, v1);
	nodes.push_back(n1);

	Vector2 p2(250, 150);
	int m2 = 1000;
	Vector2 v2(0.0, 0.0);
	//Vector2 v2(0.00001, 0.0);
	//Vector2 v2(0.0, 0.0);
	Node *n2 = new Node(1, p2, m2, 2, v2);
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
		root = new Quad(Point(0, 0), Point(winSize * scaleFactor,
											winSize * scaleFactor));
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
		double scaledRadius = node->getRadius() / scaleFactor;

		NodeColor nColor= node->getColor();
		painter.setBrush(QColor(nColor.r, nColor.g, nColor.b));

		painter.drawEllipse((node->getX() / scaleFactor) - scaledRadius,
								(node->getY() / scaleFactor) - scaledRadius,
								scaledRadius*2, scaledRadius*2);

		//force isn't cumulative over updates
		//reset it to the default
		node->resetForce();
	}
}
