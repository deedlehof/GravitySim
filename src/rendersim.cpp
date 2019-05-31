#include <QPainter>
#include <iostream>

#include "rendersim.h"
#include "node.h"
#include "quad.h"

using namespace std;

RenderSim::RenderSim(){
	cout << "Creating the root quad!" << endl;
	Quad center(Point(0, 0), Point (8, 8));
	cout << "Creating new nodes for the quad tree" << endl;
	Node a(Point(1, 1), 1, Vector2(1, 1));
	Node b(Point(2, 5), 2, Vector2(2, 2));
	Node c(Point(7, 6), 3, Vector2(3, 3));
	cout << "Inserting new nodes" << endl;
	cout << "Insert A" << endl;
	center.insert(&a);
	cout << "Insert B" << endl;
	center.insert(&b);
	cout << "Insert C" << endl;
	center.insert(&c);
	cout << "Searching for new nodes..." << endl;
	cout << "Node a: " <<
		center.search(Point(1, 1))->getMass() << endl;
	cout << "Node b: " <<
		center.search(Point(2, 5))->getMass() << endl;
	cout << "Node c: " <<
		center.search(Point(7, 6))->getMass() << endl;
	cout << "Non-existant node: " <<
		center.search(Point(5, 5)) << endl;
}

QSize RenderSim::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize RenderSim::sizeHint() const {
	return QSize(400, 400);
}

void RenderSim::paintEvent(QPaintEvent *){
	QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.setBrush(Qt::black);

	painter.drawEllipse(40, 40, 100, 100);
}
