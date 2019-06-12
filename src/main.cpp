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
		cout << "Usage: " << argv[0] << " <Window Size> <Number of Nodes>" << endl;
		cout << "OR" << endl;
		cout << "Usage: " << argv[0] << " <File Name>" << endl;
		return 1;
	}

	QApplication app(argc, argv);

	//check if inputs are of the correct type
	RenderSim *newSim;

	if (argc == 2) {
		newSim = new RenderSim(argv[1]);
	} else {
		if (isdigit(*argv[1]) && isdigit(*argv[2])){
			cout << atoi(argv[2]) << " " << atoi(argv[1]) << endl;
			newSim = new RenderSim(atoi(argv[2]), atoi(argv[1]));
		} else {
			cout << "Usage: " << argv[0] << " <Window Size> <Number of Nodes>" << endl;
			return 1;
		}
	}

	newSim->show();

	return app.exec();
}
