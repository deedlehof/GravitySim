
#include <QApplication>
#include <QLabel>
#include <iostream>
#include <stdlib.h>

#include "rendersim.h"

using namespace std;

int main(int argc, char *argv[]){

	if (argc != 3){
		cout << "Usage: " << argv[0] << " <Number of Nodes> <Window Size>" << endl;
		return 1;
	}

	if (!isdigit(*argv[1]) || !isdigit(*argv[2])){
		cout << "Usage: " << argv[0] << " <Number of Nodes> <Window Size>" << endl;
		return 1;
	}

	QApplication app(argc, argv);
	RenderSim newSim(atoi(argv[1]), atoi(argv[2]));
	newSim.show();
	return app.exec();
}
