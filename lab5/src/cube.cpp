#include "cube.h"

void Cube::randomizeCube() {
    side_num = randomInteger(0, sides.length());
}

char Cube::getVisibleSide() const {
    return sides[side_num];
}
