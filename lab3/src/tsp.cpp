/*
 * Author: wilmi895, maxra518
 * Description:
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 *
 * sources:
 * E4:
 * Own heuristic, implement multi-fragment algorithm with complexity N^2log(N)
 * https://users.cs.cf.ac.uk/C.L.Mumford/howard/Multi-Fragment.html
 *
 * Multi-fragment (above) requires a cycle detection algorithm.
 * https://www.geeksforgeeks.org/floyds-cycle-finding-algorithm/
 */

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "Point.h"
#include "Tour.h"
using namespace std;

void test_four_points_tour(QGraphicsScene* const scene) {
	// define 4 points forming a square
	Point const a(100.0, 100.0);
	Point const b(500.0, 100.0);
	Point const c(500.0, 500.0);
	Point const d(100.0, 500.0);
	// Set up a Tour with those four points
	// The constructor should link p->q->r->s->p
	Tour SquareTour(a, b, c, d);
	// Output the Tour
	SquareTour.show();
	SquareTour.draw(scene);

	cout << "Square tour distance: " << std::fixed << std::setprecision(4)
		 << std::showpoint << SquareTour.distance() << endl;
	cout << "Square tour number of points: " << SquareTour.size() << endl;
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	string filename = "tsp10.txt";
	ifstream input;
	input.open(filename);

	// get dimensions
	int width  = 0;
	int height = 0;
	input >> width;
	input >> height;

	// setup graphical window
	auto* const view  = new QGraphicsView();
	auto* const scene = new QGraphicsScene();
	view->setScene(scene);
	view->scale(1, -1);	 // screen y-axis is inverted
	view->setSceneRect(0, 0, width, height);
	view->show();

	//test_four_points_tour(scene);

	// run insertion heuristic
	Tour tour;
	double x = 0;
	double y = 0;
	while (input >> x >> y) {
		Point p(x, y);
		tour.insertNearest(p);
		//uncomment the 4 lines below to animate
		tour.draw(scene);
		std::chrono::milliseconds dura(50);
		std::this_thread::sleep_for(dura);
		app.processEvents();
	}
	input.close();

	// print tour to standard output
	cout << "Tour distance: " << std::fixed << std::setprecision(4)
		 << std::showpoint << tour.distance() << endl;
	cout << "Number of points: " << tour.size() << endl;
	tour.show();

	// draw tour
	tour.draw(scene);
	return QApplication::exec();  // start Qt event loop
}
