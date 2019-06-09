#include <QApplication>
#include <QLabel>
#include <iostream>
#include <stdlib.h>

#include "rendersim.h"

using namespace std;

int main(int argc, char *argv[]){

	//number of nodes is optional
	//some simulations don't require it
	if (argc < 2 || argc > 4){
		cout << "Usage: " << argv[0] << " Window Size <Number of Nodes>" << endl;
		return 1;
	}

	//check if inputs are of the correct type
	//convert them if so
	int winSize, numNodes;
	if (argc == 2) {
		if (isdigit(*argv[1])){
			winSize = atoi(argv[1]);
			numNodes = 0;
		} else {
			cout << "Usage: " << argv[0] << " Window Size <Number of Nodes>" << endl;
			return 1;
		}
	} else {
		if (isdigit(*argv[1]) && isdigit(*argv[2])){
			winSize = atoi(argv[1]);
			numNodes = atoi(argv[2]);
		} else {
			cout << "Usage: " << argv[0] << " Window Size <Number of Nodes>" << endl;
			return 1;
		}
	}


	QApplication app(argc, argv);
	RenderSim newSim(numNodes, winSize);
	newSim.show();

	return app.exec();
}
