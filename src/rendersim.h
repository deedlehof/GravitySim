#ifndef RENDERSIM_H
#define REDNERSIM_H

#include <QBrush>
#include <QPen>
#include <QWidget>

using namespace std;

class RenderSim : public QWidget {
	Q_OBJECT

	public:
		RenderSim();

		QSize minimumSizeHint() const override;
		QSize sizeHint() const override;

	protected:
		void paintEvent(QPaintEvent *event) override;
};

#endif
