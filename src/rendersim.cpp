#include <iostream> //io
#include <stdlib.h> //random num
#include <time.h> //rand seed
#include <chrono> //convert to ms
#include <thread> //used for thread sleeping

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

	//get millisecond sleep time
	int msSleep = 1000 / UPDATES_PER_SEC;

	createNodes();

	insertNodesIntoQuad();
	updateNodesForces();

	//repaint();
	update();

	//this_thread::sleep_for(chrono::milliseconds(msSleep));
	//delete root;

}

void RenderSim::createNodes(){
	for (int i = 0; i < numNodes; i += 1){
		Point startPoint = Point(rand() % winSize + 1,
									rand() % winSize + 1);

		int startMass = rand() % MAX_INIT_MASS + 1;

		Vector2 startVel(rand() % MAX_INIT_VELOCITY,
							rand() % MAX_INIT_VELOCITY);

		Node *newNode = new Node(startPoint, startMass, startVel);
		nodes.push_back(newNode);
	}
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

	for (int i = 0; i < numNodes; i += 1){
		painter.drawEllipse(nodes[i]->getX(), nodes[i]->getY(),
						nodes[i]->getMass(), nodes[i]->getMass());
	}
}
