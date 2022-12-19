/*
 * Authors: wilmi895 maxra518
 * Finds 2D points on the same line and renders the points and
 * lines to a scene. Occurs in O(N^2*log(N)).
 *
 */

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "Point.h"

// constants
static const int SCENE_WIDTH  = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for (const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input400.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    unsigned int N = 0;
    int x		   = 0;
    int y		   = 0;

    input >> N;
    points.reserve(N);

    for (unsigned i = 0; i < N; ++i) {
        input >> x >> y;
        points.emplace_back(x, y);
    }
    input.close();

    // setup graphical window
    auto* view	= new QGraphicsView();
    auto* scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1);	 // screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    for (unsigned i = 0; i < N - 1; i++) {
        unordered_map<double, int> counts {};
        Point const origin = points[i];

        for (unsigned j = i + 1; j < N; j++) {
            Point const next_point = points[j];
            double const slope	   = origin.slopeTo(next_point);

            // lookup: log(N)
            int& count = counts[slope];

            if (count >= 2) {
                render_line(scene, origin, next_point);
                QApplication::processEvents();

            } else {
                count++;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout
        << "Computing line segments took "
        << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
        << " milliseconds." << endl;

    return a.exec();  // start Qt event loop
}
