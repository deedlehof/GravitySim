#include <QPainter>
#include <iostream>

#include "rendersim.h"

using namespace std;

RenderSim::RenderSim(){
	cout << "test" << endl;
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
