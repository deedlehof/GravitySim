
#include <QApplication>
#include <QLabel>
#include <iostream>

#include "rendersim.h"

using namespace std;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	RenderSim newSim;
	newSim.show();
	return app.exec();
}
