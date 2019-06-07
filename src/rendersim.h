#ifndef RENDERSIM_H
#define REDNERSIM_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <list>

#include "node.h"
#include "quad.h"

using namespace std;

const int DEFAULT_NODE_NUM = 20;
const int DEFAULT_WIN_SIZE = 400;
const int MAX_INIT_MASS = 900;
const float MAX_INIT_VELOCITY = 0.00001;

class RenderSim : public QWidget {
	Q_OBJECT

	public:
		RenderSim();
		RenderSim(int _numNodes, int _winSize);

		QSize minimumSizeHint() const override;
		QSize sizeHint() const override;

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		void createNodes();
		void createSolarSystem();
		void insertNodesIntoQuad();
		void updateNodesForces();


		int numNodes;
		int winSize;
		Quad *root;
		list<Node*> nodes;
};

#endif
