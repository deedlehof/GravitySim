
#include <QApplication>
#include <QLabel>

#include "rendersim.h"

using namespace std;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	//QLabel hello("Hello World");
	//hello.show();
	RenderSim newSim;
	newSim.show();
	return app.exec();
}
