#ifndef CUBE_H
#define CUBE_H
#include <string>
#include "random.h"
using namespace std;

class Cube
{
public:
    Cube(const string& sides) : sides(sides) {}

    void randomizeCube();
    char getVisibleSide() const;
private:
    size_t side_num;
    string sides;
};

#endif // CUBE_H
